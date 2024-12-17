#ifndef BOUNCE_BACK_NODE_HPP
#define BOUNCE_BACK_NODE_HPP

#include <vector>
#include <tuple>
#include <stdexcept>
#include "boundary_node.hpp"

template<int dim>
class BounceBackNode : public BoundaryNode<dim> {
public:
    explicit BounceBackNode(const Point<double, dim>& position, unsigned int num_directions)
        : BoundaryNode<dim>(position, num_directions) {}

    void SetDistribution(int index, double distribution) override;

    void BoundaryFunction();

    void Collide() override;
    void Propagate() override;

    double GetVelocity() override;
    void UpdateVelocity() override;

    ~BounceBackNode() = default;

private:
    static auto GetLBMModelData(int num_directions);
    static constexpr double GetCsSquared() { return 1.0 / 3.0; } // Solo per D2Q9, necessaria modifica per più modelli

    static double ComputeDotProduct(const Point<int, dim>& ci, const std::array<double, dim>& uw);
};

#endif // BOUNCE_BACK_NODE_HPP

