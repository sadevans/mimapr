cmake_minimum_required(VERSION 3.21)
project(mimapr)

set(CMAKE_CXX_STANDARD 20)

add_executable(mimapr lab.cpp)

find_package(Eigen3 CONFIG REQUIRED)
target_link_libraries(mimapr PRIVATE Eigen3::Eigen)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "$<0:>${CMAKE_BINARY_DIR}/lib")