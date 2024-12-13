/*
    @author GiacomoPauletti
*/
/*
    @brief this file contains many strategies for reading the data from a node.
    (By strategy we mean that you can be interested in many different combination of the data contained in a Node).
    All the concrete classes here are used in combination with 
    lattice_boltzmann_method::NodeStep to avoiding too many implementation of the latter class.
    For example, it is undesired to have:
        - VelocityNormNodeStep2D
        - VelocityNormNodeStep3D
        - VelocityNodeStep2D
        - PressureNodeStep2D
        - ...

    Read the description of each strategy to see what property of the Node is read
*/


#ifndef NODE_READING_STRATEGY_HPP
#define NODE_READING_STRATEGY_HPP

namespace lattice_boltzmann_method
{


    /*
        @brief abstract class representing a generic strategy for accessing/reading data from a node
        See concrete implementation down below for examples
    */
    template <int dim, typename DataType>
    class NodeReadingStrategy {
        public:
            /*
                @brief reads data from the given node and returns what was read 
                @param node constant reference to a node from which data will be read
                @returns a quantity of interest somehow correlated to the data read from the node
            */
            inline virtual DataType Read(const Node<dim> &node) const = 0;
    };

    /*
        @brief reads the norm of the velocity of the given node
    */
    template <int dim>
    class VelocityNormNodeReadingStrategy : public NodeReadingStrategy<dim, double> {
        public:
            inline double Read(const Node<dim> &node) const override {
                // return node.GetVelocity().Norm();
                return 0;
            }
    };

    /*
        @brief reads the velocity vector (a Point<dim>) of the given node
    */
    template <int dim, typename T>
    class VelocityNodeReadingStrategy : public NodeReadingStrategy<dim, Point<T, dim>> {
        public:
            inline Point<T, dim> Read(const Node<dim> &node) const override {
                // return node.GetVelocity();
                return Point<T, dim>();
            }
    };

    /*
        @brief reads the pressure of the given node
    */
    template <int dim>
    class PressureNodeReadingStrategy : public NodeReadingStrategy<dim, double> {
        public:
            inline double Read(const Node<dim> &node) const override {
                // return node.GetPressure();
                return 0;
            }
    };


}

#endif // NODE_READING_STRATEGY_HPP
