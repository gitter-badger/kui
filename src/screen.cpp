#include <cassert>

#include <kui/logger.hpp>
#include <kui/screen.hpp>

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
    
    Screen::_enable_raw_mode();
  }
  
  Screen::~Screen() {
    Screen::_instances --;
    assert(Screen::_instances == 0);
  }
  
  void Screen::run() {
    KUI_LOG("Starting to run");
    while(!_quit) {
      auto event = _get_key_event();
      
      if(event.key == Key::escape) KUI_LOG("Escape\tpressed");
      if(event.key == Key::up) KUI_LOG("Up\tpressed");
      if(event.key == Key::down) KUI_LOG("Down\tpressed");
      if(event.key == Key::left) KUI_LOG("Left\tpressed");
      if(event.key == Key::right) KUI_LOG("Right\tpressed"); 
      
      if(event.key == Key::q && event.ctrl == true) {
        KUI_LOG("Got CTRL + Q to quit");
        quit();      
      }
    }
    KUI_LOG("Ending run");
  }
  
  void Screen::quit() {
    KUI_LOG("Triggered quit");
    _quit = true;
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
      raw.c_cc[VMIN] = 0;
      raw.c_cc[VTIME] = 1;
    
      if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        throw Screen::Tcsetattr_exception();
      }
  }
  
  void Screen::_disable_raw_mode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &Screen::_orig_termios) == -1) {
      throw Screen::Tcsetattr_exception();  
    }
  }
  
  Key_event Screen::_get_key_event() {
      int nread;
      char c;
      
      // Wait until character is read
      while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) {
          throw "Can't read";
        }
      }
      
      // if escape sequence 
      if(c == '\x1b') {
        char seq[3];
        
        // Failed to read a second or third character following escape sequence
        if (read(STDIN_FILENO, &seq[0], 1) != 1) return Key_event(Key::escape);
        if (read(STDIN_FILENO, &seq[1], 1) != 1) return Key_event(Key::escape);
        
        if (seq[0] == '[') {
          switch (seq[1]) {
            case 'A': return Key_event(Key::up);
            case 'B': return Key_event(Key::down);
            case 'C': return Key_event(Key::right);
            case 'D': return Key_event(Key::left);
            
            case 'H': return Key_event(Key::home);
            case 'F': return Key_event(Key::end);
          }
        }
        return Key_event(Key::escape);
      }
       
      switch(c) {
        case 8: return Key_event(Key::backspace);
        case 9: return Key_event(Key::tab);
        
        case 17: return Key_event(Key::q, false, true);
        
      }
    
  }
  
  unsigned int Screen::_instances = 0;
  struct termios Screen::_orig_termios = {};

}