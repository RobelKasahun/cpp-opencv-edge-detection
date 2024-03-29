# CMake version 3.10 or higher is required for this project
cmake_minimum_required(VERSION 3.10)

# set the project name to [ opencvproject ]
project(opencvproject)

# find the OpenCV package installed in this system
find_package(OpenCV REQUIRED)

# include OpenCV's header files in this project
include_directories(opencvproject ${OpenCV_INCLUDE_DIRS})

# add executable to this project using the specified source file [ main.cpp ]
add_executable(opencvproject main.cpp)

# link OpenCV libraries to your executable
target_link_libraries(opencvproject ${OpenCV_LIBS})