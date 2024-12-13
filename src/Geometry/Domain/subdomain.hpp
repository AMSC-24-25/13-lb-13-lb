#ifndef LBM_Subdomain
#define LBM_Subdomain

#include "../Node/node.hpp"

#include <unordered_map>
#include <vector>
#include <memory>

template<int dim>
class Subdomain {
public:
    // bugs using alias in VisualStudioCode and I'm loosing too much time...
    //using DomainNodes = std::vector<std::shared_ptr<Node<dim>>>;

    Subdomain() {}

    Subdomain(const std::vector<std::shared_ptr<Node<dim>>>&, 
    const std::unordered_map<int, std::vector<std::shared_ptr<Node<dim>>>>&,
    int);

    std::vector<std::shared_ptr<Node<dim>>> GetInterface(int);
    std::vector<int> GetNeighboursId();

    typename std::vector<std::shared_ptr<Node<dim>>>::iterator begin();
    typename std::vector<std::shared_ptr<Node<dim>>>::iterator end();

private:
    std::vector<std::shared_ptr<Node<dim>>> _internal_domain;
    std::unordered_map<int, std::vector<std::shared_ptr<Node<dim>>>> _interfaces;
    std::vector<int> _neighbour_ids;

    int _id;
};

template class Subdomain<2>;
template class Subdomain<3>;

#endif
