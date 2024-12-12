#ifndef LBM_Node
#define LBM_Node

#include "../Point/point.hpp"

#include <memory>
#include "metric.hpp"
#include <array>

template<int dim>//aggiungere num_direction oltre a dim per renderlo estendibile(cambiare poi 9 con num_directions)
class Node {
protected:
    Point<double, dim> _position;
    std::array<double, 9> _f, _f_next, _f_eq;
    double _rho;
    std::array<double, dim> _u;
    MetricNeighbour<dim>* metric;

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
