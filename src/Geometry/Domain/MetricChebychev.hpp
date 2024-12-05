#ifndef LBM_Linf
#define LBM_Linf

#include "MetricNeighbour.hpp"

template<int dim>
class MetricChebychev : MetricNeighbour<dim> {
public:
    std::vector<Node<dim>> GetNeighbours(const Domain<dim>& domain, const Point<dim>& point) {
        return std::vector<Node<dim>>();
    }
};

#endif