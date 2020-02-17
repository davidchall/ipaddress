x <- c("::/128", "256::/72", "2001:db8::8a2e:370:7334/36", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/128")

test_that("formats correctly", {
  expect_equal(format(ip_network(x)), x)
})

test_that("invalid inputs are caught", {
  expect_warning(ip_network("1::2"), "Invalid argument")
  expect_warning(ip_address("1::g/24"), "Invalid argument")
  expect_warning(ip_network("1::-2/24"), "Invalid argument")
  expect_warning(ip_network("1:2/24"), "Invalid argument")
  expect_warning(ip_network("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/24"), "Invalid argument")
  expect_warning(ip_network("1::2/-1"), "Invalid argument")
  expect_warning(ip_network("1::2/129"), "Invalid argument")
  expect_warning(ip_network("1::2/a"), "Invalid argument")
  expect_warning(ip_network("1::2/24/24"), "Invalid argument")
})

test_that("equality operations work", {
  expect_true(all(vctrs::vec_equal(ip_network(x), ip_network(x))))
  expect_false(any(vctrs::vec_equal(ip_network(x), ip_network(rev(x)))))
})

test_that("comparison operations work", {
  shifter <- function(x, n = 1L) {
    if (n == 0) x else c(tail(x, -n), head(x, n))
  }
  expect_equal(
    vctrs::vec_compare(ip_network(x), ip_network(shifter(x, 1L))),
    c(rep(-1L, length(x) - 1L), 1L)
  )
  expect_equal(
    vctrs::vec_compare(ip_network(x), ip_network(shifter(x, -1L))),
    c(-1L, rep(1L, length(x) - 1L))
  )
})
