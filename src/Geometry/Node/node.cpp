#ifndef NODE_CPP
#define NODE_CPP

#include "node.hpp"

template<int dim, int num_directions>
int Node<dim, num_directions>::_id = 0;

template<int dim, int num_directions>
Node<dim, num_directions>::Node(const Point<double, dim>& position) {
    this->_position = position;
    //manca inizializzazione attributi
}

template<int dim, int num_directions>
inline Point<double, dim> Node<dim, num_directions>::GetPosition() const
{
    return this->_position;
}

template<int dim, int num_directions>
inline int Node<dim, num_directions>::GetId() const {
    _id++;
    return _id;
}

//getter per distribuzioni

#endif