x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("integer encoding/decoding works", {
  skip_if_not_installed("bignum")

  expect_error(ip_to_integer("hello"), "`x` must be an ip_address vector")
  expect_error(integer_to_ip(1.5), class = "vctrs_error_cast_lossy")
  expect_error(integer_to_ip(x), class = "vctrs_error_incompatible_type")
  expect_error(integer_to_ip(1, is_ipv6 = "true"), "`is_ipv6` must be a logical vector or NULL")

  expect_type(ip_to_integer(x), "character")
  expect_s3_class(integer_to_ip(1), "ip_address")

  expect_equal(
    ip_to_integer(x),
    bignum::biginteger(c("3232235521", "42540766411282592856904136881884656436", NA))
  )

  expect_equal(integer_to_ip(1, is_ipv6 = c(FALSE, TRUE)), ip_address(c("0.0.0.1", "::1")))
  expect_equal(
    integer_to_ip(bignum::biginteger(2)^32L + -1:1),
    ip_address(c("255.255.255.255", "::1:0:0", "::1:0:1"))
  )

  expect_equal(integer_to_ip(ip_to_integer(x)), x)

  expect_equal(integer_to_ip(bignum::biginteger(-1)), ip_address(NA))
  expect_warning(expect_equal(
    integer_to_ip(bignum::biginteger(2)^32L + c(-1L, 0, NA), is_ipv6 = FALSE),
    ip_address(c("255.255.255.255", NA, NA))
  ))
  expect_warning(expect_equal(
    integer_to_ip(bignum::biginteger(2)^128L + c(-1L, 0, NA), is_ipv6 = TRUE),
    ip_address(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", NA, NA))
  ))
})
