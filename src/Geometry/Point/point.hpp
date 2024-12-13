#ifndef LBM_Point
#define LBM_Point

#include <array>
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <functional>
#include <type_traits>

template<typename T, int dim>
class Point {
private:
    static_assert(dim > 0, "Point: dimensions have to be greater than 0");

    std::array<T, dim> _coordinates;
    size_t _hash;

public:
    Point() {}
    Point(std::initializer_list<T>);
    Point(const std::vector<T>&);
    Point(const Point<T, dim>&, const std::array<T, dim>&);     // possible hashmap, but there would be an underlying array of zeros anyway

    T GetCoordinate(int) const;

    size_t GetHash() const;

    bool operator==(const Point<T, dim>&) const;
};

#include "point.cpp"

#endif