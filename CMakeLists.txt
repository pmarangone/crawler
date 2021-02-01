cmake_minimum_required(VERSION 3.14)

project(Crawler LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# SET COMPILER TO GCC
set(CMAKE_C_COMPILER "/usr/local/bin/gcc-9")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(wxWidgets_FIND_COMPONENTS base core net xml html adv)

# BUILD MODE
# set(CMAKE_BUILD_TYPE Debug)

# set(CMAKE_MODULE_PATH "/Users/Shared/C++/wxWidgets-3.1.4/build-cocoa-debug/")
find_package(SDL2 REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS ${wxWidgets_FIND_COMPONENTS})
# include_directories("/Users/Shared/C++/wxWidgets-3.1.4/build-cocoa-debug/lib/wx/include/")
include_directories(${SDL2_INCLUDE_DIRS})
include(${wxWidgets_USE_FILE})

# INCLUDE ALL .CPP FILES FROM SRC DIRECTORY
file(GLOB project_SRCS src/*.cpp)

add_executable(${PROJECT_NAME} ${project_SRCS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${wxWidgets_LIBRARIES})




###

# target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})

# IF FILES ARE IN MAIN PROJECT FOLDER (NOT SRC)
# add_executable(particles main.cpp screen.cpp particle.cpp swarm.cpp)

# set(CMAKE_FIND_ROOT_PATH "/usr/local/Cellar/wxmac/3.0.5.1_1/")
# cmake -G "Unix Makefiles" .. -DwxWidgets_CONFIG_EXECUTABLE=/usr/local/Cellar/wxmac/3.0.5.1_1/bin/wx-config
# cmake .. -DCMAKE_TOOLCHAIN_FILE=/Users/Shared/C++/vcpkg/scripts/buildsystems/vcpkg.cmake
# target_include_directories(${PROJECT_NAME} PUBLIC "/Users/Shared/C++/wxWidgets-3.1.4/build-cocoa-debug")

# SET COMPILER TO GCC (standard GCC)
# set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-9")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")