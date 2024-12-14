#ifndef BOUNCE_BACK_NODE_HPP
#define BOUNCE_BACK_NODE_HPP

#include "boundary_node.hpp"

template<int dim>
class BounceBackNode : public BoundaryNode<dim> {
public:
    
    explicit BounceBackNode(const Point<double, dim>& position, unsigned int num_directions)
        : BoundaryNode<dim>(position, num_directions) {}

    void BoundaryFunction() override;

    void Collide() override;
    void Propagate() override;

    ~BounceBackNode() = default;
};

#endif // BOUNCE_BACK_NODE_HPP
