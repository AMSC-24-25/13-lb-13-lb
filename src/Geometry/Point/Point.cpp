#include "Point.hpp"

template<typename T, int dim>
Point<T, dim>::Point(std::initializer_list<T> pars) {
    if(pars.size() != dim)
        throw std::invalid_argument("Point: Number of coordinates doesn't coincide with dimensions");

    int i = 0;
    for(auto n : pars) {
        this->_coordinates[i] = n;
        
        this->_hash ^= std::hash<T>()(n) + 0x9e3779b9 + (this->_hash << 6) + (this->_hash >> 2);
        i++;
    }
}

template<typename T, int dim>
Point<T, dim>::Point(const std::vector<T>& v) {
    for(int i = 0;i < dim;i++) {
        this->_coordinates[i] = v[i];
        
        this->_hash ^= std::hash<T>()(n) + 0x9e3779b9 + (this->_hash << 6) + (this->_hash >> 2);
        i++;
    }
}

template<typename T, int dim>
Point<T, dim>::Point(const Point<T, dim>& point, const std::array<T, dim>& variations) {
    for(int i = 0;i < dim;i++) {
        T x = point._coordinates[i] + variations[i];
        this->_coordinates[i] = x;
        
        this->_hash ^= std::hash<T>()(x) + 0x9e3779b9 + (this->_hash << 6) + (this->_hash >> 2);
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
bool Point<T, dim>::operator==(const Point<T, dim>& a) {
    for(int i = 0;i < dim;i++) {
        if(this->_coordinates[i] != a._coordinates[i])
            return false;
    }

    return true;
}

template<typename T, int dim>
inline size_t Point<T, dim>::GetHash() {
    return this->_hash;
}

namespace std {
    template <typename T, int dim>
    struct hash<Point<T, dim>> {
        size_t operator()(const Point<dim>& point) const {
            return point->GetHash();
        }
    };
}