#include <kui/screen.hpp>
#include <kui/logger.hpp>
#include <kui/input.hpp>

int main() {
    using namespace kui;

    auto& screen = Screen::get_screen();

    screen.on_input([](auto s, auto input){

        for(auto c: input.seq) {
            auto i = static_cast<int>(c);
            KUI_LOG(debug, "Got: " << i);
        }

        if(input == Input_const::up) {
            KUI_LOG(debug, "Got UP");
        }

        if(input == "q" || input == Input_const::ctrl_q){
            s->quit();
        }
    });

    screen.on_quit([](auto s){
        KUI_LOG(debug, "Quitting!");
    });

    screen.run();

    return 0;
}