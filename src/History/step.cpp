#include "step.hpp"

namespace lattice_boltzmann_method
{

    // Implementation of VectorStep
    VectorStep::VectorStep() : data_(std::vector<double>()) {}

    VectorStep::VectorStep(const std::vector<double> &input_data) : data_(input_data) {}

    void VectorStep::print() const
    {
        for (double val : data_)
        {
            std::cout << val << ";";
        }
        std::cout << std::endl;
    }

    size_t VectorStep::size() const
    {
        return data_.size();
    }

    void VectorStep::add(double value)
    {
        data_.push_back(value);
    }

    std::vector<double> VectorStep::get() const
    {
        return data_;
    }

    void VectorStep::set(const std::vector<double>& input_data)
    {
        data_ = input_data;
    }

    // Implementation of MatrixStep
    MatrixStep::MatrixStep() : data_(std::vector<std::vector<double>>()) {}

    MatrixStep::MatrixStep(const std::vector<std::vector<double>> &input_data) : data_(input_data) {}

    void MatrixStep::print() const
    {
        for (const auto &row : data_)
        {
            for (double val : row)
            {
                std::cout << val << ";";
            }
            std::cout << std::endl;
        }
    }

    size_t MatrixStep::size() const
    {
        return data_.size();
    }

    void MatrixStep::addRow(const std::vector<double> &row)
    {
        data_.push_back(row);
    }

    std::vector<std::vector<double>> MatrixStep::get() const
    {
        return data_;
    }

    void MatrixStep::set(const std::vector<std::vector<double>>& input_data)
    {
        data_ = input_data;
    }
}