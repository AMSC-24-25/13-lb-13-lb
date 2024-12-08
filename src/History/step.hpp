#ifndef STEP_LBM_HPP
#define STEP_LBM_HPP

#include <vector>
#include <iostream>

namespace lattice_boltzmann_method
{
    //Abstract class for generic step data
    class Step {

        public:
            virtual ~Step() = default;
            virtual void Print() const = 0;
            virtual size_t Size() const = 0;
    };

    //Derived class for row vector data
    class VectorStep : public Step {

        private:
            std::vector<double> data_;

        public:
            VectorStep();
            VectorStep(const std::vector<double>& /*input_data*/);
            void Print() const override;
            size_t Size() const override;
            void Add(double value);
            std::vector<double> Get() const;
            void Set(const std::vector<double>& /*input_data*/);
    };

    // Derived class for multiple rows data
    class MatrixStep : public Step {

        private:
            std::vector<std::vector<double>> data_;

        public:
            MatrixStep();
            MatrixStep(const std::vector<std::vector<double>>& /*input_data*/);
            void Print() const override;
            size_t Size() const override;
            void AddRow(const std::vector<double>& /*row*/);
            std::vector<std::vector<double>> Get() const;
            void Set(const std::vector<std::vector<double>>& /*input_data*/);
};

}

#endif // STEP_LBM_HPP