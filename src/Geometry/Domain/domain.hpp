#ifndef LBM_Domain
#define LBM_Domain

#include "../Point/point.hpp"
#include "../Node/node.hpp"
#include "metric_neighbour.hpp"
#include "subdomain.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>


template<int dim>
class Domain {
private:
    const MetricNeighbour<dim> _k_neighbours_strategy;
    const std::unordered_map<Point<int, dim>, Node<dim>> _k_point_to_node;
    std::vector<Subdomain<dim>> _subdomains;

    int _k_reynolds;
    double _k_density;    // TODO: move to nodes for extensibility

public:
    void LoadFromFile(const std::string&);
    void Partition(int);
    void Partition(const std::vector<int>&);

    Subdomain<dim> GetSubDomain(int) const;

    Node<dim> GetNodeFromCoordinates(const Point<int, dim>&) const;
    std::vector<Node<dim>> GetNeighbours(const Point<int, dim>&) const;
};

#endif