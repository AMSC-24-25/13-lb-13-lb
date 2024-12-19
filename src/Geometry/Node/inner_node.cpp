#ifndef INNER_NODE_CPP
#define INNER_NODE_CPP

#include "inner_node.hpp"
#include <cmath>

#include "collision_function.hpp"

namespace lattice_boltzmann_method {

    template <int dim>
    void InnerNode<dim>::Collide() {
        CollisionFunction<dim>& collision_function = CollisionFunction<dim>::GetInstance();
        collision_function.ApplyCollision(*this);
    }

    template <int dim>
    void InnerNode<dim>::Propagate() {
        this->_f[0] = this->_f_next[0];
        for (size_t i = 1; i < Node<dim>::directions_.size(); ++i) {
            /*
            auto destination_position = this->GetPosition();
            for (int d = 0; d < dim; ++d) {
                // TODO non usare ::directions ma GetDirections
                destination_position[d] += Node<dim>::directions_[i].GetCoordinate(d);
            }

            // TODO: usare i vicini e non GetNeighbourNode
            InnerNode<dim>* neighbor = GetNeighborNode(destination_position);
            if (neighbor) {
                neighbor->SetDistribution(i, this->GetDistribution(i));
            }
            */
           this->_neighbours[i-1]->SetDistribution(i, this->_f_next[i]);
        }
    }

    template <int dim>
    void InnerNode<dim>::UpdateDensity() {
        this->_rho = 0.0;
        for (const auto& f_val : this->_f) {
            this->_rho += f_val;
        }
    }

    template <int dim>
    void InnerNode<dim>::UpdateVelocity() {
        std::array<double, dim> tmp;
        for (size_t i = 0; i < this->_f.size(); ++i) {
            for (int d = 0; d < dim; ++d) {
                // TODO non usare ::directions ma GetDirections
                tmp[d] += this->_f[i] * Node<dim>::directions_[i].GetCoordinate(d);
            }
        }
        for (int d = 0; d < dim; ++d) {
            tmp[d] /= this->_rho;
        }

        this->_u = Point<double,dim>(tmp);
    }

    template <int dim>
    void InnerNode<dim>::UpdatePressure() {
        constexpr double sound_speed = 1.0 / std::sqrt(3.0); //* Node<dim>::DeltaX / Node<dim>::DeltaT;
        //this->_pressure = this->_u * sound_speed * sound_speed;
    }

}

#endif