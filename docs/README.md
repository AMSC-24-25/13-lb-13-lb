Here the documentation of the program, in an abstract way. More details may be given in separate files

Here is the diagram class UML:
``` mermaid
classDiagram
    %% The main class. It handles the simulation. This means that it set ups
    %% the Domain and the LBM classes. It then handles the evolution of the simulation
    %% and saves the data inside the History class
    class SimulationManager {
        init() void
        start() void
    }


    %% Contains an iteration of the algorithm. Calling many times the method LBM::next() makes the system evolve.
    %% Can be implemented in various way, depending on the optimization (serial, CUDA, OpenMP, MPI, ...)
    class LBM {
        << abstract >>
        computeStep() void
    }

    %% Whoever is interested in being notified by the LBM when a new step is computer
    %% it has to inherit from this interface
    class IStepObserver {
        << interface >>
        addStep(Step newStep) void
    }

    %% A container class. Keep track of the Nodes and (maybe) other details of the problem,
    %% such as the speed of sound, the viscosity and the Reynolds number.
    %% This class represents the lattice as a grid of points
    class Domain {  
        + double speedOfSound
        + parseFromFile(std::string path) void
    }

    %% A generic point in the grid. Can be either an InnerNode or a BoundaryNode
    %% Each node has a coordinate associated to it
    class Node~dim~ {
        << abstract >>
        + Point~dim~ coordinates
    }

    %% A Node which is not on the boundary. Collision and propagation are
    %% done in the classical manner
    class InnerNode~dim~ {

    }

    %% A Node which is on the boundary. Collision and, expecially, propagation
    %% hav
    class BoundaryNode~dim~ {
        << abstract >>

    }

    class BounceBackNode~dim~ {

    }

    class CollisionFunction {
        << abstract >>
    }


    class History {
        toFile(std::string path) bool
        addStep(Step step) void
    }

    class Step {

    }

    class Graphics {

    }


    SimulationManager --> LBM
    SimulationManager --> History
    LBM-->Domain
    LBM-->Step
    LBM-->IStepObserver
    IStepObserver-->Step

    InnerNode-->CollisionFunction

    Domain o-- Node
    Node <|-- BoundaryNode 
    Node <|-- InnerNode
    BoundaryNode <|-- BounceBackNode
    History o-- Step
```
