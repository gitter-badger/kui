#ifndef KUI_SCREEN_HPP
#define KUI_SCREEN_HPP

#include <termios.h>

#include <functional>
#include <memory>
#include <vector>

#include <kui/input.hpp>
#include <kui/box.hpp>
#include <kui/point.hpp>

namespace kui {

    /**
     * Main screen
     */
    class Screen {
    public:
        // Callback Types
        using Callback_on_input = std::function<void(Screen &, Input)>;
        using Callback_on_update = std::function<void(Screen &)>;
        using Callback_on_quit = std::function<void(Screen &)>;
        
        /**
         * Gets the main screen
         */
        static Screen & get_screen();

        /**
         * Update the display
         */
        void update();

        /**
         * Runs kui app
         */
        void run();

        /**
         * Quit the running kui app
         */
        void quit();

        void on_input(Callback_on_input callback) { _on_input_callback = callback; }
        void on_update(Callback_on_update callback) { _on_update_callback = callback; }
        void on_quit(Callback_on_quit callback) {_on_quit_callback = callback; }

        std::shared_ptr<Box> add_box();
        std::shared_ptr<Box> add_box(Box::Callback_on_init callback);
        bool remove_box(std::shared_ptr<Box>);

        unsigned int rows() const { return _rows; }
        unsigned int columns() const { return _columns; }


    private:
        Screen();
        ~Screen();

        bool _quit;
        unsigned long _total_updates;

        unsigned int _rows;
        unsigned int _columns;

        static void _enable_raw_mode();
        static void _disable_raw_mode();
        void _move_cursor(unsigned int row, unsigned int column);
        void _move_down(unsigned int n);
        void _save_cursor();
        void _load_cursor();

        Point<unsigned int> _cursor;

        Input _get_input();

        // Event Callbacks
        Callback_on_input _on_input_callback;
        Callback_on_update _on_update_callback;
        Callback_on_quit _on_quit_callback;

        std::vector<std::shared_ptr<Box>> _boxes;

        static struct termios _orig_termios;

        static unsigned int _instances;
    };

}

#endif