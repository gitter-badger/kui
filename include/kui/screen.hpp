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

    void screen_resize_event();

    /**
     * Main screen
     */
    class Screen {
    public:
        /**
         * Event structs
         * @{
         */
        struct Event_on_input {
            Screen& screen;
            Input input;
        };
        struct Event_on_update {
            Screen& screen;
        };
        struct Event_on_resize {
            Screen& screen;
            Point<unsigned int> prev;
            Point<unsigned int> curr;
        };
        using Event_on_quit = Event_on_update;
        /** @} */

        /**
         * Event callback types
         * @{
         */
        using Callback_on_input = std::function<void(Event_on_input)>;
        using Callback_on_update = std::function<void(Event_on_update)>;
        using Callback_on_resize = std::function<void(Event_on_resize)>;
        using Callback_on_quit = std::function<void(Event_on_quit)>;
        /** @} */
        
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
         * Resize the screen and trigger callbacks.
         * Update after resize.
         * @param row
         * @param column
         */
        void resize(unsigned int row, unsigned int column);

        /**
         * Quit the running kui app
         */
        void quit();

        /**
         * Update respective callback
         * @param callback
         *
         * @{
         */
        void on_input(Callback_on_input callback) { _on_input_callback = callback; }
        void on_update(Callback_on_update callback) { _on_update_callback = callback; }
        void on_resize(Callback_on_resize callback) { _on_resize_callback = callback; }
        void on_quit(Callback_on_quit callback) {_on_quit_callback = callback; }
        /** @} */

        /**
         * Create a box linked to the screen
         * @return
         */
        std::shared_ptr<Box> add_box();

        /**
         * Create a box linked to the screen
         * @param callback Function to be called for initialization purposes
         * @return
         */
        std::shared_ptr<Box> add_box(Box::Callback_on_init callback);

        /**
         * Remove box
         * @param box Box to remove
         * @return
         */
        bool remove_box(std::shared_ptr<Box> box);

        /**
         * Height of the screen
         * @return
         */
        unsigned int rows() const { return _rows; }

        /**
         * Width of the screen
         * @return
         */
        unsigned int columns() const { return _columns; }

        /**
         * Used by signal handler to resize on SIGWINCH
         * @param arg
         */
        static void resize_signal(int arg);

    private:
        Screen();
        ~Screen();

        bool _quit;
        unsigned long _total_updates;

        unsigned int _rows;
        unsigned int _columns;

        static void _enable_raw_mode();
        static void _disable_raw_mode();
        Point<unsigned int> _get_terminal_size();

        Point<unsigned int> _cursor;

        void _update_box(Box & b);

        Input _get_input();

        // Event Callbacks
        Callback_on_input _on_input_callback;
        Callback_on_update _on_update_callback;
        Callback_on_resize _on_resize_callback;
        Callback_on_quit _on_quit_callback;

        std::vector<std::shared_ptr<Box>> _boxes;

        static struct termios _orig_termios;

        static unsigned int _instances;
    };

}

#endif