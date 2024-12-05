#ifndef HISTORY_LBM_HPP
#define HISTORY_LBM_HPP

#include <fstream>
#include <string>
#include "step.hpp"

namespace lattice_boltzmann_method
{
    //Abstract class for streaming output
    class History /*: public Observer*/{

        private:
            std::string file_name_;
            
        public:
            virtual ~History() = default;
            virtual void addStep(Step &/*step*/)=0;
    };

    //Derived class for writing vectors in .csv file
    class CSVWriter : public History {

        private:
            std::ofstream file_;
            bool header_written_;

        public:
            CSVWriter(const std::string &/*filename*/);
            ~CSVWriter();
            void addStep(Step &/*step*/);
            void WriteHeader(const std::vector<std::string> &/*headers*/);
    };

}

#endif // HISTORY_LBM_HPP
