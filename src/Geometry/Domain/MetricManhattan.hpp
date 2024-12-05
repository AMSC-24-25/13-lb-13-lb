#ifndef LBM_L1
#define LBM_L1

#include "MetricNeighbour.hpp"

// Manhattan metric, only computes lateral movements without diagonals
template<int dim>
class MetricManhattan : MetricNeighbour<dim> {
public:
    std::vector<Node<dim>> GetNeighbours(const Domain<dim>& domain, const Point<dim>& point) {
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
};

#endif