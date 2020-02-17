x <- c("1.2.3.0", "2001:ff00::")

test_that("is_ipv4 and is_ipv6 work", {
  expect_equal(is_ipv4(ip_address(x)), c(TRUE, FALSE))
  expect_equal(is_ipv6(ip_address(x)), c(FALSE, TRUE))
  expect_equal(is_ipv4(ip_network(paste0(x, "/24"))), c(TRUE, FALSE))
  expect_equal(is_ipv6(ip_network(paste0(x, "/24"))), c(FALSE, TRUE))
})

test_that("input validation works", {
  expect_error(is_ipv4(1L), "not an ip_address vector or (.) is not an ip_network vector")
  expect_error(is_ipv6(1L), "not an ip_address vector or (.) is not an ip_network vector")
})
