#include <memory>
#include <functional>

#include "Core/simulation_manager.hpp"
#include "History/history.hpp"
#include "History/node_step.hpp"
#include "History/node_reading_strategy.hpp"
#include "Geometry/Point/point.hpp"

using namespace lattice_boltzmann_method;

int main(int argc, char *argv[]) {
    // ======================= Problem constants ========================
    constexpr int kDim= 2;
    constexpr double cell_size = 10;
    const Point<double, kDim> dimensions{{1000.0, 1000.0}};        // TODO: make point constexpr if input is constexpr
    const VelocityNormNodeReadingStrategy<kDim> node_reading_strategy;

    // ================ Creating simulation strategy =====================
    // Simulation strategy
    std::shared_ptr<SerialStepSimulationStrategy<kDim>> serial_step_simulation_strategy =
                                            std::make_shared<SerialStepSimulationStrategy<kDim>>();

    // ==================== Initializing History =========================
    // History "tracker"
    constexpr unsigned int kNumIterationsToIgnore = 20;
    std::shared_ptr<CSVWriter> csv_writer = std::make_shared<CSVWriter>("some_file");

    // Factory for creating NodeSteps
    std::function<std::shared_ptr<NodeStep2D<double>>(int)> node_step_factory = 
        [&](int iteration_number) -> std::shared_ptr<NodeStep2D<double>>
        {
            return std::make_shared<NodeStep2D<double>>(dimensions, cell_size, node_reading_strategy);
        };
    
    // NodeStepHandler for filling the NodeSteps
    std::shared_ptr<NodeStepHandler<kDim, double>> node_step_handler = 
        std::make_shared<NodeStepHandler<kDim, double>>(node_step_factory, kNumIterationsToIgnore);

    // Putting all together: history registered to node_step_handler and 
    //      node_step_handler passed to step_simulation_strategy
    node_step_handler->RegisterObserver(csv_writer);
    serial_step_simulation_strategy->AddNodeCallback(node_step_handler);

    // ================ Creating the Simulation manager ===================
    SimulationManager<kDim> simulation_manager = SimulationManager<kDim>(argc, argv, 
                                                                         serial_step_simulation_strategy,
                                                                         csv_writer);
    // ==================== Starting the simulation =======================
    simulation_manager.Start();
    return 0;
}