x <- c("0.0.0.0/32", "192.168.0.0/16", "192.168.100.0/22", "255.255.255.255/32")

test_that("construction works", {
  expect_s3_class(ip_network(), c("ip_network", "vctrs_rcrd", "vctrs_vctr"), exact = TRUE)
  expect_true(is_ip_network(ip_network(x)))
  expect_length(ip_network(), 0)
  expect_length(ip_network(x), length(x))
  expect_equal(ip_network(x), as_ip_network(x))
  expect_equal(as.character(ip_network(x)), x)
  expect_equal(vec_ptype_abbr(ip_network(x)), "ip_netwk")

  expect_error(as_ip_network(1L))

  expect_equal(
    ip_network(x),
    ip_network(ip_address(c("0.0.0.0", "192.168.0.0", "192.168.100.0", "255.255.255.255")), c(32L, 16L, 22L, 32L))
  )

  # vector recycling
  expect_equal(
    ip_network(ip_address(rep("0.0.0.0", 3)), 24L),
    ip_network(rep("0.0.0.0/24", 3))
  )
  expect_equal(
    ip_network(ip_address("0.0.0.0"), rep(24L, 3)),
    ip_network(rep("0.0.0.0/24", 3))
  )
  expect_error(ip_network(ip_address(rep("0.0.0.0", 3)), rep(24L, 2)), class = "vctrs_error_incompatible_size")
})

test_that("formats correctly", {
  expect_equal(format(ip_network(x)), x)
  expect_equal(format(ip_network(x), exploded = TRUE), x)
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
  expect_warning(ip_network("abc"))
  expect_warning(ip_network("1.2.3.4"))
  expect_warning(ip_network("1.2.3.256/24"))
  expect_warning(ip_network("1.2.3.-1/24"))
  expect_warning(ip_network("1.2.3/24"))
  expect_warning(ip_network("1.2.3.4.5/24"))
  expect_warning(ip_network("1.2.3.4/-1"))
  expect_warning(ip_network("1.2.3.4/33"))
  expect_warning(ip_network("1.2.3.4/a"))
  expect_warning(ip_network("1.2.3.4/24/24"))

  expect_error(ip_network(ip_address("1.2.3.4"), 24.5), "`prefix_length` must be an integer vector")
  expect_warning(ip_network(ip_address("1.2.3.4"), -1L))
  expect_warning(ip_network(ip_address("1.2.3.4"), 33L))
})

test_that("strict argument works", {
  expect_error(ip_network("1.2.3.4/32", strict = "yes"), "`strict` be must TRUE or FALSE")
  expect_error(ip_network("1.2.3.4/32", strict = NA), "`strict` be must TRUE or FALSE")
  expect_error(ip_network(ip_address("1.2.3.4"), prefix_length = 32L, strict = "yes"), "`strict` be must TRUE or FALSE")
  expect_error(ip_network(ip_address("1.2.3.4"), prefix_length = 32L, strict = NA), "`strict` be must TRUE or FALSE")

  expect_warning(ip_network("255.255.255.255/21"), "host bits set")
  expect_equal(ip_network("255.255.255.255/21", strict = FALSE), ip_network("255.255.248.0/21"))

  expect_warning(ip_network(ip_address("255.255.255.255"), 21L), "host bits set")
  expect_equal(ip_network(ip_address("255.255.255.255"), 21L, strict = FALSE), ip_network("255.255.248.0/21"))
})

test_that("equality operations work", {
  expect_true(all(ip_network(x) == ip_network(x)))
  expect_false(any(ip_network(x) == ip_network(rev(x))))
  expect_false(ip_network("192.168.0.0/16") == ip_network("192.168.0.0/20"))
})

test_that("comparison operations work", {
  shifter <- function(x, n = 1L) {
    if (n == 0) x else c(tail(x, -n), head(x, n))
  }
  expect_equal(
    vec_compare(ip_network(x), ip_network(shifter(x, 1L))),
    c(rep(-1L, length(x) - 1L), 1L)
  )
  expect_equal(
    vec_compare(ip_network(x), ip_network(shifter(x, -1L))),
    c(-1L, rep(1L, length(x) - 1L))
  )
  expect_equal(vec_compare(ip_network("192.168.0.0/16"), ip_network(NA)), NA_integer_)

  # network address compared before prefix length
  expect_true(ip_network("192.168.0.0/24") > ip_network("192.168.0.0/23"))
  expect_true(ip_network("192.168.4.0/22") > ip_network("192.168.0.0/23"))
})
