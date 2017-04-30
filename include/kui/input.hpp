#ifndef KUI_KEY_HPP
#define KUI_KEY_HPP

#include <string>

namespace kui {

    /**
     * Represents input in the form of character sequences
     */
    class Input {
    public:

        /**
         * Constructors
         * @{
         */
        Input(): seq("") {}
        Input(std::string sequence): seq(sequence) {}
        Input(const char * sequence): seq(sequence) {}
        /** @} */

        /**
         * Character sequence
         */
        std::string seq;

        friend bool operator==(const Input & lhs, const Input & rhs) { return lhs.seq == rhs.seq; }
    };

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