#ifndef KUI_SCREEN_HPP
#define KUI_SCREEN_HPP

#include <termios.h>

#include <kui/key_event.hpp>
#include <kui/easy_exception.hpp>

namespace kui {

    /**
     * Main screen
     */
    class Screen {
    public:
        static Screen & get_screen();

        /**
         * Runs kui app
         */
        void run();

        /**
         * Quit the running kui app
         */
        void quit();

        KUI_EASY_EXCEPTION(Tcsetattr_exception, "tcsetattr failed");
        KUI_EASY_EXCEPTION(Tcgetattr_exception, "tcgetattr failed");

    private:
        Screen();
        ~Screen();

        bool _quit;

        static void _enable_raw_mode();
        static void _disable_raw_mode();

        Key_event _get_key_event();

        static struct termios _orig_termios;

        static unsigned int _instances;
    };

}

#endif