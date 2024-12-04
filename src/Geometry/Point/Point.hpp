#ifndef LBM_Point
#define LBM_Point

#include <array>
#include <initializer_list>
#include <stdexcept>
#include <functional>

template<int dim>
class Point {
private:
    std::array<int, dim> coordinates;
    size_t hash;

public:
    Point(std::initializer_list<double>);

    double GetCoordinate(int);
    void SetCoordinate(int, double);

    size_t GetHash();

    bool operator==(const Point&);
};

#endif