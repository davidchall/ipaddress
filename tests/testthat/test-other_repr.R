x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("integer encoding/decoding works", {
  expect_error(ip_to_integer("hello"))
  expect_error(integer_to_ip(1.5))
  expect_error(integer_to_ip(x))

  expect_type(ip_to_integer(x), "character")
  expect_s3_class(integer_to_ip("1"), "ip_address")
  expect_equal(
    ip_to_integer(x),
    c("3232235521", "42540766411282592856904136881884656436", NA)
  )
  expect_equal(integer_to_ip(ip_to_integer(x)), x)

  expect_warning(integer_to_ip("hello"))
  expect_warning(integer_to_ip("-1"))
})

test_that("bytes encoding/decoding works", {
  expect_error(ip_to_bytes("hello"))
  expect_error(bytes_to_ip("hello"))
  expect_error(bytes_to_ip(x))

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

test_that("bits encoding/decoding works", {
  expect_error(ip_to_bits("hello"))
  expect_error(bits_to_ip(x))

  expect_type(ip_to_bits(x), "character")
  expect_equal(ip_to_bits(x), c(
    "11000000101010000000000000000001",
    "00100000000000010000110110111000000000000000000000000000000000000000000000000000100010100010111000000011011100000111001100110100",
    NA_character_
  ))
  expect_equal(bits_to_ip(ip_to_bits(x)), x)

  expect_warning(bits_to_ip("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), "contains non-binary characters")
  expect_warning(bits_to_ip("11000000"), "incorrect number of bits")
  expect_warning(bits_to_ip("110000001010100000000000000000010"), "incorrect number of bits")
})
