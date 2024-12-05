#ifndef LBM_Domain
#define LBM_Domain

#include "../Point/Point.hpp"
#include "../Node/Node.hpp"
#include "MetricNeighbour.hpp"
#include "MetricManhattan.hpp"

#include <string>
#include <vector>
#include <unordered_map>

template<int dim>
class Domain {
private:
    const MetricNeighbour _kNeighboursStartegy;
    const std::unordered_map<const Point<dim>&, const Node<dim>&> _kPointToNode;

public:
    Domain(const std::string&) = 0;

    Node<dim> GetNodeFromCoordinates(const Point<int, dim>&);
    std::vector<Node<dim>> GetNeighbours(const Point<int, dim>&);
};

#endif