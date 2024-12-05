#include "Node.hpp"

template<int dim>
auto Node<dim>::GetPosition() {
    return this->_position;
}