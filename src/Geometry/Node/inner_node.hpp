#ifndef INNER_NODE_HPP
#define INNER_NODE_HPP

#include "../Geometry/Node/node.hpp"
#include "../Geometry/Point/point.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    class InnerNode : public Node<dim> {
    public:
        explicit InnerNode(const Point<double, dim>& position, int num_distributions)
            : Node<dim>(position), _f(num_distributions, 0.0), _f_eq(num_distributions, 0.0), _velocity(Point<double, dim>{}), _density(0.0), _pressure(0.0) {}

        void Collide() override;
        void Propagate() override;

        void UpdateDensity() override;
        void UpdateVelocity() override;
        void UpdatePressure() override;

        const Point<double, dim>& GetVelocity() const override { return _velocity; }
        double GetDensity() const override { return _density; }
        double GetPressure() const override { return _pressure; }

        void SetDistribution(int index, double value) override {
            if (index >= 0 && index < _f.size()) {
                _f[index] = value;
            }
        }

        double GetDistribution(int index) const override {
            if (index >= 0 && index < _f.size()) {
                return _f[index];
            }
            return 0.0;
        }

    private:
        std::vector<double> _f;    
        std::vector<double> _f_eq; 
        Point<double, dim> _velocity; 
        double _density;           
        double _pressure;          
    };

}

#endif