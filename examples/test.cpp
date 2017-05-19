#include <memory>

#include <kui/attribute.hpp>
#include <kui/input.hpp>
#include <kui/logger.hpp>
#include <kui/screen.hpp>

int main() {
    using namespace kui;

    auto& screen = Screen::get_screen();

    unsigned int counter = 0;

    auto title_box = screen.add_box([](auto e){
        e.box.move(0, 0);
        e.box.resize(1, 20);

        e.box.write(0, 0, "yo heres a title", Attribute(Color::blue, Color::green));
    });

    auto counter_box = screen.add_box([](auto e){
        e.box.move(1, 1);
        e.box.resize(1, 20);

        e.box.write(0, 0, "X    - Frames");
    });

    counter_box->on_update([&counter](auto e){
        counter++;
        e.box.write(0, 0, std::to_string(counter), Attribute(Color::blue, Color::magenta));
    });

    title_box->on_resize([](auto e){
        KUI_LOG(debug, "Resized from " << e.prev << " to " << e.curr);
    });

    screen.on_input([&counter_box](auto e) {
        if(e.input == Input_const::ctrl_q) {
            e.screen.quit();
            return;
        }

        if(e.input == "a") counter_box->move(counter_box->row(), counter_box->column()-1);
        if(e.input == "d") counter_box->move(counter_box->row(), counter_box->column()+1);
        if(e.input == "s") counter_box->move(counter_box->row()+1, counter_box->column());
        if(e.input == "w") counter_box->move(counter_box->row()-1, counter_box->column());

    });

    screen.on_resize([](auto e){
        KUI_LOG(debug, "Resized screen from " << e.prev << " to " << e.curr);
    });

    screen.on_quit([](auto e) {
        KUI_LOG(debug, "Quitting!");
    });

    screen.run();

    return 0;
}
