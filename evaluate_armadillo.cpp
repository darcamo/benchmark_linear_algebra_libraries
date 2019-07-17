#include "evaluate_armadillo.h"
#include "common_funcs.h"
#include <armadillo>
#include <chrono>

std::tuple<double, double, double>
evaluate_armadillo(unsigned int vec_size, unsigned int num_reps_vec_sum,
                   unsigned int num_reps_vec_prod_mat,
                   unsigned int num_reps_mat_inv) {
  // xxxxxxxxxx Sum two vectors xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  auto tic = get_time();
  arma::vec v1_arma = arma::randu<arma::vec>(vec_size);
  arma::vec v2_arma = arma::randu<arma::vec>(vec_size);
  for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
    arma::vec sum = v1_arma + v2_arma;
  }
  auto toc = get_time();
  auto sum_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx vector times matrix xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  arma::mat m1_arma = arma::randu<arma::mat>(vec_size, vec_size);
  for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
    arma::vec prod = v1_arma * m1_arma;
  }
  toc = get_time();
  auto vec_mat_prod_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx matrix inverse xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
    arma::mat inv = arma::inv(m1_arma);
  }
  toc = get_time();
  auto mat_inv_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  return {sum_duration, vec_mat_prod_duration, mat_inv_duration};
}
