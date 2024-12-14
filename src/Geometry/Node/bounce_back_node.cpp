#include "bounce_back_node.hpp"

template<int dim>
void BounceBackNode<dim>::BoundaryFunction() {
    this->u.fill(0.0); // No-slip
}

template<int dim>
void BounceBackNode<dim>::Collide() {
    static const std::vector<int> reflection_indices = {0, 3, 4, 1, 2, 7, 8, 5, 6};

    for (int i = 0; i < _num_directions; i++) {
        this->_f[reflection_indices[i]] = this->_f_next[i];
    }
}

template<int dim>
void BounceBackNode<dim>::Propagate() { //serve come parametro (Domain<dim>& domain)

    auto neighbours = domain.GetNeighbours(this->_position);
    
    for (int direction = 0; direction < _num_directions; ++direction) {
        
        if (neighbours[direction]) {
            auto& neighbour = neighbours[direction];
            neighbour->_f_next[direction] = this->_f[direction];
        }
    }
}
