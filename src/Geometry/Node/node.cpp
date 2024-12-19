#ifndef NODE_CPP
#define NODE_CPP

#include "node.hpp"

template<int dim>
void Node<dim>::SetDirections(
                                            std::vector<Point<int, dim>> &directions, 
                                            std::vector<double> &weights) {
    directions_ = directions;
    weights_ = weights;
                                            }

template<int dim>
std::vector<Point<int, dim>> Node<dim>::GetDirections() {
    return directions_;
}

template<int dim>
std::vector<double> Node<dim>::GetWeights() {
    return weights_;
}

template<int dim>
Point<int, dim> Node<dim>::GetDirection(int i) {
    return directions_[i];
}

template<int dim>
double Node<dim>::GetWeight(int i) {
    return weights_[i];
}

template<int dim>
int Node<dim>::_id_counter = 0;

template<int dim>
Node<dim>::Node(const Point<double, dim>& position, unsigned int num_directions, Point<double, dim> initial_velocity, double rho)
    : _position{position}, _num_directions{num_directions}, _rho{rho}, _u{initial_velocity}
{
    this->_id = _id_counter;
    _id_counter++;

    this->_f.reserve(num_directions);
    this->_f_eq.reserve(num_directions);
    this->_f_next.reserve(num_directions);
    //manca inizializzazione attributi
}

template<int dim>
inline Point<double, dim> Node<dim>::GetPosition() const
{
    return this->_position;
}

template <int dim>
std::vector<std::shared_ptr<Node<dim>>> Node<dim>::GetNeighbours()
{
    return this->_neighbours;
}

template <int dim>
void Node<dim>::SetNeighbours(std::vector<std::shared_ptr<Node<dim>>> neighbours)
{
    this->_neighbours = neighbours;
}

template<int dim>
inline int Node<dim>::GetId() const {
    return this->_id;
}

//getter per distribuzioni
template<int dim>
inline double Node<dim>::GetDistribution(int index) const {
    return this->_f[index];
}

template<int dim>
inline double Node<dim>::GetEquilibriumDistribution(int index) {
    return this->_f_eq[index];
}

template<int dim>
inline std::vector<double> Node<dim>::GetDistributions() {
    return this->_f;
}

template<int dim>
inline std::vector<double> Node<dim>::GetEquilibriumDistributions() {
    return this->_f_eq;
}

template<int dim>
inline Point<double, dim> Node<dim>::GetVelocity() const {
    return Point<double, dim>(this->_u);
}

template<int dim>
inline double Node<dim>::GetDensity() const {
    return this->_rho;
}

template<int dim>
inline double Node<dim>::GetPressure() const {
    return 0.0;
}

template<int dim>
inline void Node<dim>::UpdateVelocity() {
}

template<int dim>
inline void Node<dim>::UpdatePressure() {
}

template<int dim>
inline void Node<dim>::UpdateDensity() {
}

template<int dim>
void Node<dim>::UpdateEquilibriumDistributions() {
}


#endif