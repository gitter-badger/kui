#include <cassert>

#include <kui/box.hpp>
#include <kui/screen.hpp>
#include <kui/attribute.hpp>

namespace kui {

    Box::Box(Screen * screen, Callback_on_init callback) {
        assert(screen != nullptr);

        _screen = screen;
        _on_update_callback = [](auto e){};
        _on_move_callback = [](auto e){};
        _on_resize_callback = [](auto e){};

        _background_color = Color::none;
        _foreground_color = Color::none;

        callback(Event_on_init{*this});
    }

    void Box::update() {
        _on_update_callback(Event_on_update{*this});
    }

    void Box::write(unsigned int row, unsigned int column, std::string s, Attribute attr) {
        assert(row < _buffer.rows());
        assert(column < _buffer.columns());

        for(auto c: s) {
            _buffer(row, column) = c;
            _attributes(row, column) = attr;
            column++;
        }
    }

    void Box::move(int row, int column) {
        auto prev = _position;
        _position.row = row;
        _position.column = column;

        _on_move_callback(Event_on_move{*this, prev, _position});
    }

    void Box::resize(unsigned int rows, unsigned int columns) {
        auto prev = Point<unsigned int>(this->rows(), this->columns());
        _buffer.resize(rows, columns);
        _attributes.resize(rows, columns);
        auto curr = Point<unsigned int>(this->rows(), this->columns());

        _on_resize_callback(Event_on_resize{*this, prev, curr});
    }


}