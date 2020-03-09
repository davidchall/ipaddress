x <- c("0.0.0.0", "0.0.0.1", "192.168.0.1", "255.255.255.255")

test_that("construction works", {
  expect_s3_class(ip_address(), c("ip_address", "vctrs_vctr"))
  expect_true(is_ip_address(ip_address(x)))
  expect_length(ip_address(), 0)
  expect_length(ip_address(x), length(x))
  expect_equal(as.character(ip_address(x)), x)
})

test_that("formats correctly", {
  expect_equal(format(ip_address(x)), x)
})

test_that("casting works", {
  expect_equal(vctrs::vec_cast(ip_address("1.2.3.4"), ip_address()), ip_address("1.2.3.4"))
  expect_equal(vctrs::vec_cast("1.2.3.4", ip_address()), ip_address("1.2.3.4"))
  expect_equal(vctrs::vec_cast(ip_address("1.2.3.4"), character()), "1.2.3.4")

  # since R only provides signed integers, we don't support integer casting
  expect_error(vctrs::vec_cast(ip_address("1.2.3.4"), integer()), class = "vctrs_error_incompatible_cast")
  expect_error(vctrs::vec_cast(1L, ip_address()), class = "vctrs_error_incompatible_cast")
})

test_that("coercion works", {
  expect_equal(vctrs::vec_ptype2(ip_address(), ip_address()), ip_address())
  expect_equal(vctrs::vec_ptype2(ip_address(), "1.2.3.4"), ip_address())
  expect_equal(vctrs::vec_ptype2("1.2.3.4", ip_address()), ip_address())

  # since R only provides signed integers, we don't support integer coercion
  expect_error(vctrs::vec_ptype2(ip_address("1.2.3.4"), integer()), class = "vctrs_error_incompatible_type")
  expect_error(vctrs::vec_ptype2(1L, ip_address()), class = "vctrs_error_incompatible_type")
})

test_that("missing values work", {
  expect_equal(field(ip_address(NA), "is_ipv6"), NA)
  expect_equal(ip_address(c(x, NA)), c(ip_address(x), NA))
  expect_equal(as.character(ip_address(c(x, NA))), c(x, NA))
  expect_equal(is.na(ip_address(c(x, NA))), c(rep(FALSE, length(x)), TRUE))
})

test_that("invalid inputs are caught", {
  expect_warning(ip_address("1.2.3.4/5"), "Invalid argument")
  expect_warning(ip_address("abc"), "Invalid argument")
  expect_warning(ip_address("1.2.3.256"), "Invalid argument")
  expect_warning(ip_address("1.2.3.-1"), "Invalid argument")
  expect_warning(ip_address("1.2.3.4.5"), "Invalid argument")

  # Windows accepts IP addresses in alternative formats: https://superuser.com/a/486936
  skip_on_os("windows")
  expect_warning(ip_address("1.2.3"), "Invalid argument")
})

test_that("equality operations work", {
  expect_true(all(vctrs::vec_equal(ip_address(x), ip_address(x))))
  expect_false(any(vctrs::vec_equal(ip_address(x), ip_address(rev(x)))))
})

test_that("comparison operations work", {
  shifter <- function(x, n = 1L) {
    if (n == 0) x else c(tail(x, -n), head(x, n))
  }
  expect_equal(
    vctrs::vec_compare(ip_address(x), ip_address(shifter(x, 1L))),
    c(rep(-1L, length(x) - 1L), 1L)
  )
  expect_equal(
    vctrs::vec_compare(ip_address(x), ip_address(shifter(x, -1L))),
    c(-1L, rep(1L, length(x) - 1L))
  )
})
