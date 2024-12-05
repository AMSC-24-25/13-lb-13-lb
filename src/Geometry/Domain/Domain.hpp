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
    const MetricNeighbour<dim> _kNeighboursStrategy;
    const std::unordered_map<Point<int, dim>, Node<dim>> _kPointToNode;

public:
    Domain(const std::string&);

    Node<dim> GetNodeFromCoordinates(const Point<int, dim>&);
    std::vector<Node<dim>> GetNeighbours(const Point<int, dim>&);
};

#endif