#ifndef BENCHMARK_LA_LIBRARIES_EVALUATE_XTENSOR_H
#define BENCHMARK_LA_LIBRARIES_EVALUATE_XTENSOR_H

#include <tuple>

std::tuple<double, double, double>
evaluate_dynamic_xtensor(unsigned int vec_size, unsigned int num_reps_vec_sum,
                         unsigned int num_reps_vec_prod_mat,
                         unsigned int num_reps_mat_inv);

#endif // BENCHMARK_LA_LIBRARIES_EVALUATE_XTENSOR_H
