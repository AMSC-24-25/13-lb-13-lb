#ifndef INNER_NODE_HPP
#define INNER_NODE_HPP

#include "../Geometry/Node/node.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    class InnerNode : public Node<dim> {
    public:
        explicit InnerNode(const Point<double, dim>& position, int num_distributions)
            : Node<dim>(position), _f(num_distributions, 0.0), _f_eq(num_distributions, 0.0) {}

        virtual void Collide() override;
        virtual void Propagate() override;

        std::vector<double> _f;
        std::vector<double> _f_eq;
    };

}

#endif