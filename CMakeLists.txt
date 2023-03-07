cmake_minimum_required(VERSION 3.20)
project(svd)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include)
add_executable(svd main.cpp)
