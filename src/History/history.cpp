#include "history.hpp"

namespace lattice_boltzmann_method
{

    //Implementation of History
    History::History(const std::string &filename) : file_name_(filename) {}
    
    //Implementation of CSVWriter
    CSVWriter::CSVWriter(const std::string &filename) : History(filename), header_written_(false)
    {
        file_.open(filename);
        if (!file_.is_open())
        {
            throw std::ios_base::failure("Unable to open " + file_name_ + " file");
        }
    }

    CSVWriter::~CSVWriter()
    {
        if (file_.is_open())
        {
            file_.close();
            std::cout << file_name_ << " file written successfully." << std::endl;
        }
    }

    void CSVWriter::WriteHeader(const std::vector<std::string> &headers)
    {
        if (header_written_)
        {
            throw std::logic_error("Header already written in " + file_name_ + " file");
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
            throw std::logic_error("Header must be written before adding rows in " + file_name_ + " file");
        }
        std::streambuf *coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(file_.rdbuf());
        step.Print();
        std::cout.rdbuf(coutbuf);
    }
}