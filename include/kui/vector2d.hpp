#ifndef KUI_VECTOR2D_HPP
#define KUI_VECTOR2D_HPP

#include <cassert>

#include <vector>

namespace kui {

    template<typename T>
    class Vector_2d {
    public:
        using value_type = typename std::vector<T>::value_type;
        using size_type = typename std::vector<T>::size_type;
        using reference = typename std::vector<T>::reference;
        using const_reference = typename std::vector<T>::const_reference;

        Vector_2d(): _rows(0), _columns(0), _data() {}
        Vector_2d(size_type rows, size_type columns, T val = T()) {
            _rows = rows;
            _columns = columns;
            _data = std::vector<T>(_rows * _columns, val);
        }
        Vector_2d(size_type rows, size_type columns, const std::initializer_list<T> & list) {
            assert((rows * columns) == list.size());
            _rows = rows;
            _columns = columns;
            _data.insert(_data.begin(), list.begin(), list.end());
        }

        reference operator()(size_type row, size_type column) {
            assert(row < _rows);
            assert(column < _columns);
            return _data[(row * _columns) + column];
        }
        const_reference operator()(size_type row, size_type column) const {
            assert(row < _rows);
            assert(column < _columns);
            return _data[(row * _columns) + column];
        }

        void resize(size_type rows, size_type columns, T val = T()) {
            auto old = *this;

            *this = Vector_2d(rows, columns, val);

            for(size_type y = 0; y < std::min(old._rows, _rows); y++) {
                for(size_type x = 0; x < std::min(old._columns, _columns); x++) {
                    (*this)(y, x) = old(y, x);
                }
            }
        }

        const size_type rows() const { return _rows; }
        const size_type columns() const { return _columns; }

    private:
        size_type _rows;
        size_type _columns;
        std::vector<T> _data;
    };

}

#endif