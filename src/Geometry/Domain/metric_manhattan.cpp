#ifndef LBM_L1
#define LBM_L1

#include "metric_neighbour.hpp"

// Manhattan metric, computes neighbours only on lateral movements
template<int dim>
std::vector<Node<dim>> MetricManhattan<dim>::GetNeighbours(const Domain<dim>& domain, const Point<int, dim>& point) {
    std::vector<Node<dim>> neighbors;
    std::array<double, dim> variations;
        for (int i = 0; i < dim; i++) {
        for (int d : {-1, 1}) {
            variations[i] = d;
            Point p(point, variations);

            Node<dim> node = domain.GetNodeFromCoordinates(p);
            neighbors.push_back();
        }
        variations[i] = 0;
    }
    return neighbors;
}

#endif