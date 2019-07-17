#include "common_funcs.h"

std::chrono::steady_clock::time_point get_time() {
  return std::chrono::steady_clock::now();
}

double getTimeDuration(std::chrono::steady_clock::time_point toc,
                       std::chrono::steady_clock::time_point tic) {
  return std::chrono::duration_cast<std::chrono::milliseconds>(toc - tic)
             .count() /
         1000.0;
}
