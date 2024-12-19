#ifndef SIMULATION_MANAGER_CPP
#define SIMULATION_MANAGER_CPP
#include "simulation_manager.hpp"

namespace lattice_boltzmann_method 
{
    template<int dim>
    void SimulationManager<dim>::Start() {
        this->LoadDomain();
        this->SetupDomain();

        if( step_strategy_ ) 
            step_strategy_->Setup();
            step_strategy_->SimulateUntil(10);
    }
    
    template<int dim>
    void SimulationManager<dim>::LoadDomain() {
        this->_domain = std::make_shared<Domain<2>>();
    }

    template<int dim>
    void SimulationManager<dim>::SetupDomain() {
        // setup square domain (NxN), stencil pattern?
        // I'll just default to 9 speeds for 2D LBM
        std::vector<std::vector<std::shared_ptr<Node<2>>>> mesh(this->_k_domain_length, 
            std::vector<std::shared_ptr<Node<2>>>(this->_k_domain_length));
        
        // just setup mesh, later assign neighbours
        for(int r = 0;r < this->_k_domain_length;r++) {
            for(int c = 0;c < this->_k_domain_length;c++) {
                
                double dr = static_cast<double>(r);
                double dc = static_cast<double>(c);
                
                Point<double, 2> p = Point<double, 2>(std::vector<double>({dr, dc}));

                // internal node
                if(r != 0 && c != 0 && r != this->_k_domain_length - 1 && c != this->_k_domain_length - 1) {
                    mesh[r][c] = std::make_shared<InnerNode<2>>(p, 9u, Point<double, 2>({0, 0}), 1.0);
                }
                else {
                    mesh[r][c] = std::make_shared<BounceBackNode<2>>(p, 9u, Point<double, 2>({0, 0}), 1.0);
                }
            }
        }

        // compute neighbours and add to domain
        for(int r = 0;r < this->_k_domain_length;r++) {
            for(int c = 0;c < this->_k_domain_length;c++) {
                /*// compute neighbours (3x3 grid)
                std::vector<std::shared_ptr<Node<2>>> neighbours(8);
                for(int ox = -1;ox <= 1;ox++) {
                    for(int oy = -1;oy <= 1;oy++) {
                        if(r + ox >= 0 && r + ox < this->_k_domain_length &&
                        c + oy >= 0 && c + oy < this->_k_domain_length && (ox != 0 || oy != 0)) {   // boundary check
                            neighbours[(ox + 1) * 2 + oy + 1] = mesh[r + ox][c + oy];
                        }
                    }
                }*/
                std::vector<std::shared_ptr<Node<2>>> neighbours(8);
                if(r != 0 && c != 0)
                    neighbours[5] = mesh[r - 1][c - 1];
                if(r != 0)
                    neighbours[1] = mesh[r - 1][c];
                if(r != 0 && c != this->_k_domain_length - 1)
                    neighbours[4] = mesh[r - 1][c + 1];
                if(c != 0)
                    neighbours[2] = mesh[r][c - 1];
                if(c != this->_k_domain_length - 1)
                    neighbours[0] = mesh[r][c + 1];
                if(r != this->_k_domain_length - 1 && c != 0)
                    neighbours[6] = mesh[r + 1][c - 1];
                if(r != this->_k_domain_length - 1)
                    neighbours[3] = mesh[r + 1][c];
                if(r != this->_k_domain_length - 1 && c != this->_k_domain_length - 1)
                    neighbours[7] = mesh[r + 1][c + 1];



                // add to domain
                (*mesh[r][c]).SetNeighbours(neighbours);
                (*this->_domain).AddNode(mesh[r][c], Point<int, 2>(std::vector<int>({r, c})));
            }
        }

        // initializing evolution strategy
        this->step_strategy_ = std::make_shared<SerialStepSimulationStrategy<2>>(_domain, nullptr, 0.0, 1.0);
    }

    template <int dim>
    void 
    SimulationManager<dim>::Parse_(std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                       std::shared_ptr<HistoryParser> history_parser,
                       int &argc, char *argv[]) {
        step_strategy_ = simulation_strategy_parser->Parse(argc, argv);
        history_       = history_parser->Parse(argc, argv);
    }
                
    template <int dim>
    void 
    SimulationManager<dim>::ParseFromFile_(std::shared_ptr<StepSimulationStrategyParser<dim>> simulation_strategy_parser,
                               std::shared_ptr<HistoryParser> history_parser,
                               const std::string &path) {
        step_strategy_ = simulation_strategy_parser->ParseFromFile(path);
        history_       = history_parser->ParseFromFile(path);
    }

}
#endif // SIMULATION_MANAGER_CPP
