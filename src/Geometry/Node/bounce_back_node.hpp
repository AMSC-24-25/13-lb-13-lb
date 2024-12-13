#ifndef BOUNCE_BACK_NODE_HPP
#define BOUNCE_BACK_NODE_HPP

#include "boundary_node.hpp"

template<int dim, int num_directions>
class BounceBackNode : public BoundaryNode<dim, num_directions> {
public:
    
    explicit BounceBackNode(const Point<double, dim>& position)
        : BoundaryNode<dim, num_directions>(position) {}

    void BoundaryFunction() override;

    void Collide() override;
    void Propagate() override;

    ~BounceBackNode() = default;
};

#endif 
