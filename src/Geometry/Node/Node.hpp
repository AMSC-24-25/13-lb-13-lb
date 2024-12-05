#ifndef LBM_Node
#define LBM_Node

#include "../Point/Point.hpp"

template<int dim>
class Node {
private:
    const Point<double, dim> _position;

public:
    Node<dim>(const Point<double, dim>& position) : _position(position) = 0;

    virtual void Collide() = 0;
    virtual void Propagate() = 0;

    Point<double, dim> GetPosition();
};

#endif
