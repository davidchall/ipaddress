x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("bytes encoding/decoding works", {
  expect_error(ip_to_bytes("hello"), "`x` must be an ip_address vector")
  expect_error(bytes_to_ip("hello"), "`x` must be a blob object")
  expect_error(bytes_to_ip(x), "`x` must be a blob object")

  expect_s3_class(ip_to_bytes(x), c("blob", "vctrs_vctr"))
  expect_equal(
    ip_to_bytes(x),
    blob::blob(
      as.raw(c(0xc0, 0xa8, 0x00, 0x01)),
      as.raw(c(0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34)),
      NULL
    )
  )
  expect_equal(bytes_to_ip(ip_to_bytes(x)), x)

  expect_warning(bytes_to_ip(blob::blob(as.raw(10))), "unable to decode")
})
