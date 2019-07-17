cmake_minimum_required(VERSION 3.10)

project(benchmark_la_libraries)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(main main.cpp)
target_link_libraries(main CONAN_PKG::armadillo)
target_link_libraries(main CONAN_PKG::blaze)
target_link_libraries(main CONAN_PKG::xtensor)
target_link_libraries(main CONAN_PKG::xtensor-blas)
target_link_libraries(main CONAN_PKG::xsimd)
target_link_libraries(main CONAN_PKG::eigen)
