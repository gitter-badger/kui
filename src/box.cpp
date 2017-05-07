#include <cassert>

#include <kui/box.hpp>
#include <kui/screen.hpp>

namespace kui {

    Box::Box(Screen * screen) {
        assert(screen != nullptr);

        _screen = screen;
        _on_init_callback = [](auto b){};
        _on_update_callback = [](auto b){};
    }

    void Box::init() {
        _on_init_callback(*this);
    }

}