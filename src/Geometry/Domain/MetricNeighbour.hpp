#ifndef LBM_Metric
#define LBM_Metric

#include "../Point/Point.hpp"
#include "../Domain/Domain.hpp"
#include "../Node/Node.hpp"

#include <vector>
#include <array>

template<int dim>
class Domain;

// abstract class to compute the neighbours with specified metric (strategy pattern)
template<int dim>
class MetricNeighbour {
public:
    virtual std::vector<Node<dim>> GetNeighbours(const Domain<dim>&, const Point<int, dim>&) = 0;
};

template<int dim> 
class MetricManhattan : public MetricNeighbour<dim> {
public:
    std::vector<Node<dim>> GetNeighbours(const Domain<dim>&, const Point<int, dim>&) override;
};

template<int dim> 
class MetricChebychev : public MetricNeighbour<dim> {
public:
    std::vector<Node<dim>> GetNeighbours(const Domain<dim>&, const Point<int, dim>&) override;
};

#endif