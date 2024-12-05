#ifndef LBM_Point
#define LBM_Point

#include <array>
#include <initializer_list>
#include <stdexcept>
#include <functional>
#include <type_traits>

template<typename T, int dim>
class Point {
private:
    static_assert(dim > 0, "Point: dimensions have to be greater than 0");

    std::array<T, dim> coordinates;
    size_t hash;

public:
    Point(std::initializer_list<double>);
    Point(const Point<T, dim>& other) : coordinates(other.coordinates), hash(other.hash) = 0;

    T GetCoordinate(int);
    void SetCoordinate(int, T);

    size_t GetHash();

    bool operator==(const Point<T, dim>&);
};

#endif