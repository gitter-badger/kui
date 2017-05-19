#ifndef KUI_BOX_HPP
#define KUI_BOX_HPP

#include <chrono>
#include <functional>

#include <kui/color.hpp>
#include <kui/point.hpp>
#include <kui/vector2d.hpp>
#include <kui/attribute.hpp>

namespace kui {

    class Screen;

    /**
     * An individual, drawable container
     */
    class Box {
    public:
        /**
         * Event structs
         * @{
         */
        struct Event_on_init {
            Box & box;
        };
        using Event_on_update = Event_on_init;
        struct Event_on_move {
            Box& box;
            Point<int> prev;
            Point<int> curr;
        };
        struct Event_on_resize {
            Box& box;
            Point<unsigned int> prev;
            Point<unsigned int> curr;
        };
        /** @} */

        /**
         * Event callback types
         * @{
         */
        using Callback_on_init = std::function<void(Event_on_init)>;
        using Callback_on_update = std::function<void(Event_on_update)>;
        using Callback_on_move = std::function<void(Event_on_move)>;
        using Callback_on_resize = std::function<void(Event_on_resize)>;
        /** @} */

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
         * @param attr
         */
        void write(unsigned int row, unsigned int column, std::string s, Attribute attr = Attribute());

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

        /**
         * Gets the background color
         * @return
         */
        Color background_color() const { return _background_color; }

        /**
         * Sets the background color
         * @param c the color to set to
         */
        void background_color(Color c) { _background_color = c; }

        /**
         * Gets the foreground color
         * @return
         */
        Color foreground_color() const { return _foreground_color; }

        /**
         * Sets the foreground color
         * @param c the color to set to
         */
        void foreground_color(Color c) { _foreground_color = c; }

        /**
         * Get a constant reference to the attributes
         * @return
         */
        const Vector_2d<Attribute> & attributes() const { return _attributes; }

        /**
         * Get an attribute at a specific row/column
         * @param row
         * @param column
         * @return
         */
        Attribute& attribute(unsigned int row, unsigned int column) { return _attributes(row, column); }

        /**
         * Get a constant attribute at a specific row/column
         * @param row
         * @param column
         * @return
         */
        const Attribute& attribute(unsigned int row, unsigned int column) const { return _attributes(row, column); }


    private:
        Screen * _screen;

        Vector_2d<char> _buffer;
        Vector_2d<Attribute> _attributes;

        Point<int> _position;

        Callback_on_update _on_update_callback;
        Callback_on_move _on_move_callback;
        Callback_on_resize _on_resize_callback;

        Color _background_color;
        Color _foreground_color;
    };

}

#endif
