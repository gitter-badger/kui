#include <tui/screen.hpp>

#include <cassert>

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

namespace tui {

  Screen::Screen() {
    assert(Screen::_instances == 0);
    Screen::_instances ++;
    
    Screen::_enable_raw_mode();
  }
  
  Screen::~Screen() {
  
  }
  
  void Screen::run() {
  
  }
  
  Screen & Screen::get_screen() {
    static Screen s;
    return s;
  }
  
  void Screen::_enable_raw_mode() {
      if (tcgetattr(STDIN_FILENO, &Screen::_orig_termios) == -1) {
        throw Screen::Tcgetattr_exception();
      }
      
      atexit(Screen::_disable_raw_mode);
    
      struct termios raw = Screen::_orig_termios;
      raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
      raw.c_oflag &= ~(OPOST);
      raw.c_cflag |= (CS8);
      raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    
      if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        throw Screen::Tcsetattr_exception();
      }
  }
  
  void Screen::_disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &Screen::_orig_termios) == -1) {
      throw Screen::Tcsetattr_exception();  
    }
  }
  
  unsigned int Screen::_instances = 0;
  struct termios Screen::_orig_termios = {};

}