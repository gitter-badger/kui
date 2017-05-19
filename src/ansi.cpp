#include <stdio.h>
#include <unistd.h>

#include <kui/ansi.hpp>

namespace kui {

    void Ansi::newline() {
        write(STDOUT_FILENO, "\n\r", 2);
    }

    void Ansi::move_cursor(unsigned int row, unsigned int column) {
        const std::string s = "\033[" + std::to_string(row+1) + ";" + std::to_string(column+1) + "H";
        write(STDOUT_FILENO, s.c_str(), s.size());
    }

    void Ansi::save_cursor() {
        write(STDOUT_FILENO, "\033[s", 3);
    }

    void Ansi::load_cursor() {
        write(STDOUT_FILENO, "\033[u", 3);
    }

    void Ansi::clear_screen() {
        write(STDOUT_FILENO, "\033[2J", 4);
    }

    void Ansi::attribute_reset() {
        write(STDOUT_FILENO, "\033[0m", 4);
    }

    void Ansi::attribute_bold() {
        write(STDOUT_FILENO, "\033[1m", 4);
    }

    void Ansi::attribute_underline() {
        write(STDOUT_FILENO, "\033[4m", 4);
    }

    void Ansi::attribute_foreground(Color c) {
        if(c == Color::none) return;
        const std::string s = "\033[" + std::to_string(static_cast<int>(c)-1+30) + "m";
        write(STDOUT_FILENO, s.c_str(), s.size());
    }

    void Ansi::attribute_background(Color c) {
        if(c == Color::none) return;
        const std::string s = "\033[" + std::to_string(static_cast<int>(c)-1+40) + "m";
        write(STDOUT_FILENO, s.c_str(), s.size());
    }

    void Ansi::write_stdout(const std::string & s) {
        write(STDOUT_FILENO, s.c_str(), s.size());
    }

    void Ansi::write_stdout(char c) {
        write(STDOUT_FILENO, &c, 1);
    }

}
