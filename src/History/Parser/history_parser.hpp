#ifndef HISTORY_PARSER_HPP
#define HISTORY_PARSER_HPP

#include <memory>
#include <string>

#include "../history.hpp"

namespace lattice_boltzmann_method 
{
    /*
        @brief creates an History class based on what is written in a file or in argv arguments
    */
    class HistoryParser {
        public:
            HistoryParser()=default;

            virtual std::ostream& PrintTerminalHelp(std::ostream &output_stream);

            virtual std::ostream& PrintFileHelp(std::ostream &output_stream);

            virtual std::shared_ptr<History> Parse(int &argc, char *argv[]);

            virtual std::shared_ptr<History> ParseFromFile(const std::string &path);
    };
}

#endif // HISTORY_PARSER_HPP
