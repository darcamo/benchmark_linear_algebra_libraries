#include <Eigen/Dense>
#include <armadillo>
#include <blaze/Blaze.h>
#include <iostream>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xrandom.hpp>

#include <string_view>

#include <chrono>

auto get_time() { return std::chrono::steady_clock::now(); }

template <typename T>
void print_elapsed_time(std::string_view label, const T& toc_minus_tic) {
    std::cout << label << " Elapsed time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(toc_minus_tic)
                       .count() /
                   1000.0
            << std::endl;
}
int main(int argc, char *argv[])
{
    constexpr unsigned int vec_size = 100;
    constexpr unsigned int num_reps_vec_sum = 10'000'000;
    constexpr unsigned int num_reps_vec_prod_mat = 500'000;
    constexpr unsigned int num_reps_mat_inv = 10'000;

            std::cout
        << "Generate two random vectors and sum them" << std::endl;

    // xxxxxxxxxx Armadillo case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    auto tic = get_time();
    arma::vec v1_arma = arma::randu<arma::vec>(vec_size);
    arma::vec v2_arma = arma::randu<arma::vec>(vec_size);
    for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
      arma::vec sum = v1_arma + v2_arma;
    }
    auto toc = get_time();
    print_elapsed_time("    Armadillo", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx Blaze case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    blaze::DynamicVector<double> v1_blaze(vec_size);
    blaze::DynamicVector<double> v2_blaze(vec_size);

    for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
        blaze::DynamicVector<double> sum = v1_blaze + v2_blaze;
    }
    toc = get_time();
    print_elapsed_time("    Blaze", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx xtensor case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    xt::xarray<double> v1_xtensor = xt::random::randn<double>({vec_size});
    xt::xarray<double> v2_xtensor = xt::random::randn<double>({vec_size});

    for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
        xt::xarray<double> sum = v1_xtensor + v2_xtensor;
    }
    toc = get_time();
    print_elapsed_time("    xtensor", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx eigen case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    Eigen::VectorXd v1_eigen = Eigen::VectorXd::Random(vec_size);
    Eigen::VectorXd v2_eigen = Eigen::VectorXd::Random(vec_size);
    for (unsigned int i = 0; i < num_reps_vec_sum; ++i) {
        Eigen::VectorXd sum = v1_eigen + v2_eigen;
    }
    toc = get_time();
    print_elapsed_time("    eigen", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    std::cout << "\n";

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    std::cout << "Multiply a vector and a matrix" << std::endl;

    // xxxxxxxxxx Armadillo case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    arma::mat m1_arma = arma::randu<arma::mat>(vec_size, vec_size);
    for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
      arma::vec prod = v1_arma * m1_arma;
    }
    toc = get_time();
    print_elapsed_time("    Armadillo", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx Blaze case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    blaze::DynamicMatrix<double> m1_blaze(vec_size, vec_size);
    for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
        blaze::DynamicVector<double> prod = m1_blaze * v1_blaze;
    }
    toc = get_time();
    print_elapsed_time("    Blaze", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx xtensor case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    xt::xarray<double> m1_xtensor =
        xt::random::randn<double>({vec_size, vec_size});

    m1_xtensor.reshape({vec_size, vec_size});

    for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
      xt::xarray<double> prod = xt::linalg::dot(v1_xtensor, m1_xtensor);
    }
    toc = get_time();
    print_elapsed_time("    xtensor", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx eigen case xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    Eigen::MatrixXd m1_eigen = Eigen::MatrixXd::Random(vec_size, vec_size);
    for (unsigned int i = 0; i < num_reps_vec_prod_mat; ++i) {
        Eigen::VectorXd prod = v1_eigen * m1_eigen;
    }
    toc = get_time();
    print_elapsed_time("    eigen", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    std::cout << "\n";

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    std::cout << "Invert a matrix" << std::endl;

    // xxxxxxxxxx Armadillo xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
        arma::mat inv = arma::inv(m1_arma);
    }
    toc = get_time();
    print_elapsed_time("    Armadillo", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx Blaze xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
        blaze::DynamicMatrix<double> inv = blaze::inv(m1_blaze);
    }
    toc = get_time();
    print_elapsed_time("    Blaze", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx xtensor xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
        xt::xarray<double> inv = xt::linalg::inv(m1_xtensor);
    }
    toc = get_time();
    print_elapsed_time("    xtensor", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // xxxxxxxxxx eigen xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    tic = get_time();
    for (unsigned int i = 0; i < num_reps_mat_inv; i++) {
      Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
          inv = Eigen::Inverse(m1_eigen);
    }
    toc = get_time();
    print_elapsed_time("    eigen", toc - tic);
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    return 0;
}
