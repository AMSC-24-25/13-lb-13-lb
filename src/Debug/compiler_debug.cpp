#include "compiler_debug.hpp"

using namespace lattice_boltzmann_method;

// domain.hpp
template class Domain<1>;
template class Domain<2>;
template class Domain<3>;

// subdomain.hpp
template class Subdomain<1>;
template class Subdomain<2>;
template class Subdomain<3>;

// simulation_manager.hpp
template class SimulationManager<1>;
template class SimulationManager<2>;
template class SimulationManager<3>;

// step_simulation_strategy.hpp
template class SerialStepSimulationStrategy<1>;
template class SerialStepSimulationStrategy<2>;
template class SerialStepSimulationStrategy<3>;

// openmp_step_simulation_strategy.hpp
template class OpenMPStepSimulationStrategy<1>;
template class OpenMPStepSimulationStrategy<2>;
template class OpenMPStepSimulationStrategy<3>;

// step_simulation_strategy_parser.hpp
template class StepSimulationStrategyParser<1>;
template class StepSimulationStrategyParser<2>;
template class StepSimulationStrategyParser<3>;

// point.hpp
template class Point<int, 1>;
template class Point<int, 2>;
template class Point<int, 3>;
template class Point<double, 1>;
template class Point<double, 2>;
template class Point<double, 3>;

// node.hpp
template class Node<1>;
template class Node<2>;
template class Node<3>;

// node_step.hpp
template class NodeStep1D<double>;
template class NodeStep1D<Point<double,1>>;
template class NodeStep2D<double>;
template class NodeStep2D<Point<double, 2>>;
template class NodeStep3D<double>;
template class NodeStep3D<Point<double, 3>>;
template class NodeStepHandler<1, double>;
template class NodeStepHandler<1, Point<double,1>>;
template class NodeStepHandler<2, double>;
template class NodeStepHandler<2, Point<double, 2>>;
template class NodeStepHandler<3, double>;
template class NodeStepHandler<3, Point<double, 3>>;


// node_reading_strategy.hpp
template class VelocityNormNodeReadingStrategy<1>;
template class VelocityNormNodeReadingStrategy<2>;
template class VelocityNormNodeReadingStrategy<3>;
template class VelocityNodeReadingStrategy<1, double>;
template class VelocityNodeReadingStrategy<2, double>;
template class VelocityNodeReadingStrategy<3, double>;
template class PressureNodeReadingStrategy<1>;
template class PressureNodeReadingStrategy<2>;
template class PressureNodeReadingStrategy<3>;