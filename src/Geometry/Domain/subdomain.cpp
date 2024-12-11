#include "subdomain.hpp"

template <int dim>
Subdomain<dim>::Subdomain(
    const std::vector<std::shared_ptr<Node<dim>>>& internal, 
    const std::unordered_map<int, std::vector<std::shared_ptr<Node<dim>>>>& interfaces, 
    int id)
{
    this->_id = id;
    this->_internal_domain = internal;
    this->_interfaces = interfaces;

    for(auto n : interfaces) {
        this->_neighbour_ids.push_back(n.first);
    }
}

template <int dim>
std::vector<std::shared_ptr<Node<dim>>> Subdomain<dim>::GetInterface(int id)
{
    return this->_interfaces[id];
}

template <int dim>
std::vector<int> Subdomain<dim>::GetNeighboursId()
{
    return this->_neighbour_ids;
}

template <int dim>
typename std::vector<std::shared_ptr<Node<dim>>>::iterator Subdomain<dim>::begin()
{
    return this->_internal_domain.begin();
}

template <int dim>
typename std::vector<std::shared_ptr<Node<dim>>>::iterator Subdomain<dim>::end()
{
    return this->_internal_domain.end();
}