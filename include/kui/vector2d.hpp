#ifndef KUI_VECTOR2D_HPP
#define KUI_VECTOR2D_HPP

#include <cassert>

#include <vector>

namespace kui {

    template<typename T>
    class Vector_2d {
    public:
        using reference = typename std::vector<T>::reference;
        using const_reference = typename std::vector<T>::const_reference;

        Vector_2d(): _rows(0), _columns(0), _data() {}
        Vector_2d(unsigned int rows, unsigned int columns, T val = T()) {
            _rows = rows;
            _columns = columns;
            _data = std::vector<T>(_rows * _columns, val);
        }
        Vector_2d(unsigned int rows, unsigned int columns, const std::initializer_list<T> & list) {
            assert((rows * columns) == list.size());
            _rows = rows;
            _columns = columns;
            _data.insert(_data.begin(), list.begin(), list.end());
        }

        reference operator()(unsigned int row, unsigned int column) {
            assert(row < _rows);
            assert(column < _columns);
            return _data[(row * _columns) + column];
        }
        const_reference operator()(unsigned int row, unsigned int column) const {
            assert(row < _rows);
            assert(column < _columns);
            return _data[(row * _columns) + column];
        }

        void resize(unsigned int rows, unsigned int columns, T val = T()) {
            auto old = *this;

            *this = Vector_2d(rows, columns, val);

            for(unsigned int y = 0; y < std::min(old._rows, _rows); y++) {
                for(unsigned int x = 0; x < std::min(old._columns, _columns); x++) {
                    (*this)(y, x) = old(y, x);
                }
            }
        }

        const unsigned int rows() const { return _rows; }
        const unsigned int columns() const { return _columns; }

    private:
        unsigned int _rows;
        unsigned int _columns;
        std::vector<T> _data;
    };

}

#endif