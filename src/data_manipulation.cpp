#include "fast_stats.h"
#include "data_manipulation.h"

using namespace Rcpp;
// [[Rcpp::depends(RcppEigen)]]

// [[Rcpp::export(rng = false)]]
Eigen::MatrixXd dgcmatrix_row_scale(
    Eigen::Map<Eigen::SparseMatrix<double>> mat,
    bool scale = true,
    bool center = true,
    double scale_max = 10
) {
  std::vector<double> mu, sigma;
  if (center) {
    mu = dgcmatrix_rowmeans(mat);
    if (scale) {
      sigma = dgcmatrix_rowvars_know_means(mat, mu);
    }
  } else {
    if (scale) {
      sigma = dgcmatrix_rowvars(mat);
    }
  }
  Eigen::MatrixXd scaled_mat = dgcmatrix_row_scale2(
    mat, mu, sigma, scale, center, scale_max
  );
  return scaled_mat;
}

// [[Rcpp::export(rng = false)]]
Eigen::MatrixXd dgcmatrix_row_scale2(
    Eigen::Map<Eigen::SparseMatrix<double>> mat,
    std::vector<double> &mu,
    std::vector<double> &sigma,
    bool scale = true,
    bool center = true,
    double scale_max = 10
) {
  Eigen::MatrixXd scaled_mat(mat.rows(), mat.cols());
  for (int i = 0; i < mat.cols(); ++i) {
    scaled_mat.col(i) = mat.col(i);
    for (int j = 0; j < mat.rows(); ++j) {
      if (center) {
        scaled_mat(j, i) -= mu[j];
      }
      if (scale) {
        scaled_mat(j, i) /= std::sqrt(sigma[j]);
      }
      if (scaled_mat(j, i) > scale_max) {
        scaled_mat(j, i) = scale_max;
      }
    }
  }
  return scaled_mat;
}
