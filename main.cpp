#include <iostream>

#include "evaluate_armadillo.h"
#include "evaluate_blaze.h"
#include "evaluate_eigen.h"
#include "evaluate_xtensor.h"

int main(int argc, char *argv[]) {
  constexpr unsigned int vec_size = 1000;
  constexpr unsigned int num_reps_vec_sum = 1'000'000;
  constexpr unsigned int num_reps_vec_prod_mat = 5'000;
  constexpr unsigned int num_reps_mat_inv = 100;

  std::cout << "Running armadillo code" << std::flush;
  auto [arma_sum_time, arma_vec_mat_prod_time, arma_mat_inv_time] =
      evaluate_armadillo(vec_size, num_reps_vec_sum, num_reps_vec_prod_mat,
                         num_reps_mat_inv);
  std::cout << " -> done" << std::endl;

  std::cout << "Running blaze code" << std::flush;
  auto [blaze_sum_time, blaze_vec_mat_prod_time, blaze_mat_inv_time] =
      evaluate_blaze(vec_size, num_reps_vec_sum, num_reps_vec_prod_mat,
                     num_reps_mat_inv);
  std::cout << " -> done" << std::endl;

  std::cout << "Running xtensor code" << std::flush;
  auto [xtensor_sum_time, xtensor_vec_mat_prod_time, xtensor_mat_inv_time] =
      evaluate_xtensor(vec_size, num_reps_vec_sum, num_reps_vec_prod_mat,
                       num_reps_mat_inv);
  std::cout << " -> done" << std::endl;

  std::cout << "Running eigen code" << std::flush;
  auto [eigen_sum_time, eigen_vec_mat_prod_time, eigen_mat_inv_time] =
      evaluate_eigen(vec_size, num_reps_vec_sum, num_reps_vec_prod_mat,
                     num_reps_mat_inv);
  std::cout << " -> done\n" << std::endl;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  std::cout << "Generate two random vectors and sum them" << std::endl;
  std::cout << "    Armadillo Elapsed Time: " << arma_sum_time << std::endl;
  std::cout << "    Blaze Elapsed Time: " << blaze_sum_time << std::endl;
  std::cout << "    xtensor Elapsed Time: " << xtensor_sum_time << std::endl;
  std::cout << "    Eigen Elapsed Time: " << eigen_sum_time << std::endl;

  std::cout << "\n";

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  std::cout << "Multiply a vector and a matrix" << std::endl;
  std::cout << "    Armadillo Elapsed Time: " << arma_vec_mat_prod_time
            << std::endl;
  std::cout << "    Blaze Elapsed Time: " << blaze_vec_mat_prod_time
            << std::endl;
  std::cout << "    xtensor Elapsed Time: " << xtensor_vec_mat_prod_time
            << std::endl;
  std::cout << "    eigen Elapsed Time: " << eigen_vec_mat_prod_time
            << std::endl;

  std::cout << "\n";

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  std::cout << "Invert a matrix" << std::endl;

  std::cout << "    Armadillo Elapsed Time: " << arma_mat_inv_time << std::endl;
  std::cout << "    Blaze Elapsed Time: " << blaze_mat_inv_time << std::endl;
  std::cout << "    xtensor Elapsed Time: " << xtensor_mat_inv_time
            << std::endl;
  std::cout << "    eigen Elapsed Time: " << eigen_mat_inv_time << std::endl;

  return 0;
}
