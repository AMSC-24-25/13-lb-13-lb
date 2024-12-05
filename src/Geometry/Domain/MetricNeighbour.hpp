#ifndef LBM_Metric
#define LBM_Metric

#include "../Point/Point.hpp"
#include "../Domain/Domain.hpp"

#include <vector>
#include <array>

// abstract class to compute the neighbours with specified metric (strategy pattern)
template<int dim>
class MetricNeighbour {
public:
    virtual std::vector<Node> GetNeighbours(const Domain<dim>&, const Point<dim>&) = 0;
};

#endif