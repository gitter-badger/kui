#ifndef KUI_ATTR_CHAR_HPP
#define KUI_ATTR_CHAR_HPP

#include <cinttypes>

namespace kui {

    enum class Standard_color: uint8_t {
        black, red, green, yellow, blue, magenta, cyan, white
    };

    class Attr_char {
    public:
        char character;
        Standard_color foreground;
        Standard_color background;
        bool bold;
        bool underline;
    };

}

#endif