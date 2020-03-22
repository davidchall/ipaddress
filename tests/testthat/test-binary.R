x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("as_packed() and from_packed() work", {
  expect_error(as_packed("hello"))
  expect_error(from_packed("hello"))
  expect_error(from_packed(x))

  expect_s3_class(as_packed(x), c("blob", "vctrs_vctr"))
  expect_equal(
    as_packed(x),
    blob::blob(
      as.raw(c(0xc0, 0xa8, 0x00, 0x01)),
      as.raw(c(0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34)),
      NULL
    )
  )
  expect_equal(from_packed(as_packed(x)), x)

  expect_warning(from_packed(blob::blob(as.raw(10))), "unable to decode")
})

test_that("as_binary() and from_binary() work", {
  expect_error(as_binary("hello"))
  expect_error(from_binary(x))

  expect_type(as_binary(x), "character")
  expect_equal(as_binary(x), c(
    "11000000101010000000000000000001",
    "00100000000000010000110110111000000000000000000000000000000000000000000000000000100010100010111000000011011100000111001100110100",
    NA_character_
  ))
  expect_equal(from_binary(as_binary(x)), x)

  expect_warning(from_binary("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), "contains non-binary characters")
  expect_warning(from_binary("11000000"), "incorrect number of bits")
  expect_warning(from_binary("110000001010100000000000000000010"), "incorrect number of bits")
})
