#include "Node.hpp"

template <int dim>
inline Point<double, dim> Node<dim>::GetPosition()
{
    return this->_position;
}