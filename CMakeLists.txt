cmake_minimum_required(VERSION 3.15)
project(svd)

set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)

set(CMAKE_CXX_STANDARD 17)

project(svd LANGUAGES CXX CUDA)

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)

add_executable(svd main.cpp)

add_executable(svd_c src/svd_main.c src/svd_one_sided_jacobi_C.c src/host_functions.c)

find_package(Eigen3 REQUIRED)
message(${EIGEN3_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})

set(OpenCV_DIR /home/guanyx/cpp-resource/3rdparty/opencv-3.4.12/build)
find_package(OpenCV 3.0 QUIET)

add_executable(svd_cpp src/svd_main.cpp src/host_func.cpp src/svd_one_sided_jacobi_CPP.cpp)
target_link_libraries(svd_cpp ${EIGEN3_LIBS} ${OpenCV_LIBS})

add_executable(svd_cuda_seq src/oneSidedSequential.cu src/svd_one_sided_jacobi_CPP_cuda.cpp src/host_func.cpp)
target_link_libraries(svd_cuda_seq ${EIGEN3_LIBS})

add_executable(generate src/generate.cpp)