#include "Domain.hpp"


template<int dim>
Domain<dim>::Domain(const std::string& path) {

}

template<int dim>
inline Node<dim> Domain<dim>::GetNodeFromCoordinates(const Point<int, dim>& point) const
{
    return this->_k_point_to_node[point];
}

template<int dim>
inline std::vector<Node<dim>> Domain<dim>::GetNeighbours(const Point<int, dim>& point) const {
    return this->_k_neighbours_strategy->GetNeighbours(this, point);
}