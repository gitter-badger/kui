#ifndef KUI_SCREEN_HPP
#define KUI_SCREEN_HPP

#include <termios.h>

#include <functional>

#include <kui/input.hpp>

namespace kui {

    /**
     * Main screen
     */
    class Screen {
    public:
        // Callback Types
        using Callback_on_input = std::function<void(Screen *, Input)>;
        using Callback_on_quit = std::function<void(Screen *)>;
        
        /**
         * Gets the main screen
         */
        static Screen & get_screen();

        /**
         * Runs kui app
         */
        void run();

        /**
         * Quit the running kui app
         */
        void quit();

        /**
         * Set callback to be called when input is entered
         * @param callback
         */
        void on_input(Callback_on_input callback) { _on_input_callback = callback; }

        /**
         * Set callback to be called when the screen is about to be quit
         * @param callback
         */
        void on_quit(Callback_on_quit callback) {_on_quit_callback = callback; }


    private:
        Screen();
        ~Screen();

        bool _quit;
        unsigned long _total_updates;

        static void _enable_raw_mode();
        static void _disable_raw_mode();

        Input _get_input();

        // Event Callbacks
        Callback_on_input _on_input_callback;
        Callback_on_quit _on_quit_callback;

        static struct termios _orig_termios;

        static unsigned int _instances;
    };

}

#endif