#ifndef LBM_Metric
#define LBM_Metric

#include "../Point/point.hpp"
#include "../Node/node.hpp"

#include <vector>
#include <array>

template<int dim>
class Domain;

// abstract class to compute the neighbours with specified metric (strategy pattern)
template<int dim>
class MetricNeighbour {
public:
    virtual std::vector<std::shared_ptr<Node<dim>>> GetNeighbours(const Domain<dim>&, const Point<int, dim>&) = 0;
};

template<int dim> 
class MetricManhattan : MetricNeighbour<dim> {
public:
    std::vector<std::shared_ptr<Node<dim>>> GetNeighbours(const Domain<dim>&, const Point<int, dim>&) override;
};

template<int dim> 
class MetricChebychev : MetricNeighbour<dim> {
public:
    std::vector<std::shared_ptr<Node<dim>>> GetNeighbours(const Domain<dim>&, const Point<int, dim>&) override;
};

#endif