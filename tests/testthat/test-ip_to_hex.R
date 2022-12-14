x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("hex encoding/decoding works", {
  expect_snapshot(error = TRUE, {
    ip_to_hex("hello")
  })
  expect_snapshot(error = TRUE, {
    hex_to_ip(x)
    hex_to_ip("0xff", is_ipv6 = "true")
  })

  expect_type(ip_to_hex(x), "character")
  expect_s3_class(hex_to_ip("0xff"), "ip_address")

  expect_equal(
    ip_to_hex(x),
    c("0xC0A80001", "0x20010DB80000000000008A2E03707334", NA)
  )

  expect_equal(hex_to_ip("0x1", is_ipv6 = c(FALSE, TRUE)), ip_address(c("0.0.0.1", "::1")))
  expect_equal(
    hex_to_ip(c("0xFFFFFFFF", "0x100000000", "0x100000001")),
    ip_address(c("255.255.255.255", "::1:0:0", "::1:0:1"))
  )

  expect_equal(hex_to_ip(ip_to_hex(x)), x)

  expect_snapshot(error = TRUE, {
    hex_to_ip("0x12GH")
    hex_to_ip(c("12ab", "hello"))
  })
  expect_warning(expect_equal(
    hex_to_ip(c("0xFFFFFFFF", "0x100000000"), is_ipv6 = FALSE),
    ip_address(c("255.255.255.255", NA))
  ))
  expect_warning(expect_equal(
    hex_to_ip(c("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "0x100000000000000000000000000000000"), is_ipv6 = TRUE),
    ip_address(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", NA))
  ))
})
