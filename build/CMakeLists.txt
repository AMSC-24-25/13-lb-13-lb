cmake_minimum_required(VERSION 3.12.0)
project(LatticeBoltzmannMethod LANGUAGES CXX C)

SET(GCC_MY_COMPILE_FLAGS "-g3")
SET(GCC_MY_LINK_FLAGS    "")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_MY_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_MY_LINK_FLAGS}")
                        
#include(../../common/cmake-common.cmake)

set(SOURCES 
	${CMAKE_CURRENT_LIST_DIR}/../src/main.cpp 

    # Core
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/simulation_manager.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/step_simulation_strategy.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/node_callback.cpp

    # Geometry
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/domain.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/subdomain.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/metric_manhattan.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/metric_chebychev.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Point/point.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/node.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/boundary_node.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/inner_node.cpp

    # History
	${CMAKE_CURRENT_LIST_DIR}/../src/History/history.cpp
	${CMAKE_CURRENT_LIST_DIR}/../src/History/step.cpp

)

set(HEADERS
    # Core
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/simulation_manager.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/step_simulation_strategy.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/node_callback.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Core/step_simulation_strategy.hpp

    # Geometry
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/domain.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/subdomain.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Domain/metric_neighbour.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/node.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/boundary_node.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Node/inner_node.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/Geometry/Point/point.hpp

    # History
	${CMAKE_CURRENT_LIST_DIR}/../src/History/history.hpp
	${CMAKE_CURRENT_LIST_DIR}/../src/History/step.hpp
)

add_executable(main ${SOURCES} ${HEADERS})
