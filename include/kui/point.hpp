#ifndef KUI_POINT_HPP
#define KUI_POINT_HPP

#include <iostream>

namespace kui {

    template<typename T>
    class Point {
    public:
        Point(): row(), column() {}
        Point(T r, T c): row(r), column(c) {}

        T row;
        T column;
    };

    template<typename T>
    std::ostream & operator<<(std::ostream & stream, const Point<T>& obj) {
        stream << "(" << obj.row << ", " << obj.column << ")";
        return stream;
    }

}

#endif