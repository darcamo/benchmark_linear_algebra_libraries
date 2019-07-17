#include "evaluate_eigen.h"
#include "common_funcs.h"
#include <Eigen/Dense>
#include <chrono>

std::tuple<double, double, double>
evaluate_eigen(unsigned int vec_size, unsigned int num_reps_vec_sum,
               unsigned int num_reps_vec_prod_mat,
               unsigned int num_reps_mat_inv) {

  // xxxxxxxxxx Sum two vectors xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  auto tic = get_time();
  Eigen::VectorXd v1_eigen = Eigen::VectorXd::Random(vec_size);
  Eigen::VectorXd v2_eigen = Eigen::VectorXd::Random(vec_size);
  for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
    Eigen::VectorXd sum = v1_eigen + v2_eigen;
  }
  auto toc = get_time();
  auto sum_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx vector times matrix xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  Eigen::MatrixXd m1_eigen = Eigen::MatrixXd::Random(vec_size, vec_size);
  for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
    Eigen::VectorXd prod = v1_eigen * m1_eigen;
  }
  toc = get_time();
  auto vec_mat_prod_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  // xxxxxxxxxx matrix inverse xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  tic = get_time();
  for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> inv =
        Eigen::Inverse(m1_eigen);
  }
  toc = get_time();
  auto mat_inv_duration = getTimeDuration(toc, tic);
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  return {sum_duration, vec_mat_prod_duration, mat_inv_duration};
}
