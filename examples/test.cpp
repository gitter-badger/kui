/*** includes ***/

#include <tui/easy_exception.hpp>
#include <tui/screen.hpp>

int main() {
  auto& screen = tui::Screen::get_screen();

  
  screen.run();

  return 0;
}