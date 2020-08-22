x <- c("192.168.0.1/10", "2001:db8::abcd/32")

test_that("construction works", {
  expect_s3_class(ip_interface(), c("ip_interface", "ip_address", "vctrs_rcrd", "vctrs_vctr"), exact = TRUE)
  expect_true(is_ip_interface(ip_interface(x)))
  expect_length(ip_interface(), 0)
  expect_length(ip_interface(x), length(x))
  expect_equal(ip_interface(x), as_ip_interface(x))
  expect_equal(as.character(ip_interface(x)), x)
  expect_equal(format(ip_interface(x)), x)
  expect_equal(vec_ptype_abbr(ip_interface(x)), "ip_intf")

  expect_error(as_ip_interface(1L))

  expect_equal(
    ip_interface(x),
    ip_interface(ip_address(c("192.168.0.1", "2001:db8::abcd")), c(10L, 32L))
  )

  # vector recycling
  expect_equal(
    ip_interface(ip_address(rep("0.0.0.0", 3)), 24L),
    ip_interface(rep("0.0.0.0/24", 3))
  )
  expect_equal(
    ip_interface(ip_address("0.0.0.0"), rep(24L, 3)),
    ip_interface(rep("0.0.0.0/24", 3))
  )
  expect_error(ip_interface(ip_address(rep("0.0.0.0", 3)), rep(24L, 2)), class = "vctrs_error_incompatible_size")
})

test_that("formats correctly", {
  expect_equal(format(ip_interface(x)), x)
  expect_equal(format(ip_interface("2001:0db8:85a3:0000:0000:8a2e:0370:7334/32")), "2001:db8:85a3::8a2e:370:7334/32")
  expect_equal(format(ip_interface("2001:db8:85a3::8a2e:370:7334/32"), exploded = TRUE), "2001:0db8:85a3:0000:0000:8a2e:0370:7334/32")
})

test_that("can extract address and network", {
  expect_equal(
    as_ip_address(ip_interface(x)),
    ip_address(c("192.168.0.1", "2001:db8::abcd"))
  )
  expect_equal(
    as_ip_network(ip_interface(x)),
    ip_network(c("192.128.0.0/10", "2001:db8::/32"))
  )
})

test_that("missing values work", {
  expect_equal(field(ip_interface(NA), "is_ipv6"), NA)
  expect_equal(ip_interface(c(x, NA)), c(ip_interface(x), NA))
  expect_equal(as.character(ip_interface(c(x, NA))), c(x, NA))
  expect_equal(is.na(ip_interface(c(x, NA))), c(rep(FALSE, length(x)), TRUE))
  expect_equal(ip_interface(ip_address(NA), 32L), ip_interface(NA))
  expect_equal(ip_interface(ip_address("0.0.0.0"), NA_integer_), ip_interface(NA))
})

test_that("invalid inputs are caught", {
  expect_warning(ip_interface("192.168.0.1"))
  expect_error(ip_interface(ip_address("192.168.0.1"), 24.5), "`prefix_length` must be an integer vector")
  expect_warning(ip_interface(ip_address("192.168.0.1"), -1L))
})

test_that("equality operations work", {
  expect_true(all(ip_interface(x) == ip_interface(x)))
  expect_false(any(ip_interface(x) == rev(ip_interface(x))))
  expect_false(ip_interface("192.168.0.1/22") == ip_interface("192.168.0.1/23"))

  expect_error(ip_interface("0.0.0.0/32") == ip_address("0.0.0.0"), class = "vctrs_error_incompatible_type")
  expect_error(ip_address("0.0.0.0") == ip_interface("0.0.0.0/32"), class = "vctrs_error_incompatible_type")
  expect_error(ip_interface("0.0.0.0/32") == ip_network("0.0.0.0/32"), class = "vctrs_error_incompatible_type")
  expect_error(ip_network("0.0.0.0/32") == ip_interface("0.0.0.0/32"), class = "vctrs_error_incompatible_type")
})

test_that("comparison operations work", {
  expect_true(ip_interface("192.168.0.1/10") > ip_interface("192.168.0.0/10"))
  expect_true(ip_interface("2001:db8::abcd/32") > ip_interface("2001:db8::abc0/32"))

  # network compared before address
  expect_true(ip_interface("192.168.0.0/24") > ip_interface("192.168.0.1/23"))
  expect_true(ip_interface("192.168.0.1/23") > ip_interface("192.168.0.0/23"))

  expect_error(ip_interface("0.0.0.0/32") > ip_address("0.0.0.0"), class = "vctrs_error_incompatible_type")
  expect_error(ip_address("0.0.0.0") > ip_interface("0.0.0.0/32"), class = "vctrs_error_incompatible_type")
  expect_error(ip_interface("0.0.0.0/32") > ip_network("0.0.0.0/32"), class = "vctrs_error_incompatible_type")
  expect_error(ip_network("0.0.0.0/32") > ip_interface("0.0.0.0/32"), class = "vctrs_error_incompatible_type")
})

test_that("arithmetic operations disabled", {
  expect_error(!ip_interface("192.168.0.1/10"), class = "vctrs_error_incompatible_op")
  expect_error(ip_interface("192.168.0.1/10") + 1L, class = "vctrs_error_incompatible_op")
  expect_error(ip_interface("192.168.0.1/10") & ip_interface("192.168.0.1/10"), class = "vctrs_error_incompatible_op")
  expect_error(ip_interface("192.168.0.1/10") & ip_address("192.168.0.1"), class = "vctrs_error_incompatible_op")
  expect_error(ip_address("192.168.0.1") & ip_interface("192.168.0.1/10"), class = "vctrs_error_incompatible_op")
})
