#include "Domain.hpp"


template<int dim>
Domain<dim>::Domain(const std::string& path) {

}

template<int dim>
inline Node<dim> Domain<dim>::GetNodeFromCoordinates(const Point<int, dim>& point) const
{
    return this->kPointToNode[point];
}

template<int dim>
inline std::vector<Node<dim>> Domain<dim>::GetNeighbours(const Point<int, dim>& point) const {
    return this->_kNeighboursStrategy->GetNeighbours(this, point);
}