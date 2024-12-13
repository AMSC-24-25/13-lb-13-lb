#include "bounce_back_node.hpp"

template<int dim, int num_directions>
void BounceBackNode<dim, num_directions>::BoundaryFunction() {
    this->u.fill(0.0); // No-slip
}

template<int dim, int num_directions>
void BounceBackNode<dim, num_directions>::Collide() {
    static const std::array<int, num_directions> reflection_indices = {0, 3, 4, 1, 2, 7, 8, 5, 6};

    for (int i = 0; i < num_directions; i++) {
        this->_f[reflection_indices[i]] = this->_f_next[i];
    }
}

template<int dim, int num_directions>
void BounceBackNode<dim, num_directions>::Propagate() { //serve come parametro (Domain<dim>& domain)

    auto neighbours = domain.GetNeighbours(this->_position);
    
    for (int direction = 0; direction < num_directions; ++direction) {
        
        if (neighbours[direction]) {
            auto& neighbour = neighbours[direction];
            neighbour->_f_next[direction] = this->_f[direction];
        }
    }
}
