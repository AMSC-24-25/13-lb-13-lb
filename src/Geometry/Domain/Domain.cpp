#include "Domain.hpp"



template<int dim>
inline Node<dim> Domain<dim>::GetNodeFromCoordinates(const Point<int, dim>& point)
{
    return this->kPointToNode[point];
}

template<int dim>
inline std::vector<Node<dim>> Domain<dim>::GetNeighbours(const Point<int, dim>& point) {
    return this->_kNeighbourStrategy->GetNeighbours();
}