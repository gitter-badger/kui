#include <cassert>

#include <algorithm>

#include <kui/screen.hpp>
#include <kui/input.hpp>
#include <kui/logger.hpp>

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

        _on_input_callback = [](auto& s, auto input){};
        _on_update_callback = [](auto &s){};
        _on_resize_callback = [](auto& s, auto prev, auto curr){};
        _on_quit_callback = [](auto& s){};

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
            auto event = _get_input();

            _on_input_callback(*this, event);

            update();
        }
    }

    void Screen::quit() {
        _on_quit_callback(*this);
        _quit = true;
    }

    std::shared_ptr<Box> Screen::add_box() {
        auto box = std::make_shared<Box>(this, [](Box& b){});
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
        _on_resize_callback(*this, prev, curr);

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
        _on_update_callback(*this);

        for(auto& b: _boxes) {
            b->update();
        }

        _clear_screen();
        for(auto& box: _boxes) {
            _update_box(*box);
        }
    }

    void Screen::_update_box(Box &b) {
        auto& buf = b.buffer();
        auto& attrs = b.attributes();

        unsigned int cr = b.row();
        unsigned int cc = b.column();

        using size_type = std::vector<char>::size_type;
        std::string s;

        Attribute curr_attr;

        // Move to proper location
        s.append("\033[" + std::to_string(cr+1) + ";" + std::to_string(cc) + "H");

        if(attrs.rows() > 0 && attrs.columns() > 0) {
            curr_attr = attrs(0, 0);
            s.append("\33[0m");
            if(curr_attr.foreground != Color::none) {
                int i = static_cast<int>(curr_attr.foreground)-1;
                // NOTE: Add 29 because fg black = 30
                i += 30;
                s.append("\33[" + std::to_string(i) + "m");
            }
            if(curr_attr.background != Color::none) {
                int i = static_cast<int>(curr_attr.background)-1;
                // NOTE: Add 29 because bg black = 39
                i += 40;
                s.append("\33[" + std::to_string(i) + "m");
            }
            if(curr_attr.bold) {
                s.append("\33[1m");
            }
            if(curr_attr.underline) {
                s.append("\33[4m");
            }
        }

        for(size_type r = 0; r < buf.rows(); r++) {

            for(size_type c = 0; c < buf.columns(); c++) {
                auto attr = attrs(r, c);
                auto ch = buf(r, c);

                if(attr != curr_attr) {
                    curr_attr = attr;
                    s.append("\33[0m");
                    if(curr_attr.foreground != Color::none) {
                        int i = static_cast<int>(curr_attr.foreground)-1;
                        // NOTE: Add 29 because fg black = 30
                        i += 30;
                        s.append("\33[" + std::to_string(i) + "m");
                    }
                    if(curr_attr.background != Color::none) {
                        int i = static_cast<int>(curr_attr.background)-1;
                        // NOTE: Add 29 because bg black = 39
                        i += 40;
                        s.append("\33[" + std::to_string(i) + "m");
                    }
                    if(curr_attr.bold) {
                        s.append("\33[1m");
                    }
                    if(curr_attr.underline) {
                        s.append("\33[4m");
                    }
                }

                s.push_back(ch);
            }

            if(r+1 < buf.rows()) {
                s.append("\n\r");
            }
        }

        // Clear attribute printing
        s.append("\33[0m");

        KUI_LOG(debug, "Writing string: " << s.size() << " - " << s);

        write(STDOUT_FILENO, s.c_str(), s.size());
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

    void Screen::_move_cursor(unsigned int row, unsigned int column) {
        std::string buf = "\033[" + std::to_string(row+1) + ";" + std::to_string(column) + "H";
        write(STDOUT_FILENO, buf.c_str(), buf.size());
        _cursor.row = row;
        _cursor.column = column;
    }

    void Screen::_clear_screen() {
        write(STDOUT_FILENO, "\033[2J", 4);
    }

    void Screen::_save_cursor() { write(STDOUT_FILENO, "\033[s", 3); }
    void Screen::_load_cursor() { write(STDOUT_FILENO, "\033[u", 3); }

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