#ifndef LBM_Domain
#define LBM_Domain

#include "../Point/Point.hpp"
#include "../Node/Node.hpp"
#include "MetricNeighbour.hpp"

#include <string>
#include <vector>
#include <unordered_map>

template<int dim>
class Domain {
private:
    const MetricNeighbour<dim> _k_neighbours_strategy;
    const std::unordered_map<Point<int, dim>, Node<dim>> _k_point_to_node;

public:
    Domain(const std::string&);

    Node<dim> GetNodeFromCoordinates(const Point<int, dim>&) const;
    std::vector<Node<dim>> GetNeighbours(const Point<int, dim>&) const;
};

#endif