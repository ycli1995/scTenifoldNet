
#include <Rcpp.h>
#include <RcppEigen.h>

#include "fast_stats.h"

Eigen::MatrixXd dgcmatrix_row_scale(
    Eigen::Map<Eigen::SparseMatrix<double>> mat,
    bool scale,
    bool center,
    double scale_max
);

Eigen::MatrixXd dgcmatrix_row_scale2(
    Eigen::Map<Eigen::SparseMatrix<double>> mat,
    std::vector<double> &mu,
    std::vector<double> &sigma,
    bool scale,
    bool center,
    double scale_max
);
