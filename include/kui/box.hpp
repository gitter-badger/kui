#ifndef KUI_BOX_HPP
#define KUI_BOX_HPP

#include <chrono>
#include <functional>

namespace kui {

    class Screen;

    class Box {
    public:
        Box(Screen * screen);

        void init();

        using Callback_on_init = std::function<void(Box &)>;
        using Callback_on_update = std::function<void(Box &)>;

        void on_init(Callback_on_init callback) { _on_init_callback = callback; }
        void on_update(Callback_on_update callback) { _on_update_callback = callback; }

        void write_c(char c);
        void write_str(std::string s);

    private:
        Screen * _screen;

        Callback_on_init _on_init_callback;
        Callback_on_update _on_update_callback;

        unsigned int _width;
        unsigned int _height;
    };

}

#endif