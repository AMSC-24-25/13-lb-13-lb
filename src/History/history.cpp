#include "history.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

namespace lattice_boltzmann_method
{

    //Implementation of History
    History::History(const std::string &filename) : file_name_(filename) {}
    
    //Implementation of CSVWriter
    CSVWriter::CSVWriter(const std::string &filename) : History(filename), header_written_(false)
    {
        file_.open(filename + ".csv");
        if (!file_.is_open())
        {
            throw std::ios_base::failure("Unable to open " + file_name_ + ".csv file");
        }
    }

    CSVWriter::~CSVWriter()
    {
        if (file_.is_open())
        {
            file_.close();
            std::cout << file_name_ << ".csv file written successfully." << std::endl;
        }
    }

    void CSVWriter::WriteHeader(const std::vector<std::string> &headers)
    {
        if (header_written_)
        {
            throw std::logic_error("Header already written in " + file_name_ + ".csv file");
        }
        for (size_t i = 0; i < headers.size(); ++i)
        {
            file_ << headers[i] << ";";
        }
        file_ << std::endl;
        header_written_ = true;
    }

    void CSVWriter::AddStep(const Step &step)
    {
        if (!header_written_)
        {
            throw std::logic_error("Header must be written before adding rows in " + file_name_ + ".csv file");
        }
        std::streambuf *coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(file_.rdbuf());
        step.Print();
        std::cout.rdbuf(coutbuf);
    }

    //Implementation of ImageStreamWriter
    ImageStreamWriter::ImageStreamWriter(const std::string &filename, double minimum_value_, double maximum_value_) 
        : History(filename), counter_(0),minimum_value_(minimum_value_), maximum_value_(maximum_value_) {}

    void ImageStreamWriter::AddStep(const Step &step)
    {
        const std::vector<std::vector<double>>* data_matrix = static_cast<const std::vector<std::vector<double>>*>(step.Get());
        int height = data_matrix->size();
        int width = (*data_matrix)[0].size();

        // Create array for data image
        std::vector<unsigned char> image_data(height * width * 3);

        // Transform into RGB colors
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Color color = InterpolateColor((*data_matrix)[y][x]);
                int idx = (y * width + x) * 3;
                image_data[idx] = color.r;
                image_data[idx + 1] = color.g;
                image_data[idx + 2] = color.b;
            }
        }

        // Write the image as filename_counter.png
        std::string output_file = file_name_ + "_" + std::to_string(counter_) + ".png";
        if (stbi_write_png((output_file).c_str(), width, height, 3, image_data.data(), width * 3) == 0) {
            std::cerr << "Error during writing: " << output_file << std::endl;
        } else {
            std::cout << "Image saved in " << output_file << std::endl;
        }

        // Increase counter
        this->counter_++;
    }

    ImageStreamWriter::Color ImageStreamWriter::InterpolateColor(double value)
    {
        // Normalize between 0 and 1
        double normalized = (value - minimum_value_) / (maximum_value_ - minimum_value_);
        normalized = std::max(0.0, std::min(1.0, normalized));
    
        // Blue-Red scale
        int r = static_cast<int>(std::min(255.0, ((2*normalized+1)*(2*normalized+1)-1)/3*255));
        int b = static_cast<int>(std::min(255.0, ((3.0 - 2.0*normalized)*(3.0 - 2.0*normalized) - 1)/3 * 255));
        int g = std::min(r, b);

        return {r, g, b};
    }

}