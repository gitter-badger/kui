#include <kui/easy_exception.hpp>
#include <kui/screen.hpp>

int main() {
  using namespace kui;

  auto& screen = Screen::get_screen();

  
  screen.run();

  return 0;
}