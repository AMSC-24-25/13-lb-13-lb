#ifndef LBM_Node
#define LBM_Node

#include "../Point/point.hpp"

#include <memory>
#include <array>

template<int dim>
class Node {
private:
    static int _id_counter;

protected:
    Point<double, dim> _position;
    std::vector<double> _f, _f_next, _f_eq;
    double _rho;
    std::array<double, dim> _u;
    const unsigned int _num_directions;
    int _id;

    // temporary solution to neighbours problem
    std::vector<std::shared_ptr<Node<dim>>> _neighbours;

public:
    Node(const Point<double, dim>&, unsigned int num_directions);

    virtual void Collide() = 0;
    virtual void Propagate() = 0;

    virtual std::unique_ptr<Node<dim>> clone() const = 0;

    Point<double, dim> GetPosition() const;

    std::vector<std::shared_ptr<Node<dim>>> GetNeighbours();
    void SetNeighbours(std::vector<std::shared_ptr<Node<dim>>>);

    int GetId() const;  // need enumeration for hashmaps in partitioning
};

#include "node.cpp"

#endif
