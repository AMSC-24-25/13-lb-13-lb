cmake_minimum_required(VERSION 3.12.0)
project(LatticeBoltzmannMethod LANGUAGES CXX C)

SET(GCC_MY_COMPILE_FLAGS "-g3 -std=c++20")
SET(GCC_MY_LINK_FLAGS    "")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_MY_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_MY_LINK_FLAGS}")
                        
#include(../../common/cmake-common.cmake)

set(SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/../src/main.cpp 

    # Core
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/simulation_manager.cpp
		# StepSimulationStrategy
		${CMAKE_CURRENT_LIST_DIR}/../src/Core/StepSimulationStrategy/step_simulation_strategy.cpp
			# Parser
			${CMAKE_CURRENT_LIST_DIR}/../src/Core/StepSimulationStrategy/Parser/step_simulation_strategy_parser.hpp
		# Utils
		${CMAKE_CURRENT_LIST_DIR}/../src/Core/Utils/node_callback.cpp

    # Geometry
		# Domain
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/domain.cpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/subdomain.cpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/metric_manhattan.cpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/metric_chebychev.cpp
		# Point
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Point/point.cpp
		# Node
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/node.cpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/boundary_node.cpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/inner_node.cpp

    # History
	${CMAKE_CURRENT_LIST_DIR}/../src/History/history.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/History/step.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/History/node_step.cpp
		# Parser
		${CMAKE_CURRENT_LIST_DIR}/../src/History/Parser/history_parser.cpp


	# Debug
	${CMAKE_CURRENT_LIST_DIR}/../src/Debug/compiler_debug.cpp
)

set(HEADERS
    # Core
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/simulation_manager.hpp
		# StepSimulationStrategy
		${CMAKE_CURRENT_LIST_DIR}/../src/Core/StepSimulationStrategy/step_simulation_strategy.hpp
			# Parser
			${CMAKE_CURRENT_LIST_DIR}/../src/Core/StepSimulationStrategy/Parser/step_simulation_strategy_parser.hpp
		#Utils
		${CMAKE_CURRENT_LIST_DIR}/../src/Core/Utils/node_callback.hpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Core/Utils/simulation_observer.hpp

    # Geometry
		# Domain
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/domain.hpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/subdomain.hpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/metric_neighbour.hpp
		# Node
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/node.hpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/boundary_node.hpp
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/inner_node.hpp
		# Point
		${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Point/point.hpp

    # History
	${CMAKE_CURRENT_LIST_DIR}/../src/History/history.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/History/step.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/History/node_step.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/History/node_reading_strategy.hpp
	 	# Parser
		${CMAKE_CURRENT_LIST_DIR}/../src/History/Parser/history_parser.hpp

	# Debug
	${CMAKE_CURRENT_LIST_DIR}/../src/Debug/compiler_debug.hpp

)

# Linking OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


add_executable(main ${SOURCES} ${HEADERS})
