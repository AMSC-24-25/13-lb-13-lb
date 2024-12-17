#ifndef BOUNDARY_NODE_HPP
#define BOUNDARY_NODE_HPP

#include "node.hpp"

template<int dim>
class BoundaryNode : public Node<dim> {

    protected:
    std::array<double, dim> _boundary_velocity;

    public:
            explicit BoundaryNode(const Point<double, dim>& position, unsigned int num_directions)
        : Node<dim>(position, num_directions), _boundary_velocity{0.0} {} 
        //nel caso in cui abbia una velocità usare UpdateVelocity(sto valutando se modificare permettendo di settarla nel costruttore)
    
        virtual void BoundaryFunction() = 0;

        virtual void Collide() override = 0;
        virtual void Propagate() override = 0;

        void SetDistribution(int index, double distribution) override = 0;

        virtual double GetVelocity() override = 0;
        virtual void UpdateVelocity() override = 0;

        virtual ~BoundaryNode() = default; //non dovrebbe servire
};

#endif