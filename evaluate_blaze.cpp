#include "evaluate_blaze.h"

#include "common_funcs.h"
#include <blaze/Blaze.h>
#include <chrono>

std::tuple<double, double, double>
evaluate_blaze(unsigned int vec_size, unsigned int num_reps_vec_sum,
               unsigned int num_reps_vec_prod_mat,
               unsigned int num_reps_mat_inv) {

  // xxxxxxxxxx Sum two vectors xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  auto tic = get_time();
  blaze::DynamicVector<double> v1_blaze(vec_size);
  blaze::DynamicVector<double> v2_blaze(vec_size);

  blaze::randomize(v1_blaze);
  blaze::randomize(v2_blaze);

  for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
    blaze::DynamicVector<double> sum = v1_blaze + v2_blaze;
  }
  auto toc = get_time();
  auto sum_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx vector times matrix xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  blaze::DynamicMatrix<double> m1_blaze(vec_size, vec_size);
  for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
    blaze::DynamicVector<double, blaze::rowVector> prod = blaze::trans(v1_blaze) * m1_blaze;
  }
  toc = get_time();
  auto vec_mat_prod_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx matrix inverse xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
    blaze::DynamicMatrix<double> inv = blaze::inv(m1_blaze);
  }
  toc = get_time();
  auto mat_inv_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  return {sum_duration, vec_mat_prod_duration, mat_inv_duration};
}
