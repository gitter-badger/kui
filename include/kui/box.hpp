#ifndef KUI_BOX_HPP
#define KUI_BOX_HPP

#include <chrono>
#include <functional>

#include <optional.hpp>

#include <kui/vector2d.hpp>
#include <kui/point.hpp>

namespace kui {

    class Screen;

    class Box {
    public:
        using Callback_on_init = std::function<void(Box &)>;
        using Callback_on_update = std::function<void(Box &)>;
        using Callback_on_move = std::function<void(Box&, Point<int>, Point<int>)>;
        using Callback_on_resize = std::function<void(Box&, Point<unsigned int>, Point<unsigned int>)>;

        Box(Screen * screen, Callback_on_init callback);

        /**
         * Get access to the parent screen
         * @return
         */
        Screen* screen() const { return _screen; }

        /**
         * Call update callback
         */
        void update();

        void on_update(Callback_on_update callback) { _on_update_callback = callback; }
        void on_move(Callback_on_move callback) { _on_move_callback = callback; }
        void on_resize(Callback_on_resize callback) { _on_resize_callback = callback; }

        /**
         * Get access to internal character buffer
         * @return
         */
        const Vector_2d<char> & buffer() const { return _buffer; }

        /**
         * Write a string to the internal buffer
         * @param row
         * @param column
         * @param s
         */
        void write(unsigned int row, unsigned int column, std::string s);

        /**
         * Gets the y position of the box
         * @return
         */
        unsigned int row() const { return _position.row; }

        /**
         * Gets the x position of the box
         * @return
         */
        unsigned int column () const { return _position.column; }

        /**
         * Gets the height of the box
         * @return
         */
        unsigned int rows() const { return _buffer.rows(); }

        /**
         * Gets the width of the box
         * @return
         */
        unsigned int columns() const { return _buffer.columns(); }

        /**
         * Move the box and call on_move callback
         * @param row
         * @param column
         */
        void move(int row, int column);

        /**
         * Resize the box and call on_resize callback
         * @param rows
         * @param columns
         */
        void resize(unsigned int rows, unsigned int columns);


    private:
        Screen * _screen;

        Vector_2d<char> _buffer;
        Point<int> _position;

        Callback_on_update _on_update_callback;
        Callback_on_move _on_move_callback;
        Callback_on_resize _on_resize_callback;
    };

}

#endif