#include <cassert>

#include <kui/box.hpp>
#include <kui/screen.hpp>

namespace kui {

    Box::Box(Screen * screen, Callback_on_init callback) {
        assert(screen != nullptr);

        _screen = screen;
        _on_update_callback = [](auto& b){};
        _on_move_callback = [](auto& b, auto prev, auto curr){};
        _on_resize_callback = [](auto& b, auto prev, auto curr){};

        callback(*this);
    }

    void Box::update() {
        _on_update_callback(*this);
    }

    void Box::write(unsigned int row, unsigned int column, std::string s) {
        assert(row < _buffer.rows());
        assert(column < _buffer.columns());

        for(auto c: s) {
            _buffer(row, column) = c;
            column++;
        }
    }

    void Box::move(int row, int column) {
        auto prev = _position;
        _position.row = row;
        _position.column = column;

        _on_move_callback(*this, prev, _position);
    }

    void Box::resize(unsigned int rows, unsigned int columns) {
        auto prev = Point<unsigned int>(this->rows(), this->columns());
        _buffer.resize(rows, columns);
        auto curr = Point<unsigned int>(this->rows(), this->columns());

        _on_resize_callback(*this, prev, curr);
    }


}