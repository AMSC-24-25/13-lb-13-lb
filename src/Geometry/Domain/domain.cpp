#ifndef DOMAIN_CPP
#define DOMAIN_CPP

#include "domain.hpp"


/*template<int dim>
void Domain<dim>::LoadFromFile(const std::string& path) {
    /* File structure:
     * Row 1: Neighbour strategy ("1": Manhattan, "2": Chebychev)
     * Row 2: Reynolds number (int)
     * Row 3: Density
     * Next rows: one row per point
     *  Point description (all on one line): 
     *      Coordinates ("(x y) or (x y z)")
     *      Node type "type"
    *//*

   std::ifstream file(path);

    if (!file)
        throw std::invalid_argument("Domain: can't find file for domain configuration");

    int strategy;
    file >> strategy;

    switch(strategy) {
        case 1:
            this->_k_neighbours_strategy = std::unique_ptr<MetricNeighbour<dim>>(MetricManhattan<dim>());
            break;
        case 2:
            this->_k_neighbours_strategy = std::unique_ptr<MetricNeighbour<dim>>(MetricChebychev<dim>());
            break;
    }

    file >> this->_k_reynolds;
    file >> this->_k_density;

    // TODO: finish loading
}*/

template<int dim>
void Domain<dim>::Partition(int partitions) {
    typename std::vector<std::vector<std::shared_ptr<Node<dim>>>> internal(partitions);
    typename std::vector<std::unordered_map<int, std::vector<std::shared_ptr<Node<dim>>>>> interfaces(partitions);

    std::unordered_map<int, int> assignments;

    // hashmap iterators are deterministic over the same instance
    // assignment of points to each subdomain (this strategy easy but inefficient, should be O(n))
    int index = 0;
    for(auto& n : this->_k_point_to_node) {
        int id = n.second->GetId();
        assignments.insert({id, index});
        index = (index + 1) % partitions;
    }

    // computing neighbours
    for(auto& n : this->_k_point_to_node) {
        int id = n.second->GetId();
        int index = assignments[id];

        internal[index].push_back(n.second);

        auto neighbours = this->GetNeighbours(n.first);

        for(auto& k : neighbours) {
            int k_index = assignments[k->GetId()];

            if(k_index != index)
                interfaces[k_index][index].push_back(n.second);
        }
    }

    // generating subdomains
    for(int i = 0;i < partitions;i++) {
        this->_subdomains[i] = Subdomain<dim>(internal[i], interfaces[i], i);
    }
}

template<int dim>
void Domain<dim>::Partition(const std::vector<int>& indexes) {
    int partitions = indexes.size();

    typename std::vector<std::vector<std::shared_ptr<Node<dim>>>> internal(partitions);
    typename std::vector<std::unordered_map<int, std::vector<std::shared_ptr<Node<dim>>>>> interfaces(partitions);

    std::unordered_map<int, int> assignments;

    // hashmap iterators are deterministic over the same instance
    // assignment of points to each subdomain (this strategy easy but inefficient, should be O(n))
    int index = 0;
    for(auto& n : this->_k_point_to_node) {
        int id = n.second->GetId();
        assignments.insert({id, index});
        index = (index + 1) % partitions;
    }

    // computing neighbours
    for(auto& n : this->_k_point_to_node) {
        int id = n.second->GetId();
        int index = assignments[id];

        internal[index].push_back(n.second);

        auto neighbours = this->GetNeighbours(n.first);

        for(auto& k : neighbours) {
            int k_index = assignments[k->GetId()];

            if(k_index != index)
                interfaces[k_index][index].push_back(n.second);
        }
    }

    // generating subdomains
    for(int i = 0;i < partitions;i++) {
        this->_subdomains[i] = Subdomain<dim>(internal[i], interfaces[i], indexes[i]);
    }
}

template <int dim>
inline Subdomain<dim>& Domain<dim>::GetSubDomain(int index) const {
    return this->_subdomains[index];
}

template <int dim>
inline std::shared_ptr<Subdomain<dim>> Domain<dim>::GetSubDomainPtr(int index) const {
    return std::make_shared<Subdomain<dim>>(this->_subdomains.at(index));
}

template<int dim>
inline std::shared_ptr<Node<dim>> Domain<dim>::GetNodeFromCoordinates(const Point<int, dim>& point) const {
    return this->_k_point_to_node[point];
}

template<int dim>
inline std::vector<std::shared_ptr<Node<dim>>> Domain<dim>::GetNeighbours(const Point<int, dim>& point) const {
    return this->_k_neighbours_strategy->GetNeighbours(*this, point);
}

#endif