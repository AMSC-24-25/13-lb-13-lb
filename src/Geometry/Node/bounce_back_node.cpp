#include "bounce_back_node.hpp"

template<int dim>
void BounceBackNode<dim>::BoundaryFunction(){}

template<int dim>
void BounceBackNode<dim>::Collide(){}

template<int dim>
void BounceBackNode<dim>::Propagate(){}

template<int dim>
double BounceBackNode<dim>::GetVelocity(){
    return this->_boundary_velocity;
}

template<int dim>
void BounceBackNode<dim>::UpdateVelocity(){} //serve parametro in caso

template<int dim>
void BounceBackNode<dim>::SetDistribution(int index, double distribution) {
    auto [direction_vectors, weights, reflection_indices] = GetLBMModelData(this->_num_directions);

    auto& neighbour = this->_neighbours[reflection_indices[index]];
    if (!neighbour) {
        throw std::runtime_error("Neighbour node is missing in BounceBackNode");
    }

    constexpr double cs_squared = GetCsSquared();

    const auto& uw = this->_boundary_velocity;
    const auto& ci = direction_vectors[index];
    double wi = weights[index];

    double ci_dot_uw = ComputeDotProduct(ci, uw);
    double fPropagate = distribution - 2.0 * wi * (this->_rho) * ci_dot_uw / cs_squared;

    neighbour->SetDistribution(reflection_indices[index], fPropagate);
}

template<int dim>
auto BounceBackNode<dim>::GetLBMModelData(int num_directions) {
    if (num_directions == 9) {
        return std::make_tuple(
            std::vector<Point<int, 2>>{
                {0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1},
                {1, 1}, {-1, 1}, {-1, -1}, {1, -1}
            },
            std::vector<double>{
                4.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                1.0 / 36.0, 1.0 / 36.0, 1.0 / 36.0, 1.0 / 36.0
            },
            std::vector<int>{0, 3, 4, 1, 2, 7, 8, 5, 6}
        );
    }
    throw std::invalid_argument("Invalid number of directions for LBM model");
}

template<int dim>
double BounceBackNode<dim>::ComputeDotProduct(const Point<int, dim>& ci, const std::array<double, dim>& uw) {
    double result = 0.0;
    for (int d = 0; d < dim; ++d) {
        result += ci[d] * uw[d];
    }
    return result;
}
