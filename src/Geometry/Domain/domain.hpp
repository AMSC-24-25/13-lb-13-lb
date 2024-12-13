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
#include <memory>


template<int dim>
class Domain {
private:
    const std::unique_ptr<MetricNeighbour<dim>> _k_neighbours_strategy;
    std::unordered_map<Point<int, dim>, std::shared_ptr<Node<dim>>> _k_point_to_node;
    std::unordered_map<int, Subdomain<dim>> _subdomains;

    int _k_reynolds;
    double _k_density;    // TODO: move to nodes for extensibility

public:
    //void LoadFromFile(const std::string&);
    void Partition(int);
    void Partition(const std::vector<int>&);

    Subdomain<dim>&                 GetSubDomain(int) ;
    std::shared_ptr<Subdomain<dim>> GetSubDomainPtr(int) const;

    std::shared_ptr<Node<dim>> GetNodeFromCoordinates(const Point<int, dim>&) ;
    std::vector<std::shared_ptr<Node<dim>>> GetNeighbours(const Point<int, dim>&) const;
};

#include "domain.cpp"

#endif