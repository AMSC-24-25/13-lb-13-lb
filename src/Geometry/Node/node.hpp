#ifndef LBM_Node
#define LBM_Node

#include "../Point/point.hpp"

#include <memory>

template<int dim>
class Node {
private:
    Point<double, dim> _position;

public:
    Node<dim>(const Point<double, dim>&);

    virtual void Collide() = 0;
    virtual void Propagate() = 0;

    virtual std::unique_ptr<Node<dim>> clone() const = 0;

    Point<double, dim> GetPosition() const;
};

// template instances
template class Node<2>;
template class Node<3>;

#endif
