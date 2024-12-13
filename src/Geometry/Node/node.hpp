#ifndef LBM_Node
#define LBM_Node

#include "../Point/point.hpp"

#include <memory>

template<int dim>//aggiungere num_direction oltre a dim per renderlo estendibile(cambiare poi 9 con num_directions)
class Node {
private:
    static int _id;

protected:
    Point<double, dim> _position;
    std::array<double, 9> _f, _f_next, _f_eq;
    double _rho;
    std::array<double, dim> _u;

public:
    Node<dim>(const Point<double, dim>&);

    virtual void Collide() = 0;
    virtual void Propagate() = 0;

    virtual std::unique_ptr<Node<dim>> clone() const = 0;

    Point<double, dim> GetPosition() const;

    int GetId() const;  // need enumeration for hashmaps in partitioning
};

#include "node.cpp"

#endif
