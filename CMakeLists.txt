cmake_minimum_required(VERSION 3.10)

project(benchmark_la_libraries)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)


add_library(common
        common_funcs.h
        common_funcs.cpp)


add_library(evaluate_armadillo
        evaluate_armadillo.h
        evaluate_armadillo.cpp)
target_link_libraries(evaluate_armadillo
        PRIVATE
        CONAN_PKG::armadillo
        common)

# add_definitions(-DBLAZE_BLAS_MODE=1 )
# add_definitions(-DBLAZE_USE_BLAS_MATRIX_VECTOR_MULTIPLICATION=1)
add_library(evaluate_blaze
        evaluate_blaze.h
        evaluate_blaze.cpp)
target_link_libraries(evaluate_blaze
        PRIVATE
        CONAN_PKG::blaze
        common)


add_library(evaluate_xtensor
        evaluate_xtensor.h
        evaluate_xtensor.cpp)
target_link_libraries(evaluate_xtensor
        PRIVATE
        CONAN_PKG::xtensor
        CONAN_PKG::xtensor-blas
        common)


add_library(evaluate_eigen
        evaluate_eigen.h
        evaluate_eigen.cpp)
target_link_libraries(evaluate_eigen
        PRIVATE
        CONAN_PKG::eigen
        common)


add_executable(main main.cpp)
target_link_libraries(main evaluate_armadillo)
target_link_libraries(main evaluate_blaze)
target_link_libraries(main evaluate_xtensor)
target_link_libraries(main evaluate_eigen)



