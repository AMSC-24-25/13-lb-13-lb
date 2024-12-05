#include "Point.hpp"

template<typename T, int dim>
Point<T, dim>::Point(std::initializer_list<double> pars) {
    if(pars.size() != dim)
        throw std::invalid_argument("Point: Number of coordinates doesn't coincide with dimensions");

    int i = 0;
    for(auto n : pars) {
        this.coordinates[i] = n;
        
        this.hash ^= std::hash<double>()(n) + 0x9e3779b9 + (this.hash << 6) + (this.hash >> 2);
        i++;
    }
}

template<typename T, int dim>
T Point<T, dim>::GetCoordinate(int x) {
    if(x <= -1 || x >= dim)
        throw std::invalid_argument("Point: Requested coordinate out-of-bounds");

    return this.coordinates[x];
}

template<typename T, int dim>
void Point<T, dim>::SetCoordinate(int x, T val) {
    if(x <= -1 || x >= dim)
        throw std::invalid_argument("Point: Requested coordinate out-of-bounds");

    this.coordinates[x] = val;
}

template<typename T, int dim>
bool Point<T, dim>::operator==(const Point<T, dim>& a) {
    for(int i = 0;i < dim;i++) {
        if(this.get(i) != a.get(i))
            return false;
    }

    return true;
}

template<typename T, int dim>
size_t Point<T, dim>::GetHash() {
    return this.hash;
}

namespace std {
    template <typename T, int dim>
    struct hash<Point<T, dim>> {
        size_t operator()(const Point<dim>& point) const {
            return point.GetHash();
        }
    };
}