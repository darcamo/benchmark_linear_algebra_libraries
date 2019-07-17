#include "evaluate_xtensor.h"

#include "common_funcs.h"
#include <chrono>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xrandom.hpp>

std::tuple<double, double, double>
evaluate_xtensor(unsigned int vec_size, unsigned int num_reps_vec_sum,
                 unsigned int num_reps_vec_prod_mat,
                 unsigned int num_reps_mat_inv) {

  // xxxxxxxxxx Sum two vectors xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  auto tic = get_time();
  xt::xarray<double> v1_xtensor = xt::random::randn<double>({vec_size});
  xt::xarray<double> v2_xtensor = xt::random::randn<double>({vec_size});

  for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
    xt::xarray<double> sum = v1_xtensor + v2_xtensor;
  }
  auto toc = get_time();
  auto sum_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx vector times matrix xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  xt::xarray<double> m1_xtensor =
      xt::random::randn<double>({vec_size, vec_size});

  m1_xtensor.reshape({vec_size, vec_size});

  for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
    xt::xarray<double> prod = xt::linalg::dot(v1_xtensor, m1_xtensor);
  }
  toc = get_time();
  auto vec_mat_prod_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx matrix inverse xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
    xt::xarray<double> inv = xt::linalg::inv(m1_xtensor);
  }
  toc = get_time();
  auto mat_inv_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  return {sum_duration, vec_mat_prod_duration, mat_inv_duration};
}
