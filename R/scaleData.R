#' @importFrom Seurat FastRowScale
NULL

#' @export
scaleData <- function(mat, ...) {
  UseMethod("scaleData", mat)
}

#' @export
#' @method scaleData matrix
scaleData.matrix <- function(
    mat,
    scale = TRUE,
    center = TRUE,
    scale.max = 10,
    ...
) {
  FastRowScale(mat, center = center, scale = scale, scale_max = scale.max)
}

#' @export
#' @method scaleData dgCMatrix
scaleData.dgCMatrix <- function(
    mat,
    scale = TRUE,
    center = TRUE,
    scale.max = 10,
    ...
) {
  mat.dimns <- dimnames(mat)
  mat <- dgcmatrix_row_scale(mat, scale, center, scale.max)
  dimnames(mat) <- mat.dimns
  mat[is.na(mat)] <- 0
  mat
}
