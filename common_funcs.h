#ifndef BENCHMARK_LA_LIBRARIES_COMMON_FUNCS_H
#define BENCHMARK_LA_LIBRARIES_COMMON_FUNCS_H

#include <chrono>
#include <iostream>
#include <string_view>

std::chrono::steady_clock::time_point get_time();

double getTimeDuration(std::chrono::steady_clock::time_point toc,
                       std::chrono::steady_clock::time_point tic);

template <typename T>
void print_elapsed_time(std::string_view label, const T &toc_minus_tic) {
  std::cout << label << " Elapsed time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   toc_minus_tic)
                       .count() /
                   1000.0
            << std::endl;
}

#endif // BENCHMARK_LA_LIBRARIES_COMMON_FUNCS_H
