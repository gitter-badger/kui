#include <memory>

#include <kui/screen.hpp>
#include <kui/logger.hpp>
#include <kui/input.hpp>

int main() {
    using namespace kui;

    auto& screen = Screen::get_screen();

    auto title_box = screen.add_box([](Box& b){
        b.move(0, 0);
        b.resize(200, 100);

        b.write_str(0, 0, "yo heres a title");
    });

    title_box->on_resize([](auto& b, auto prev, auto curr){
        KUI_LOG(debug, "Resized from " << prev << " to " << curr);
    });

    screen.on_input([](Screen& s, Input input) {
        if(input == Input_const::ctrl_q) {
            s.quit();
        }
    });

    screen.on_quit([](auto& s) {
        KUI_LOG(debug, "Quitting!");
    });

    screen.run();

    return 0;
}