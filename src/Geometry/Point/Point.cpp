#include "Point.hpp"

template<int dim>
Point<dim>::Point(std::initializer_list<double> pars) {
    if(pars.size() != dim)
        throw std::invalid_argument("Point: Number of coordinates doesn't coincide with dimensions");

    int i = 0;
    for(auto n : pars) {
        this.coordinates[i] = n;
        
        this.hash ^= std::hash<double>()(n) + 0x9e3779b9 + (this.hash << 6) + (this.hash >> 2);
        i++;
    }
}

template<int dim>
double Point<dim>::GetCoordinate(int x) {
    if(x <= -1 || x >= dim)
        throw std::invalid_argument("Point: Requested coordinate out-of-bounds");

    return this.coordinates[x];
}

template<int dim>
void Point<dim>::SetCoordinate(int x, double val) {
    if(x <= -1 || x >= dim)
        throw std::invalid_argument("Point: Requested coordinate out-of-bounds");

    this.coordinates[x] = val;
}

template<int dim>
bool Point<dim>::operator==(const Point<dim>& a) {
    for(int i = 0;i < dim;i++) {
        if(this.get(i) != a.get(i))
            return false;
    }

    return true;
}

template<int dim>
size_t Point<dim>::GetHash() {
    return this.hash;
}

namespace std {
    template <int dim>
    struct hash<Point<dim>> {
        size_t operator()(const Point<dim>& point) const {
            return point.GetHash();
        }
    };
}