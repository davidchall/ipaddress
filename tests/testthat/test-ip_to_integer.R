x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("integer encoding/decoding works", {
  expect_error(ip_to_integer("hello"), "`x` must be an ip_address vector")
  expect_error(integer_to_ip(1.5), "`x` must be a character vector")
  expect_error(integer_to_ip(x), "`x` must be a character vector")
  expect_error(integer_to_ip("1", is_ipv6 = "true"), "`is_ipv6` must be a logical vector or NULL")

  expect_type(ip_to_integer(x), "character")
  expect_s3_class(integer_to_ip("1"), "ip_address")

  expect_equal(
    ip_to_integer(x),
    c("3232235521", "42540766411282592856904136881884656436", NA)
  )
  expect_equal(
    ip_to_integer(x, base = "hex"),
    c("0xC0A80001", "0x20010DB80000000000008A2E03707334", NA)
  )
  expect_equal(ip_to_integer(x, base = "bin"), ip_to_binary(x))

  # zero padding
  expect_equal(ip_to_integer(ip_address("0.0.0.0"), base = "hex"), paste0("0x", strrep("0", 8)))
  expect_equal(ip_to_integer(ip_address("::"), base = "hex"), paste0("0x", strrep("0", 32)))

  expect_equal(integer_to_ip("1", is_ipv6 = NULL), ip_address("0.0.0.1"))
  expect_equal(integer_to_ip("1", is_ipv6 = c(FALSE, TRUE)), ip_address(c("0.0.0.1", "::1")))
  expect_equal(integer_to_ip(ip_to_integer(x)), x)
  expect_equal(integer_to_ip(c(0, 3232235521, 4294967295)), ip_address(c("0.0.0.0", "192.168.0.1", "255.255.255.255")))

  expect_warning(integer_to_ip("hello"))
  expect_warning(integer_to_ip("-1"))
  expect_warning(integer_to_ip(as.character(2^32), is_ipv6 = FALSE))
  expect_warning(integer_to_ip("-1", is_ipv6 = TRUE))
})
