#include "step.hpp"

namespace lattice_boltzmann_method
{

    // Implementation of VectorStep
    VectorStep::VectorStep() : data_(std::vector<double>()) {}

    VectorStep::VectorStep(const std::vector<double> &input_data) : data_(input_data) {}

    void VectorStep::Print() const
    {
        for (double val : data_)
        {
            std::cout << val << ";";
        }
        std::cout << std::endl;
    }

    size_t VectorStep::Size() const
    {
        return data_.size();
    }

    void VectorStep::Add(double value)
    {
        data_.push_back(value);
    }

    const void * VectorStep::Get() const
    {
        return &data_;
    }

    void VectorStep::Set(const std::vector<double>& input_data)
    {
        data_ = input_data;
    }

    // Implementation of MatrixStep
    MatrixStep::MatrixStep() : data_(std::vector<std::vector<double>>()) {}

    MatrixStep::MatrixStep(const std::vector<std::vector<double>> &input_data) : data_(input_data) {}

    void MatrixStep::Print() const
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

    size_t MatrixStep::Size() const
    {
        return data_.size();
    }

    void MatrixStep::AddRow(const std::vector<double> &row)
    {
        data_.push_back(row);
    }

    const void * MatrixStep::Get() const
    {
        return &data_;
    }

    void MatrixStep::Set(const std::vector<std::vector<double>>& input_data)
    {
        data_ = input_data;
    }
}