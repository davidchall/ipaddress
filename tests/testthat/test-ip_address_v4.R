x <- c("0.0.0.0", "0.0.0.1", "192.168.0.1", "255.255.255.255")

test_that("construction works", {
  expect_s3_class(ip_address(), c("ip_address", "vctrs_rcrd", "vctrs_vctr"), exact = TRUE)
  expect_true(is_ip_address(ip_address(x)))
  expect_length(ip_address(), 0)
  expect_length(ip_address(x), length(x))
  expect_equal(ip_address(x), as_ip_address(x))
  expect_equal(as.character(ip_address(x)), x)
  expect_equal(vec_ptype_abbr(ip_address(x)), "ip_addr")

  expect_error(as_ip_address(1L))
})

test_that("formats correctly", {
  expect_equal(format(ip_address(x)), x)
  expect_equal(format(ip_address(x), exploded = TRUE), x)
})

test_that("missing values work", {
  expect_equal(field(ip_address(NA), "is_ipv6"), NA)
  expect_equal(ip_address(c(x, NA)), c(ip_address(x), NA))
  expect_equal(as.character(ip_address(c(x, NA))), c(x, NA))
  expect_equal(is.na(ip_address(c(x, NA))), c(rep(FALSE, length(x)), TRUE))
})

test_that("invalid inputs are caught", {
  expect_warning(ip_address("1.2.3.4/5"))
  expect_warning(ip_address("abc"))
  expect_warning(ip_address("1.2.3.256"))
  expect_warning(ip_address("1.2.3.-1"))
  expect_warning(ip_address("1.2.3.4.5"))

  # Windows accepts IP addresses in alternative formats: https://superuser.com/a/486936
  skip_on_os("windows")
  expect_warning(ip_address("1.2.3"))
})

test_that("equality operations work", {
  expect_true(all(ip_address(x) == ip_address(x)))
  expect_false(any(ip_address(x) == ip_address(rev(x))))
})

test_that("comparison operations work", {
  shifter <- function(x, n = 1L) {
    if (n == 0) x else c(tail(x, -n), head(x, n))
  }
  expect_equal(
    vec_compare(ip_address(x), ip_address(shifter(x, 1L))),
    c(rep(-1L, length(x) - 1L), 1L)
  )
  expect_equal(
    vec_compare(ip_address(x), ip_address(shifter(x, -1L))),
    c(-1L, rep(1L, length(x) - 1L))
  )
  expect_equal(vec_compare(ip_address("192.168.0.1"), ip_address(NA)), NA_integer_)

  # not effected by machine byte-endianness
  expect_true(ip_address("255.128.0.0") > ip_address("0.0.128.255"))
})
