#ifndef LBM_Linf
#define LBM_Linf

#include "metric_neighbour.hpp"

// Chebychev metric, computes neighbours also on diagonals
template<int dim>
std::vector<Node<dim>> MetricChebychev<dim>::GetNeighbours(const Domain<dim>& domain, const Point<int, dim>& point) {
    std::vector<Node<dim>> neighbours;

    for (int i = 0; i < (1 << (2 * dim)); ++i) {
        bool is_original = true;
        
        for (int j = 0; j < dim; ++j) {
            int change = (i >> (2 * j)) & 3;
            std::array<int, dim> var;

            if (change == 1) {
                var[j] += 1;
                is_original = false;
            } else if (change == 2) {
                var[j] -= 1;
                is_original = false;
            }
        }
        Point<int, dim> neighbor(point, var);

        Node<dim> n = domain.GetNodeFromCoordinates(neighbor);
        if (!is_original && n != nullptr) {
            neighbours.push_back(domain.GetNodeFromCoordinates());
        }
    }

    return neighbours;
}

#endif