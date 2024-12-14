/*
    @author GiacomoPauletti
*/

#ifndef NODE_STEP_CPP
#define NODE_STEP_CPP

#include "node_step.hpp"

namespace lattice_boltzmann_method 
{
    // ======================= NodeStepHandler ============================

    template <int dim, typename DataType>
    void NodeStepHandler<dim,DataType>::NotifyNewIteration(int iteration_number) {
        // NodeStep filled; notifying observers
        if ( num_steps_left_ == num_steps_to_skip_ ) {
            this->FlushNodeStep();
        } 

        num_steps_left_--;

        // creating empty NodeStep
        if ( num_steps_left_ == 0 ) {
            this->current_node_step_ = this->node_step_factory_(iteration_number);

            num_steps_left_ = num_steps_to_skip_;
            node_step_flushed_ = false;
        }

    }
    
    template <int dim, typename DataType>
    void NodeStepHandler<dim,DataType>::FlushNodeStep() {
        if (node_step_flushed_ && this->current_node_step_ &&
             num_steps_left_ == num_steps_to_skip_) {
            this->NotifyAllConst(*this->current_node_step_);
        }

        node_step_flushed_ = true;
    }

    template <int dim, typename DataType>
    void NodeStepHandler<dim,DataType>::HandleNode(const Node<dim> &node) {
        if ( num_steps_left_ == 0 ) {
            this->current_node_step_->SaveNode(node);
        }
    }

    template <int dim, typename DataType>
    void NodeStepHandler<dim,DataType>::HandleNonConstNode(Node<dim> &node) {
        this->HandleNode(node);
    }


    // ========================== NodeStep1D ==============================
    template <typename DataType>
    void NodeStep1D<DataType>::Print() const {
        return;
    }

    template <typename DataType>
    size_t NodeStep1D<DataType>::Size() const {
        return 0;
    }

    template <typename DataType>
    const void * NodeStep1D<DataType>::Get() const {
        return nullptr;
    }

    template <typename DataType>
    void NodeStep1D<DataType>::SaveNode(const Node<1> &node) {
        const int kXIndex = static_cast<int>(
            node.GetPosition().GetCoordinate(0) / this->cell_size_
        );

        matrix_[kXIndex] = this->reading_strategy_.Read(node);
    }


    // ========================== NodeStep2D ==============================
    template <typename DataType>
    void NodeStep2D<DataType>::Print() const {
        return;
    }

    template <typename DataType>
    size_t NodeStep2D<DataType>::Size() const {
        return 0;
    }

    template <typename DataType>
    const void * NodeStep2D<DataType>::Get() const {
        return nullptr;
    }

    template <typename DataType>
    void NodeStep2D<DataType>::SaveNode(const Node<2> &node) {
        const int kXIndex = static_cast<int>(
            node.GetPosition().GetCoordinate(0) / this->cell_size_
        );
        const int kYIndex = static_cast<int>(
            node.GetPosition().GetCoordinate(1) / this->cell_size_
        );

        matrix_[kYIndex][kXIndex] = this->reading_strategy_.Read(node);
    }

    // ========================== NodeStep2D ==============================
    template <typename DataType>
    void NodeStep3D<DataType>::Print() const {
        return;
    }

    template <typename DataType>
    size_t NodeStep3D<DataType>::Size() const {
        return 0;
    }

    template <typename DataType>
    const void * NodeStep3D<DataType>::Get() const {
        return nullptr;
    }

    template <typename DataType>
    void NodeStep3D<DataType>::SaveNode(const Node<3> &node) {
        const int kXIndex = static_cast<int>(
            node.GetPosition().GetCoordinate(0) / this->cell_size_
        );
        const int kYIndex = static_cast<int>(
            node.GetPosition().GetCoordinate(1) / this->cell_size_
        );
        const int kZIndex = static_cast<int>(
            node.GetPosition().GetCoordinate(2) / this->cell_size_
        );

        matrix_[kZIndex][kYIndex][kXIndex] = this->reading_strategy_.Read(node);
    }

}
#endif // NODE_STEP_CPP
