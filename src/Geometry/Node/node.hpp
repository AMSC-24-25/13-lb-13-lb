#ifndef LBM_Node
#define LBM_Node

#include "../Point/point.hpp"

#include <memory>
#include "metric.hpp"
#include <array>

template<int dim, int num_directions>
class Node {
private:
    static int _id;

protected:
    Point<double, dim> _position;
    std::array<double, num_directions> _f, _f_next, _f_eq;
    double _rho;
    std::array<double, dim> _u;

public:
    Node<dim, num_directions>(const Point<double, dim>&);

    virtual void Collide() = 0;
    virtual void Propagate() = 0;

    virtual std::unique_ptr<Node<dim, num_directions>> clone() const = 0;

    Point<double, dim> GetPosition() const;

    int GetId() const;  // need enumeration for hashmaps in partitioning
};

#include "node.cpp"

#endif
