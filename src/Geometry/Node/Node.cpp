#include "Node.hpp"

template<int dim>
Node<dim>::Node(const Point<double, dim>& position) {
    this->_position = position;
}

template <int dim>
inline Point<double, dim> Node<dim>::GetPosition() const
{
    return this->_position;
}