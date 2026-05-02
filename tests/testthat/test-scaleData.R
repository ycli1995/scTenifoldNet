
test_that("scaleData", {
  mat <- Matrix::rsparsematrix(20, 10, density = 0.5)
  rownames(mat) <- letters[1:20]
  colnames(mat) <- LETTERS[1:10]
  
  ans <- Matrix::t(scale(Matrix::t(mat)))
  
  ans1 <- scaleData(mat, scale.max = Inf)
  ans2 <- scaleData(as.matrix(mat), scale.max = Inf)
  
  expect_equal(ans1, ans, ignore_attr = TRUE)
  expect_equal(ans2, ans, ignore_attr = TRUE)
})
