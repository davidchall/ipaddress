x <- c("0.0.0.0/32", "192.168.0.0/16", "192.168.100.0/22", "255.255.255.255/32")

test_that("construction works", {
  expect_s3_class(ip_network(), c("ip_network", "vctrs_vctr"))
  expect_true(is_ip_network(ip_network(x)))
  expect_length(ip_network(), 0)
  expect_length(ip_network(x), length(x))
  expect_equal(as.character(ip_network(x)), x)

  expect_equal(
    ip_network(x),
    ip_network(ip_address(c("0.0.0.0", "192.168.0.0", "192.168.100.0", "255.255.255.255")), c(32L, 16L, 22L, 32L))
  )
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
  expect_equal(field(ip_network(NA), "is_ipv6"), NA)
  expect_equal(ip_network(c(x, NA)), c(ip_network(x), NA))
  expect_equal(as.character(ip_network(c(x, NA))), c(x, NA))
  expect_equal(is.na(ip_network(c(x, NA))), c(rep(FALSE, length(x)), TRUE))
  expect_equal(ip_network(ip_address(NA), 32L), ip_network(NA))
  expect_equal(ip_network(ip_address("0.0.0.0"), NA_integer_), ip_network(NA))
})

test_that("invalid inputs are caught", {
  expect_warning(ip_network("abc"), "Invalid value")
  expect_warning(ip_network("1.2.3.4"), "Invalid value")
  expect_warning(ip_network("1.2.3.256/24"), "Invalid value")
  expect_warning(ip_network("1.2.3.-1/24"), "Invalid value")
  expect_warning(ip_network("1.2.3/24"), "Invalid value")
  expect_warning(ip_network("1.2.3.4.5/24"), "Invalid value")
  expect_warning(ip_network("1.2.3.4/-1"), "Invalid value")
  expect_warning(ip_network("1.2.3.4/33"), "Invalid value")
  expect_warning(ip_network("1.2.3.4/a"), "Invalid value")
  expect_warning(ip_network("1.2.3.4/24/24"), "Invalid value")

  expect_error(ip_network(ip_address("1.2.3.4"), 24), "not an integer")
  expect_warning(ip_network(ip_address("1.2.3.4"), -1L), "Invalid value")
  expect_warning(ip_network(ip_address("1.2.3.4"), 33L), "Invalid value")
})

test_that("strict argument works", {
  expect_error(ip_network("1.2.3.4/32", strict = "yes"), "not a flag")
  expect_error(ip_network("1.2.3.4/32", strict = NA), "contains 1 missing values")

  expect_warning(ip_network("255.255.255.255/21"), "host bits set")
  expect_equal(ip_network("255.255.255.255/21", strict = FALSE), ip_network("255.255.248.0/21"))

  expect_warning(ip_network(ip_address("255.255.255.255"), 21L), "host bits set")
  expect_equal(ip_network(ip_address("255.255.255.255"), 21L, strict = FALSE), ip_network("255.255.248.0/21"))
})

test_that("equality operations work", {
  expect_true(all(vctrs::vec_equal(ip_network(x), ip_network(x))))
  expect_false(any(vctrs::vec_equal(ip_network(x), ip_network(rev(x)))))
  expect_false(vctrs::vec_equal(ip_network("192.168.0.0/16"), ip_network("192.168.0.0/20")))
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
  expect_equal(vec_compare(ip_network("192.168.0.0/16"), ip_network(NA)), NA_integer_)
})

test_that("extracting basic info works", {
  expect_equal(prefix_length(ip_network(x)), c(32L, 16L, 22L, 32L))
  expect_equal(num_addresses(ip_network(x)), c(1, 65536, 1024, 1))
  expect_equal(
    network_address(ip_network(x)),
    ip_address(c("0.0.0.0", "192.168.0.0", "192.168.100.0", "255.255.255.255"))
  )
  expect_equal(
    broadcast_address(ip_network(x)),
    ip_address(c("0.0.0.0", "192.168.255.255", "192.168.103.255", "255.255.255.255"))
  )

  expect_error(prefix_length(ip_address("192.168.0.1")), "not an ip_network")
  expect_error(num_addresses(ip_address("192.168.0.1")), "not an ip_network")
  expect_error(network_address(ip_address("192.168.0.1")), "not an ip_network")
  expect_error(broadcast_address(ip_address("192.168.0.1")), "not an ip_network")

  expect_equal(prefix_length(ip_network(NA)), NA_integer_)
  expect_equal(num_addresses(ip_network(NA)), NA_real_)
  expect_equal(network_address(ip_network(NA)), ip_address(NA))
  expect_equal(broadcast_address(ip_network(NA)), ip_address(NA))

  expect_equal(
    ip_network(x),
    ip_network(network_address(ip_network(x)), prefix_length(ip_network(x)))
  )
})
