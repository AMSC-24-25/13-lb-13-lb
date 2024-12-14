#include "history_parser.hpp"

namespace lattice_boltzmann_method 
{

    std::ostream& HistoryParser::PrintTerminalHelp(std::ostream &output_stream){
        // TODO
        return output_stream;
    }

    std::ostream& HistoryParser::PrintFileHelp(std::ostream &output_stream) {
        // TODO
        return output_stream;
    }
    
    std::shared_ptr<History> HistoryParser::Parse(int &argc, char *argv[]) {
        // TODO
        return nullptr;
    }

    std::shared_ptr<History> HistoryParser::ParseFromFile(const std::string &path) {
        // TODO
        return nullptr;
    }

}