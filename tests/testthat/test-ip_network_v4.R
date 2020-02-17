x <- c("0.0.0.0/32", "192.168.0.0/16", "192.168.100.0/22", "255.255.255.255/32")

test_that("construction works", {
  expect_s3_class(ip_network(), c("ip_network", "vctrs_vctr"))
  expect_true(is_ip_network(ip_network(x)))
  expect_length(ip_network(), 0)
  expect_length(ip_network(x), length(x))
  expect_equal(as.character(ip_network(x)), x)
})

test_that("formats correctly", {
  expect_equal(format(ip_network(x)), x)
})

test_that("casting works", {
  expect_equal(vctrs::vec_cast(ip_network("198.51.100.0/24"), ip_network()), ip_network("198.51.100.0/24"))
  expect_equal(vctrs::vec_cast("198.51.100.0/24", ip_network()), ip_network("198.51.100.0/24"))
  expect_equal(vctrs::vec_cast(ip_network("198.51.100.0/24"), character()), "198.51.100.0/24")

  # since R only provides signed integers, we don't support integer casting
  expect_error(vctrs::vec_cast(ip_network("198.51.100.0/24"), integer()), class = "vctrs_error_incompatible_cast")
  expect_error(vctrs::vec_cast(1L, ip_network()), class = "vctrs_error_incompatible_cast")
})

test_that("coercion works", {
  expect_equal(vctrs::vec_ptype2(ip_network(), ip_network()), ip_network())
  expect_equal(vctrs::vec_ptype2(ip_network(), "198.51.100.0/24"), ip_network())
  expect_equal(vctrs::vec_ptype2("198.51.100.0/24", ip_network()), ip_network())

  # since R only provides signed integers, we don't support integer coercion
  expect_error(vctrs::vec_ptype2(ip_network("198.51.100.0/24"), integer()), class = "vctrs_error_incompatible_type")
  expect_error(vctrs::vec_ptype2(1L, ip_network()), class = "vctrs_error_incompatible_type")
})

test_that("missing values work", {
  expect_equal(field(ip_network(NA), "address1"), NA_integer_)
  expect_equal(ip_network(c(x, NA)), c(ip_network(x), NA))
  expect_equal(as.character(ip_network(c(x, NA))), c(x, NA))
  expect_equal(is.na(ip_network(c(x, NA))), c(rep(FALSE, length(x)), TRUE))
})

test_that("invalid inputs are caught", {
  expect_warning(ip_network("abc"), "Invalid argument")
  expect_warning(ip_network("1.2.3.4"), "Invalid argument")
  expect_warning(ip_network("1.2.3.256/24"), "Invalid argument")
  expect_warning(ip_network("1.2.3.-1/24"), "Invalid argument")
  expect_warning(ip_network("1.2.3/24"), "Invalid argument")
  expect_warning(ip_network("1.2.3.4.5/24"), "Invalid argument")
  expect_warning(ip_network("1.2.3.4/-1"), "Invalid argument")
  expect_warning(ip_network("1.2.3.4/33"), "Invalid argument")
  expect_warning(ip_network("1.2.3.4/a"), "Invalid argument")
  expect_warning(ip_network("1.2.3.4/24/24"), "Invalid argument")
})

test_that("strict argument works", {
  expect_warning(ip_network("255.255.255.255/21"), "host bits set")
  expect_equal(ip_network("255.255.255.255/21", strict = FALSE), ip_network("255.255.248.0/21"))
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
