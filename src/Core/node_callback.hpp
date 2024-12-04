#ifndef NODE_CALLBACK_HPP
#define NODE_CALLBACK_HPP

namespace lattice_boltzmann_method
{

    class NodeCallback {
        public:
            NodeCallback() {}
            virtual void HandleNode(/*const Node &node*/)=0;
            virtual void HandleNonConstNode(/*Node &node*/)=0;
    };

}

#endif // NODE_HANDLER_HPP
