/*
    @author GiacomoPauletti
*/
#ifndef NODE_CALLBACK_HPP
#define NODE_CALLBACK_HPP

#include "../Geometry/Node/node.hpp"

namespace lattice_boltzmann_method
{

    template<int dim>
    class NodeCallback {
        public:
            NodeCallback() {}
            virtual void NotifyNewIteration(int iteration_number)=0;
            virtual void HandleNode(const Node<dim> &node)=0;
            virtual void HandleNonConstNode(Node<dim> &node)=0;
    };

}

#endif // NODE_HANDLER_HPP
