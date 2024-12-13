#ifndef BOUNDARY_NODE_HPP
#define BOUNDARY_NODE_HPP

#include "node.hpp"

template<int dim, int num_directions>
class BoundaryNode : public Node<dim, num_directions> {
public:

    explicit BoundaryNode(const Point<double, dim>& position)
        : Node<dim, num_directions>(position) {}
    
    virtual void BoundaryFunction() = 0;

    virtual void Collide() override = 0;
    virtual void Propagate() override = 0;

    virtual ~BoundaryNode() = default; //non dovrebbe servire
};

#endif