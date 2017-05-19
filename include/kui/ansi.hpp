#ifndef KUI_ANSI_BUILDER_HPP
#define KUI_ANSI_BUILDER_HPP

#include <string>

#include <kui/color.hpp>

namespace kui {

    /**
     * Helper class to build ANSI
     */
    class Ansi {
    public:

        /**
         * Perform a carriage return and newline
         */
        static void newline();

        /**
         * Generate ANSI to move cursor position
         * @param row
         * @param column
         * @return
         */
        static void move_cursor(unsigned int row, unsigned int column);

        /**
         * Generate ANSI to save cursor position
         * @return
         */
        static void save_cursor();

        /**
         * Generate ANSI to load saved cursor position
         * @return
         */
        static void load_cursor();

        /**
         * Generate ANSI to clear the screen and move cursor to (0, 0)
         * @return
         */
        static void clear_screen();

        /**
         * Generate ANSI to reset the text attributes
         * @return
         */
        static void attribute_reset();

        /**
         * Generate ANSI to enable bold text
         * @return
         */
        static void attribute_bold();

        /**
         * Generate ANSI to enable underline text
         * @return
         */
        static void attribute_underline();

        /**
         * Generate ANSI to enable foreground color.
         * @param c
         * @return
         */
        static void attribute_foreground(Color c);

        /**
         * Generate ANSI to enable background color
         * @param c
         * @return
         */
        static void attribute_background(Color c);

        static void write_stdout(const std::string & s);
        static void write_stdout(char c);
    };

}

#endif
