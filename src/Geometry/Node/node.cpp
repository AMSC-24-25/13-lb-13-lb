#include "node.hpp"

template<int dim>
Node<dim>::Node(const Point<double, dim>& position) {
    this->_position = position;
    //manca inizializzazione attributi
}

template <int dim>
inline Point<double, dim> Node<dim>::GetPosition() const
{
    return this->_position;
}

//getter per distribuzioni