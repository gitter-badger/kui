#include <kui/screen.hpp>
#include <kui/logger.hpp>
#include <kui/input.hpp>

int main() {
    using namespace kui;

    auto& screen = Screen::get_screen();

    auto title_box = screen.add_box();

    screen.on_quit([](auto& s) {
        KUI_LOG(debug, "Quitting!");
    });

    screen.run();

    return 0;
}