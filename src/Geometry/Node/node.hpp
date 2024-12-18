#ifndef NODE_HPP
#define NODE_HPP

#include "../Point/point.hpp"

#include <memory>
#include <array>
#include <vector>

template<int dim>
class Node {
private:
    static int _id_counter;

protected:
    Point<double, dim> _position;
    std::vector<double> _f, _f_next, _f_eq;
    double _rho;
    std::array<double, dim> _u;
    const unsigned int _num_directions;
    int _id;

    // temporary solution to neighbours problem
    std::vector<std::shared_ptr<Node<dim>>> _neighbours;

    static inline std::vector<Point<int,dim>> directions_;
    static inline std::vector<double>         weights_;
public:
    static void                         SetDirections(
                                                std::vector<Point<int, dim>> &directions, 
                                                std::vector<double> &weights);
    static std::vector<Point<int, dim>> GetDirections();
    static std::vector<double>          GetWeights();

    static Point<int, dim>              GetDirection(int i);
    static double                       GetWeight(int i);

    Node(const Point<double, dim>&, unsigned int num_directions);

    virtual void Collide() = 0;
    virtual void Propagate() = 0;

    // abstract methods for physical properties
    virtual void SetDistribution(int /*index*/, double /*distribution*/) = 0;
    virtual double GetDistribution(int /*index*/) = 0;
    virtual double GetEquilibriumDistribution(int /*index*/) = 0;
    virtual void UpdateEquilibriumDistributions() = 0;
    virtual std::vector<double> GetDistributions() = 0;
    virtual std::vector<double> GetEquilibriumDistributions() = 0;
    virtual double GetVelocity() = 0;
    virtual double GetPressure() = 0;
    virtual double GetDensity() = 0;
    virtual void UpdateVelocity() = 0;
    virtual void UpdatePressure() = 0;
    virtual void UpdateDensity() = 0;

    virtual std::unique_ptr<Node<dim>> clone() const = 0;

    Point<double, dim> GetPosition() const;

    std::vector<std::shared_ptr<Node<dim>>> GetNeighbours();
    void SetNeighbours(std::vector<std::shared_ptr<Node<dim>>>);

    int GetId() const;  // need enumeration for hashmaps in partitioning
};

#include "node.cpp"

#endif // NODE_HPP
