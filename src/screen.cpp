#include <cassert>

#include <algorithm>

#include <kui/screen.hpp>
#include <kui/input.hpp>

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

namespace kui {

    Screen::Screen() {
        assert(Screen::_instances == 0);
        Screen::_instances ++;
        _quit = false;
        _total_updates = 0;

        _on_input_callback = [](auto& s, auto input){};
        _on_quit_callback = [](auto& s){};

        Screen::_enable_raw_mode();
    }

    Screen::~Screen() {
    Screen::_instances --;
    assert(Screen::_instances == 0);
    }

    void Screen::run() {
        while(!_quit) {
            auto event = _get_input();

            _on_input_callback(*this, event);
        }
    }

    void Screen::quit() {
        _on_quit_callback(*this);
        _quit = true;
    }

    std::shared_ptr<Box> Screen::add_box() {
        auto box = std::make_shared<Box>(this);
        _boxes.push_back(box);
        box->init();
        return box;
    }

    bool Screen::remove_box(std::shared_ptr<Box> box) {
        auto box_it = std::find(_boxes.begin(), _boxes.end(), box);
        if(box_it == _boxes.end()) return false;

        _boxes.erase(box_it);
        return true;
    }

    Screen & Screen::get_screen() {
        static Screen s;
        return s;
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
        input.seq.push_back(c);
        if(c == '\x1b') {
            // Failed to read a second or third character following escape sequence
            if (read(STDIN_FILENO, &c, 1) != 1) {
                return input;
            }
            input.seq.push_back(c);

            if (read(STDIN_FILENO, &c, 1) != 1) {
                return input;
            }
            input.seq.push_back(c);
            return input;
        }

        return input;
    }

    unsigned int Screen::_instances = 0;
    struct termios Screen::_orig_termios = {};

}