#ifndef NODE_CPP
#define NODE_CPP

#include "node.hpp"

template<int dim>
int Node<dim>::_id = 0;

template<int dim>
Node<dim>::Node(const Point<double, dim>& position, unsigned int num_directions) 
    : _position{position}, _num_directions{num_directions}
{
    this->_f.reserve(num_directions);
    this->_f_eq.reserve(num_directions);
    this->_f_next.reserve(num_directions);
    //manca inizializzazione attributi
}

template<int dim>
inline Point<double, dim> Node<dim>::GetPosition() const
{
    return this->_position;
}

template<int dim>
inline int Node<dim>::GetId() const {
    _id++;
    return _id;
}

//getter per distribuzioni

#endif