#include <cassert>

#include <algorithm>

#include <kui/screen.hpp>
#include <kui/input.hpp>
#include <kui/logger.hpp>
#include <kui/ansi.hpp>

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <csignal>
#include <sys/ioctl.h>

namespace kui {



    Screen::Screen() {
        assert(Screen::_instances == 0);
        Screen::_instances ++;
        _quit = false;
        _total_updates = 0;

        _on_input_callback = [](auto e){};
        _on_update_callback = [](auto e){};
        _on_resize_callback = [](auto e){};
        _on_quit_callback = [](auto e){};

        signal(SIGWINCH, Screen::resize_signal);

        Screen::_enable_raw_mode();

        auto size = _get_terminal_size();
        resize(size.row, size.column);
    }

    Screen::~Screen() {
        Screen::_instances--;
        assert(Screen::_instances == 0);
    }

    void Screen::run() {

        update();

        while(!_quit) {
            auto input = _get_input();

            _on_input_callback(Event_on_input{*this, input});

            update();
        }
    }

    void Screen::quit() {
        _on_quit_callback(Event_on_quit{*this});
        _quit = true;
    }

    std::shared_ptr<Box> Screen::add_box() {
        auto box = std::make_shared<Box>(this, [](auto e){});
        _boxes.push_back(box);
        return box;
    }

    std::shared_ptr<Box> Screen::add_box(Box::Callback_on_init callback) {
        auto box = std::make_shared<Box>(this, callback);
        _boxes.push_back(box);
        return box;
    }

    bool Screen::remove_box(std::shared_ptr<Box> box) {
        auto box_it = std::find(_boxes.begin(), _boxes.end(), box);
        if(box_it == _boxes.end()) return false;

        _boxes.erase(box_it);
        return true;
    }

    void Screen::resize(unsigned int rows, unsigned int columns) {
        if(rows == _rows && columns == _columns) return;

        auto prev = Point<unsigned int>(_rows, _columns);
        _rows = rows;
        _columns = columns;
        auto curr = Point<unsigned int>(_rows, _columns);
        _on_resize_callback(Event_on_resize{*this, prev, curr});

        update();
    }

    Screen & Screen::get_screen() {
        static Screen s;
        return s;
    }

    void Screen::resize_signal(int arg) {
        auto& screen = Screen::get_screen();
        auto size = screen._get_terminal_size();
        screen.resize(size.row, size.column);
    }

    void Screen::update() {
        _on_update_callback(Event_on_update{*this});

        for(auto& b: _boxes) {
            b->update();
        }

        Ansi::clear_screen();
        for(auto& box: _boxes) {
            _update_box(*box);
        }
    }

    void Screen::_update_box(Box &b) {
        auto& buf = b.buffer();
        auto& attrs = b.attributes();

        using size_type = std::vector<char>::size_type;
        std::string s;

        Attribute curr_attr;

        auto start_row = std::max<int>(0, b.row());
        auto end_row = std::min<int>(_rows, b.row()+b.rows());

        auto start_column = std::max<int>(0, b.column());
        auto end_column = std::min<int>(_columns, b.column()+b.columns());

        // Exit if nothing to write
        if(start_row >= end_row || start_column >= end_column) {
            return;
        }

        KUI_LOG(debug, "Start row: " << start_row);
        KUI_LOG(debug, "End row: " << end_row);

        KUI_LOG(debug, "Start column: " << start_column);
        KUI_LOG(debug, "End column: " << end_column);

        KUI_LOG(debug, start_row - b.row() << " - " << start_column - b.column());

        // Move to proper location
        Ansi::move_cursor(start_row, start_column);

        curr_attr = attrs(start_row - b.row() , start_column - b.column());
        Ansi::attribute_reset();
        Ansi::attribute_foreground(b.foreground_color());
        Ansi::attribute_background(b.background_color());

        Ansi::attribute_foreground(curr_attr.foreground);
        Ansi::attribute_background(curr_attr.background);

        if(curr_attr.bold) {
            Ansi::attribute_bold();
        }
        if(curr_attr.underline) {
            Ansi::attribute_underline();
        }

        for(int row = start_row; row < end_row; row++) {
            int r = row - b.row();

            for(int column = start_column; column < end_column; column++) {
                int c = column - b.column();

                KUI_LOG(debug, "Cursor: (" << row << ", " << column << ")\tBuffer: (" << r << ", " << c << ")");

                auto attr = attrs(r, c);
                auto ch = buf(r, c);

                if(attr != curr_attr) {
                    curr_attr = attr;
                    Ansi::attribute_reset();
                    Ansi::attribute_foreground(b.foreground_color());
                    Ansi::attribute_background(b.background_color());

                    Ansi::attribute_foreground(curr_attr.foreground);
                    Ansi::attribute_background(curr_attr.background);

                    if(curr_attr.bold) {
                        Ansi::attribute_bold();
                    }
                    if(curr_attr.underline) {
                        Ansi::attribute_underline();
                    }
                }

                Ansi::write_stdout(ch);
            }

            if(r+1 < end_row) {
                Ansi::newline();
            }
        }

        // Clear attribute printing
        Ansi::attribute_reset();
    }

    void Screen::_enable_raw_mode() {
      if (tcgetattr(STDIN_FILENO, &Screen::_orig_termios) == -1) {
        throw "tcgetattr failed";
      }

      atexit(Screen::_disable_raw_mode);

      struct termios raw = Screen::_orig_termios;
      raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
      raw.c_oflag &= ~(OPOST);
      raw.c_cflag |= (CS8);
      raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
      raw.c_cc[VMIN] = 0;
      raw.c_cc[VTIME] = 1;

      if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        throw "tcsetattr failed";
      }
    }

    void Screen::_disable_raw_mode() {
        if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &Screen::_orig_termios) == -1) {
          throw "tcsetattr failed";
        }
    }

    Point<unsigned int> Screen::_get_terminal_size() {
        struct winsize ws;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
            throw "Failed to get window size";
        } else {
            assert(ws.ws_row >= 0);
            assert(ws.ws_col >= 0);
            Point<unsigned int> size;
            size.row = static_cast<unsigned int>(ws.ws_row);
            size.column = static_cast<unsigned int>(ws.ws_col);

            return size;
        }
    }

    Input Screen::_get_input() {
        int nread;
        char c;

        Input input;

        // Wait until character is read
        while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
            if (nread == -1 && errno != EAGAIN) {
                throw "Can't read";
            }
        }

        // if escape sequence
        input.push_back(c);
        if(c == '\x1b') {
            // Failed to read a second or third character following escape sequence
            if (read(STDIN_FILENO, &c, 1) != 1) {
                return input;
            }
            input.push_back(c);

            if (read(STDIN_FILENO, &c, 1) != 1) {
                return input;
            }
            input.push_back(c);
            return input;
        }

        return input;
    }

    unsigned int Screen::_instances = 0;
    struct termios Screen::_orig_termios = {};

}
