# Lattice Boltzmann Method HandsOn

Lattice Boltzmann Method (LBM) Simulation for 2D Lid-Driven Cavity Problem
This project implements a Lattice Boltzmann Method (LBM) simulation to solve the 2D lid-driven cavity problem at a Reynolds number of 100. The lid-driven cavity problem is a widely used benchmark for computational fluid dynamics (CFD) simulations, where a fluid is confined within a square cavity. The top lid of the cavity moves with a constant velocity, while the other three walls remain stationary.
The LBM method offers advantages over traditional Navier-Stokes solvers, including simpler algorithms, better scalability for parallelization, and flexibility in handling complex geometries. In this project, the results obtained from the simulation are compared with reference data from the paper "High-Resolution for Incompressible Flow Using the Navier-Stokes Equations and a Multigrid Method" by U. Ghia, K. N. Ghia, and C. T. Shin (Journal of Computational Physics, 1982).
________________________________________
Table of Contents
1.	Introduction
2.	Code Structure
3.	Parallelization
4.	Simulation Workflow
________________________________________
1. Introduction
The Lattice Boltzmann Method (LBM) is a numerical approach for simulating fluid dynamics, especially in systems where complex geometries and parallelization are required. Unlike traditional CFD methods that solve the Navier-Stokes equations for macroscopic quantities (velocity, pressure, etc.), LBM simulates the behavior of fictive particles on a discrete lattice grid. These particles undergo two key processes:
•	Propagation: Particles move to neighboring lattice sites.
•	Collision: Particles interact and relax towards an equilibrium distribution.
LBM is particularly well-suited for parallelization and complex geometries, making it an ideal choice for fluid dynamics simulations like the lid-driven cavity problem.
________________________________________
2. Code Structure and Key Components
The codebase is designed to simulate the 2D lid-driven cavity problem using the Lattice Boltzmann Method (LBM). It is modular, flexible, and scalable, allowing for easy configuration of simulation parameters, grid size, dimensionality, and parallelization options. Below is a breakdown of the main components in the code structure:
Core Modules:
1.	Domain: Defines the spatial grid and discretization of the simulation domain (cavity). The domain can be easily customized to represent different grid sizes or geometries. It specifies how the cavity is divided into smaller cells and determines the resolution and cell size.
2.	NodeStep: Stores the state of the simulation at each time step, encapsulating the fluid properties such as velocity, density, and distribution functions for each node in the grid. NodeStep is implemented in a way that it can manage grids of varying dimensions (1D, 2D, or 3D) by using specialized subclasses like NodeStep1D, NodeStep2D, and NodeStep3D. These classes store simulation data in vector or matrix formats, depending on the dimensionality of the simulation.
3.	LBM Solver: Implements the core Lattice Boltzmann algorithm, which involves the propagation and collision steps for updating fluid properties at each grid node. It manages the evolution of the velocity distribution functions and fluid quantities at each step.
4.	Boundary Conditions: Responsible for enforcing the boundary conditions of the simulation. For the 2D lid-driven cavity problem:
o	Top Lid: The velocity of the fluid at the top boundary is set to a constant value (moving lid).
o	Other Walls: No-slip conditions are applied, meaning zero velocity is imposed on the left, right, and bottom walls.
5.	Observers: These components collect data during the simulation and output it for analysis. The primary observer is the CSVWriter, which tracks the simulation data and writes it to a CSV file. Observers can be registered to NodeStepHandler to ensure that data is recorded at each step of the simulation.
Key Classes:
•	Point: Represents spatial points in the simulation domain. This class is generalized to manage 1D, 2D, or 3D spaces and stores the coordinates of grid cells. It plays a significant role in tracking the fluid properties at each location in the domain.
•	NodeStep: This class abstracts the storage of simulation data at each time step. It contains the fluid properties for each node, including the velocity distribution functions and other macroscopic quantities (e.g., density, pressure). It provides methods for interacting with this data, including accessing and updating node states.
o	NodeStep1D, NodeStep2D, NodeStep3D: These are specialized subclasses of NodeStep for handling 1D, 2D, and 3D grids. They store simulation data in different matrix or vector formats, depending on the dimensionality of the simulation.
•	NodeStepHandler: This class manages the creation and filling of NodeStep objects during each simulation iteration. It coordinates the interaction between simulation steps and observers (like CSVWriter). It tracks iteration numbers, time, and boundary conditions, and can be configured to skip certain iterations for performance reasons.
•	CSVWriter: An observer class that collects simulation data and writes it to CSV files for analysis. It listens for updates from the simulation and records the state of the system at each simulation step.
•	SimulationManager: The central class that orchestrates the simulation. It initializes the simulation strategy, manages the execution of simulation steps, and coordinates with observers like CSVWriter to track the state of the system. It provides the Start() method that begins the simulation and runs it through all the steps.
•	SerialStepSimulationStrategy: This strategy controls the step-by-step execution of the simulation. It dictates how each simulation step is performed and how the data in NodeStep objects is managed at each iteration.
________________________________________
3. Parallelization
This project supports parallel computing using either MPI (Message Passing Interface) or OpenMP for multi-threading.
•	MPI for distributing the grid across multiple processes running on different nodes, with communication occurring at the boundaries of each sub-domain.
•	OpenMP for multi-threading on shared-memory systems, where different threads operate on different sections of the grid in parallel.
The parallelization is designed to improve the simulation's scalability and efficiency, especially for large grids or complex simulations.
________________________________________
4. Simulation Workflow
Here is the step-by-step workflow for running the simulation:
1.	Initialize Constants: Define simulation constants such as dimensionality (2D), cell size, and the domain dimensions.
2.	Create Simulation Strategy: Define the simulation control using SerialStepSimulationStrategy, which dictates how the simulation progresses step-by-step.
3.	Initialize History Management: Create the CSVWriter to track simulation data and output it for analysis.
4.	Create NodeStepHandler: The handler is responsible for creating NodeStep objects at each iteration and adding them to the history tracker.
5.	Register Observers: Register the CSVWriter to observe the NodeStepHandler and output simulation data to a CSV file.
6.	Start the Simulation: Using SimulationManager, the simulation is initialized with the configured strategy and history tracking. The Start() method begins the simulation process, running through iterations and generating output.
________________________________________
Conclusion
This project demonstrates the application of the Lattice Boltzmann Method (LBM) for solving the 2D lid-driven cavity problem. It provides a flexible and efficient simulation framework that can be extended to higher-dimensional simulations or modified for different fluid dynamics problems. The parallelization using MPI or OpenMP ensures that the simulation scales well for large grids or high-resolution models. By comparing the simulation results with reference data, this project validates the correctness of the LBM implementation.

________________________________________
