#ifndef KUI_ATTRIBUTE_HPP
#define KUI_ATTRIBUTE_HPP

#include <kui/color.hpp>

namespace kui {

    class Attribute {
    public:
        Attribute(Color fg = Color::none, Color bg = Color::none, bool b = false, bool u = false):
                foreground(fg), background(bg), bold(b), underline(u) {}

        Color foreground;
        Color background;
        bool bold;
        bool underline;

        /**
         * Checks if the attributes are the same
         * @param lhs
         * @param rhs
         * @return true if attributes are the same; false otherwise
         */
        friend bool operator==(const Attribute & lhs, const Attribute & rhs) {
            return lhs.foreground == rhs.foreground &&
                   lhs.background == rhs.background &&
                   lhs.bold == rhs.bold &&
                   lhs.underline == rhs.underline;

        }

        /**
         * Checks if the attributes are the different
         * @param lhs
         * @param rhs
         * @return true if attributes are different; false otherwise
         */
        friend bool operator!=(const Attribute & lhs, const Attribute & rhs) {
            return !(lhs == rhs);
        }
    };

}

#endif