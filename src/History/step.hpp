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
            virtual void print() const = 0;
            virtual size_t size() const = 0;
    };

    //Derived class for row vector data
    class VectorStep : public Step {

        private:
            std::vector<double> data_;

        public:
            VectorStep();
            VectorStep(const std::vector<double>& /*input_data*/);
            void print() const override;
            size_t size() const override;
            void add(double value);
            std::vector<double> get() const;
            void set(const std::vector<double>& /*input_data*/);
    };

    // Derived class for multiple rows data
    class MatrixStep : public Step {

        private:
            std::vector<std::vector<double>> data_;

        public:
            MatrixStep();
            MatrixStep(const std::vector<std::vector<double>>& /*input_data*/);
            void print() const override;
            size_t size() const override;
            void addRow(const std::vector<double>& /*row*/);
            std::vector<std::vector<double>> get() const;
            void set(const std::vector<std::vector<double>>& /*input_data*/);
};

}

#endif // STEP_LBM_HPP