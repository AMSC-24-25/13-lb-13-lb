#ifndef HISTORY_LBM_HPP
#define HISTORY_LBM_HPP

#include <fstream>
#include <string>
#include "step.hpp"

namespace lattice_boltzmann_method
{
    //Abstract class for streaming output
    class History /*: public Observer*/{

        protected:
            std::string file_name_;
            
        public:
            History(const std::string &/*filename*/);
            virtual ~History() = default;
            virtual void addStep(const Step &/*step*/)=0;
    };

    //Derived class for writing data vectors rowswise in .csv file
    class CSVWriter : public History {

        protected:
            std::ofstream file_;
            bool header_written_;

        public:
            CSVWriter(const std::string &/*filename*/);
            ~CSVWriter();
            void addStep(const Step &/*step*/) override;
            // Writes the header (column names), to be used before adding steps
            void WriteHeader(const std::vector<std::string> &/*headers*/);
    };

}

#endif // HISTORY_LBM_HPP
