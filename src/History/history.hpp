#ifndef HISTORY_LBM_HPP
#define HISTORY_LBM_HPP

#include <fstream>
#include <string>
#include "step.hpp"
#include "../Core/Utils/simulation_observer.hpp"
#include <algorithm>
#include "../include/stb_image_write.h"

namespace lattice_boltzmann_method
{
    //Abstract class for streaming output
    class History : public SimulationObserver{

        protected:
            std::string file_name_;
            
        public:
            History(const std::string &/*filename*/);
            virtual ~History() = default;
            virtual void AddStep(const Step &/*step*/)=0;
            virtual void AddStep (Step &step) {AddStep(std::as_const(step));}
    };

    //Derived class for writing data vectors rowswise in .csv file
    class CSVWriter : public History {

        protected:
            std::ofstream file_;
            bool header_written_;

        public:
            CSVWriter(const std::string &/*filename*/);
            ~CSVWriter();
            void AddStep(const Step &/*step*/) override;
            // Writes the header (column names), to be used before adding steps
            void WriteHeader(const std::vector<std::string> &/*headers*/);
    };

    //Derived class for writing series of .png images
    class ImageStreamWriter : public History {

        protected:
            unsigned counter_;
            double minimum_value_;
            double maximum_value_;
            struct Color {int r, g, b;};
            Color InterpolateColor(double /*value*/);

        public:
            void AddStep(const Step &/*step*/) override;
            ImageStreamWriter(const std::string &/*filename*/, double /*minimum_value_*/, double /*maximum_value_*/);
    };

}

#endif // HISTORY_LBM_HPP
