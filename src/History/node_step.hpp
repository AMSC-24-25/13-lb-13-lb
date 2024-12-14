/*
    @author GiacomoPauletti
*/

#ifndef NODE_STEP_HPP
#define NODE_STEP_HPP

#include <cmath>
#include <memory>

#include "step.hpp"
#include "../Geometry/Point/point.hpp"
#include "../Core/Utils/node_callback.hpp"
#include "../Core/Utils/simulation_observer.hpp"
#include "node_reading_strategy.hpp"

namespace lattice_boltzmann_method 
{
    /*
        @brief abstract class representing the storage of a simulation step in a matrix format.

        @tparam dim dimensionality of the problem (i.e.: 1, 2 or 3)
        @tparam DataType type of the data to read from the Node and store in the matrix

        This class is used to generate a matrix of values (DataType defines 
        the type of this values) where each entry is a Node in the Domain or, 
        when the domain is not rectangular, an empty cell used to "rectangularify"
        the Domain.

        This is an abstract class, use the implementations 
        lattice_boltzmann_method::NodeStep{1D,2D,3D}.
    */
    template <int dim, typename DataType>
    class NodeStep : public Step {
        public:
            /*
                @param dimensions initializes the class attribute dimensions_ (see its documentation for more)
                @param cell_size initializes the class attribute cell_size_   (see its documentation for more) 
                @param reading_strategy initializes reading_strategy_         (see its documentation for more)
            */
            NodeStep(const Point<double, dim>& dimensions, double cell_size,
                     const NodeReadingStrategy<dim, DataType> &reading_strategy) 
                : dimensions_{dimensions}, cell_size_{cell_size}, 
                  reading_strategy_{reading_strategy}
            {};

            /*
                An implementation of this class shall in here read from the 
                argument node and save the result (of type DataType) in the matrix
            */
            virtual void SaveNode(const Node<dim>& node) = 0;

            virtual void Print() const = 0;
            virtual size_t Size() const = 0;
            virtual const void * Get() const = 0;
        protected:
            /*
                a Point containing, on each coordinate, the dimension of the 
                matrix on that coordinate. Dimensions are expressed in the units of the
                problem (e.g.: meters),not in pixels. So the matrix will not have 
                dimensions.getCooordinate(0) columns but instead dimensions.getCoordinate(0) / cell_size
            */
            const Point<double, dim>& dimensions_;
            /*
                dimension of a single cell, in the units of the problem
            */
            const double cell_size_;
            const NodeReadingStrategy<dim, DataType> &reading_strategy_;
    };

    /*
        1 dimensional implementation of NodeStep abstract class. 
        Output matrix is a row vector.

        See NodeStep for further details
    */
    template <typename DataType>
    class NodeStep1D : public NodeStep<1, DataType> {
        public:
            NodeStep1D(const Point<double, 1>& dimensions, double cell_size,
                       const NodeReadingStrategy<1, DataType> &reading_strategy) 
                : NodeStep<1,DataType>(dimensions, cell_size, reading_strategy)
            {
                // TODO: dimensions is dimension in pixel or does it has to be divided by cell_size?
                matrix_.reserve(
                    static_cast<int>(
                        dimensions.GetCoordinate(0) / cell_size
                    )
                );
            };

            virtual void SaveNode(const Node<1>& node) override;
            void Print() const;
            size_t Size() const;
            const void * Get() const;
        private:
            std::vector<DataType> matrix_;

    };

    /*
        2 dimensional implementation of NodeStep abstract class. 
        Output matrix is a classical matrix.

        See NodeStep for further details
    */
    template <typename DataType>
    class NodeStep2D : public NodeStep<2, DataType> {
        public:
            NodeStep2D(const Point<double, 2>& dimensions, double cell_size,
                       const NodeReadingStrategy<2, DataType> &reading_strategy) 
                : NodeStep<2,DataType>(dimensions, cell_size, reading_strategy)
            {
                // TODO: dimensions is dimension in pixel or does it has to be divided by cell_size?
                matrix_.reserve(
                    static_cast<int>(
                        dimensions.GetCoordinate(0) / cell_size
                    )
                );
            };

            virtual void SaveNode(const Node<2>& node) override;
            void Print() const;
            size_t Size() const;
            const void * Get() const;
        private:
            std::vector<std::vector<DataType>> matrix_;

    };

    /*
        3 dimensional implementation of NodeStep abstract class. 
        Output matrix is a 3 dimensional matrix.

        See NodeStep for further details
    */
    template <typename DataType>
    class NodeStep3D : public NodeStep<3, DataType> {
        public:
            NodeStep3D(const Point<double, 3>& dimensions, double cell_size,
                       const NodeReadingStrategy<3, DataType> &reading_strategy) 
                : NodeStep<3,DataType>(dimensions, cell_size, reading_strategy)
            {
                // TODO: dimensions is dimension in pixel or does it has to be divided by cell_size?
                matrix_.reserve(
                    static_cast<int>(
                        dimensions.GetCoordinate(0) / cell_size
                    )
                );
            };

            virtual void SaveNode(const Node<3>& node) override;
            void Print() const;
            size_t Size() const;
            const void * Get() const;
        private:
            std::vector<std::vector<std::vector<DataType>>> matrix_;

    };


    /*
        @brief handles the creation of each NodeStep throughout the evolution of the simulation

        @tparam dim dimension of the problem (i.e. 1, 2 or 3)
        @tparam DataType data type which NodeStep collects for each node

        This class handles the creation of NodeStep, mainly handling on which iteration (step) a
        NodeStep has to be generated and on which iteration (step) it does not.
        In particular, this class lives between StepSimulationStrategy, which calls the 
        HandleNode of this class, and the NodeStep class, of which an object is created in 
        HandleNode according to node_step_factory_ and num_steps_to_skip_. 
    */
    template <int dim, typename DataType>
    class NodeStepHandler : public SimulationObservable, public NodeCallback<dim> {
        public:
            /*
                @param node_step_factory initializes node_step_factory_ (see its documentation for more) 
                @param num_steps_to_skip initializes num_steps_to_skip_ (see its documentation for more)             
            */
            NodeStepHandler(std::function<std::shared_ptr<NodeStep<dim,DataType>>(int)> node_step_factory, 
                            unsigned int num_steps_to_skip) 
                             : node_step_factory_{node_step_factory},
                               num_steps_to_skip_{num_steps_to_skip},
                               num_steps_left_{1},
                               node_step_flushed_{false}
            {
            }
            /* TODO: code below is not thread-safe. If 2 threads call the method below, NodeStep is
                     created twice !!
            */
            
            /*
                Method inherited from lattice_boltzmann_method::NodeCallback<dim>.
                Gets notified when a new iteration has began.
                If in the previous iteration a NodeStep was ensembled, all 
                SimulationObservers receive the NodeStep
            */
            virtual void NotifyNewIteration(int iteration_number);
            /*
                If simulation is finished, you should always call this method. 
                It can happen that the last iteration of the simulation coincides with the iteration
                where NodeStep is created and filled. However, no new iteration is performed and this
                class is not aware of the ending of the current iteration. 
                This method makes it aware of it and the currently used NodeStep is "flushed", which 
                means that all the observers are notified
            */
            virtual void FlushNodeStep();
            /* 
                Method inherited from lattice_boltzmann_method::NodeCallback<dim>.

                Adds the node to the NodeStep, only if current iteration is the
                first one or num_steps_to_skip_ away from the previous one
            */
            virtual void HandleNode(const Node<dim> &node);
            /* 
                Method inherited from lattice_boltzmann_method::NodeCallback<dim>.

                Adds the node to the NodeStep, only if current iteration is the
                first one or num_steps_to_skip_ away from the previous one
            */
            virtual void HandleNonConstNode(Node<dim> &node);

        protected:
            /*
                Function which generates a new empty NodeStep.
                    Input: current iteration number
                    Output: new empty NodeStep
                Can be useful to pass a lambda function: readable and concise.
            */
            std::function<std::shared_ptr<NodeStep<dim,DataType>>(int)> node_step_factory_;
            /*
                Since saving each iteration (step) of the simulation is expensive, it is better to
                save 1 iteration every num_steps_to_skip_+1 iterations. 
                By setting it to 0, every iteration (Step) is saved
            */
            const unsigned int num_steps_to_skip_;
            /*
                Internal use only.
                Counts the number of steps to wait until next NodeStep is generated
            */
            unsigned int num_steps_left_;
            /*
                Internal use only.
                Whether the last NodeStep has been sent to the observers or not
            */
            bool node_step_flushed_;

            /*
                Internal use only.
                Current step that is being filled
            */
            std::shared_ptr<NodeStep<dim,DataType>> current_node_step_;

    };


}

#include "node_step.cpp"

#endif // NODE_STEP_HPP
