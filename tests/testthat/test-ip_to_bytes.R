address <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
bytes <- list(
  as.raw(c(0xc0, 0xa8, 0x00, 0x01)),
  as.raw(c(0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34)),
  NULL
)

test_that("encoding works", {
  expect_error(ip_to_bytes("hello"), "`x` must be an ip_address vector")

  expect_type(ip_to_bytes(address), "list")
  expect_equal(ip_to_bytes(address), bytes)
})

test_that("decoding works", {
  expect_error(bytes_to_ip("hello"), "`x` must be a list of raw vectors")
  expect_error(bytes_to_ip(address), "`x` must be a list of raw vectors")
  expect_error(bytes_to_ip(c(bytes, "a")), "`x` must be a list of raw vectors")

  expect_warning(bytes_to_ip(list(as.raw(10))), "unable to decode")

  expect_equal(bytes_to_ip(bytes), address)
})
