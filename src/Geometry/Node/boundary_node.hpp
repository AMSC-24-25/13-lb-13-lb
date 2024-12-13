#ifndef BOUNDARY_NODE_HPP
#define BOUNDARY_NODE_HPP

#include "node.hpp"

template<int dim>
class BoundaryNode : public Node<dim> {
public:

    explicit BoundaryNode(const Point<double, dim>& position)
        : Node<dim>(position) {}
    
    virtual void BoundaryFunction() = 0;

    virtual void Collide() override = 0;
    virtual void Propagate() override = 0;

    virtual ~BoundaryNode() = default; //non dovrebbe servire
};

#endif