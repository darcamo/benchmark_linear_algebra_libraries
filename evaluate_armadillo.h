#ifndef BENCHMARK_LA_LIBRARIES_EVALUATE_ARMADILLO_H
#define BENCHMARK_LA_LIBRARIES_EVALUATE_ARMADILLO_H

#include <tuple>

std::tuple<double, double, double>
evaluate_dynamic_armadillo(unsigned int vec_size, unsigned int num_reps_vec_sum,
                           unsigned int num_reps_vec_prod_mat,
                           unsigned int num_reps_mat_inv);

#endif // BENCHMARK_LA_LIBRARIES_EVALUATE_ARMADILLO_H
