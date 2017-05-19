#ifndef KUI_POINT_HPP
#define KUI_POINT_HPP

#include <iostream>

namespace kui {

    /**
     * Point represented by a row and column
     * @tparam T
     */
    template<typename T>
    class Point {
    public:
        Point(): row(), column() {}
        Point(T r, T c): row(r), column(c) {}

        T row;
        T column;
    };

    /**
     * Output point to a stream as (r, c)
     * @tparam T
     * @param stream
     * @param obj
     * @return
     */
    template<typename T>
    std::ostream & operator<<(std::ostream & stream, const Point<T>& obj) {
        stream << "(" << obj.row << ", " << obj.column << ")";
        return stream;
    }

}

#endif