#ifndef BOUNCE_BACK_NODE_HPP
#define BOUNCE_BACK_NODE_HPP

#include "boundary_node.hpp"

template<int dim>
class BounceBackNode : public BoundaryNode<dim> {
public:
    
    BounceBackNode(const Point<double, dim>& position)
        : BoundaryNode<dim>(position) {} //forse è meglio che sia explicit

    void BoundaryFunction() override;

    void Collide() override;
    void Propagate() override;
};

#endif 
