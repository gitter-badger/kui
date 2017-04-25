#ifndef TUI_SCREEN_HPP
#define TUI_SCREEN_HPP

#include <termios.h>

#include <tui/easy_exception.hpp>

namespace tui {

  class Screen {
  public:
    static Screen & get_screen();
  
    void run();
    void exit();

    TUI_EASY_EXCEPTION(Tcsetattr_exception, "tcsetattr failed");
    TUI_EASY_EXCEPTION(Tcgetattr_exception, "tcgetattr failed");
    
  private:
    Screen();
    ~Screen();
  
    static void _enable_raw_mode();
    static void _disable_raw_mode();
    
    static struct termios _orig_termios;
    
    static unsigned int _instances;
  };

}

#endif