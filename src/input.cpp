#include <kui/input.hpp>

namespace kui {
    const Input Input_const::esc = "\x1b";
    const Input Input_const::ctrl_q = "\x11";

    const Input Input_const::up = "\x1b[A";
    const Input Input_const::down = "\x1b[B";
    const Input Input_const::left = "\x1b[D";
    const Input Input_const::right = "\x1b[C";
}