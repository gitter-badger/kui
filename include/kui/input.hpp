#ifndef KUI_KEY_HPP
#define KUI_KEY_HPP

#include <string>

namespace kui {

    /**
     * Terminal input collected as a string
     */
    using Input = std::string;

    /**
     * Common input constants
     */
    class Input_const {
    public:
        static const Input esc;
        static const Input ctrl_q;

        static const Input up;
        static const Input down;
        static const Input left;
        static const Input right;
    };
}

#endif