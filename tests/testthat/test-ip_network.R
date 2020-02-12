# underlying data is a 32-bit integer and R only supports signed integers
host_int <- c(0L, 1L, -1062731775L, -1L)
prefix_int <- c(32L, 32L, 32L, 32L)
x <- c("0.0.0.0/32", "0.0.0.1/32", "192.168.0.1/32", "255.255.255.255/32")

test_that("construction works", {
  expect_s3_class(ip_network(), c("vctrs_ip_network", "vctrs_vctr"))
  expect_equal(ip_network(x), new_ip_network(host_int, prefix_int))
  expect_true(is_ip_network(ip_network(x)))
  expect_length(ip_network(), 0)
  expect_length(ip_network(x), length(x))
})

test_that("formats correctly", {
  expect_equal(format(ip_network(x)), x)
})

test_that("casting works", {
  expect_equal(vctrs::vec_cast(ip_network("1.2.3.4/5"), ip_network()), ip_network("1.2.3.4/5"))
  expect_equal(vctrs::vec_cast("1.2.3.4/5", ip_network()), ip_network("1.2.3.4/5"))
  expect_equal(vctrs::vec_cast(ip_network("1.2.3.4/5"), character()), "1.2.3.4/5")

  # since R only provides signed integers, we don't support integer casting
  expect_error(vctrs::vec_cast(ip_network("1.2.3.4/5"), integer()), class = "vctrs_error_incompatible_cast")
  expect_error(vctrs::vec_cast(1L, ip_network()), class = "vctrs_error_incompatible_cast")
})

test_that("coercion works", {
  expect_equal(vctrs::vec_ptype2(ip_network(), ip_network()), ip_network())
  expect_equal(vctrs::vec_ptype2(ip_network(), "1.2.3.4/5"), ip_network())
  expect_equal(vctrs::vec_ptype2("1.2.3.4/5", ip_network()), ip_network())

  # since R only provides signed integers, we don't support integer coercion
  expect_error(vctrs::vec_ptype2(ip_network("1.2.3.4/5"), integer()), class = "vctrs_error_incompatible_type")
  expect_error(vctrs::vec_ptype2(1L, ip_network()), class = "vctrs_error_incompatible_type")
})

test_that("missing values work", {
  # TODO: expect_equal(ip_network(NA), NA)
  expect_equal(ip_network(c(x, NA)), c(ip_network(x), NA))
  expect_equal(is.na(ip_network(c(x, NA))), c(rep(FALSE, length(x)), TRUE))
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

test_that("arithmetic operations work", {
  expect_error(+ip_network(x), class = "vctrs_error_incompatible_op")
  expect_error(-ip_network(x), class = "vctrs_error_incompatible_op")

  expect_error(ip_network(x) + ip_network(x), class = "vctrs_error_incompatible_op")
  expect_error(ip_network(x) - ip_network(x), class = "vctrs_error_incompatible_op")
  expect_error(ip_network(x) / ip_network(x), class = "vctrs_error_incompatible_op")
  expect_error(ip_network(x) * ip_network(x), class = "vctrs_error_incompatible_op")
  expect_error(ip_network(x) ^ ip_network(x), class = "vctrs_error_incompatible_op")
  expect_error(ip_network(x) %% ip_network(x), class = "vctrs_error_incompatible_op")
  expect_error(ip_network(x) %/% ip_network(x), class = "vctrs_error_incompatible_op")

  expect_error(ip_network(x) + 1L, class = "vctrs_error_incompatible_op")
  expect_error(ip_network(x) - 1L, class = "vctrs_error_incompatible_op")
})
