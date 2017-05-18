#include <memory>

#include <kui/attribute.hpp>
#include <kui/input.hpp>
#include <kui/logger.hpp>
#include <kui/screen.hpp>

int main() {
    using namespace kui;

    auto& screen = Screen::get_screen();

    unsigned int counter = 0;

    auto title_box = screen.add_box([](auto& b){
        b.move(0, 0);
        b.resize(1, 20);

        b.write(0, 0, "yo heres a title", Attribute(Color::blue, Color::green));
    });

    auto counter_box = screen.add_box([](auto& b){
        b.move(1, 1);
        b.resize(1, 20);

        b.write(0, 0, "X    - Frames");
    });

    counter_box->on_update([&counter](auto& b){
        counter++;
        b.write(0, 0, std::to_string(counter), Attribute(Color::blue, Color::magenta));
    });

    title_box->on_resize([](auto& b, auto prev, auto curr){
        KUI_LOG(debug, "Resized from " << prev << " to " << curr);
    });

    screen.on_input([&counter_box](Screen& s, Input input) {
        if(input == Input_const::ctrl_q) {
            s.quit();
            return;
        }

        if(input == "a") counter_box->move(counter_box->row(), counter_box->column()-1);
        if(input == "d") counter_box->move(counter_box->row(), counter_box->column()+1);
        if(input == "s") counter_box->move(counter_box->row()+1, counter_box->column());
        if(input == "w") counter_box->move(counter_box->row()-1, counter_box->column());

    });

    screen.on_resize([](auto& s, auto prev, auto curr){
        KUI_LOG(debug, "\033[33m Resized screen from " << prev << " to " << curr);
    });

    screen.on_quit([](auto& s) {
        KUI_LOG(debug, "Quitting!");
    });

    screen.run();

    return 0;
}