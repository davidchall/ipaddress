x <- c("1.2.3.0", "2001:ff00::")

test_that("is_ipv4 and is_ipv6 work", {
  expect_equal(is_ipv4(ip_address(x)), c(TRUE, FALSE))
  expect_equal(is_ipv6(ip_address(x)), c(FALSE, TRUE))
  expect_equal(is_ipv4(ip_network(paste0(x, "/24"))), c(TRUE, FALSE))
  expect_equal(is_ipv6(ip_network(paste0(x, "/24"))), c(FALSE, TRUE))
})

test_that("max_prefix_length works", {
  expect_equal(max_prefix_length(ip_address(x)), c(32L, 128L))
  expect_equal(max_prefix_length(ip_network(paste0(x, "/24"))), c(32L, 128L))
})

test_that("input validation works", {
  expect_error(is_ipv4(1L), "`x` must be an ip_address or ip_network vector")
  expect_error(is_ipv6(1L), "`x` must be an ip_address or ip_network vector")
  expect_error(max_prefix_length(1L), "`x` must be an ip_address or ip_network vector")
})
