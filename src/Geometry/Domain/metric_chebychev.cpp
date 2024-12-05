#ifndef LBM_Linf
#define LBM_Linf

#include "metric_neighbour.hpp"

// Chebychev metric, computes neighbours also on diagonals
template<int dim>
std::vector<Node<dim>> MetricChebychev<dim>::GetNeighbours(const Domain<dim>& domain, const Point<int, dim>& point) {
    return std::vector<Node<dim>>();
}

#endif