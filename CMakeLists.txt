cmake_minimum_required(VERSION 3.14)

project(Crawler LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# SET COMPILER TO GCC (Mac and Linux only)
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(wxWidgets_FIND_COMPONENTS base core net xml html adv)

# BUILD MODE
# set(CMAKE_BUILD_TYPE Debug)

find_package(wxWidgets REQUIRED COMPONENTS ${wxWidgets_FIND_COMPONENTS})
include(${wxWidgets_USE_FILE})

# INCLUDE ALL .CPP FILES FROM SRC DIRECTORY
file(GLOB project_SRCS src/*.cpp)

add_executable(${PROJECT_NAME} ${project_SRCS})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})