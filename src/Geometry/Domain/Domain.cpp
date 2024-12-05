#include "Domain.hpp"



template<int dim>
Node<dim> Domain<dim>::GetNodeFromCoordinates(const Point<int, dim>& point)
{
    return this->kPointToNode.at(point);
}

template<int dim>
std::vector<Node<dim>> Domain<dim>::GetNeighbours(const Point<int, dim>& point) {
    std::vector<Node> neighbours;



    return neighbours;
}