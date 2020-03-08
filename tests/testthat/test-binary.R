x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("packed() and unpack() work", {
  expect_s3_class(packed(x), c("blob", "vctrs_vctr"))
  expect_equal(unpack(packed(x)), x)

  expect_warning(unpack(blob::blob(as.raw(10))), "unable to decode")
})

test_that("as_binary() and from_binary() work", {
  expect_type(as_binary(x), "character")
  expect_equal(as_binary(x), c(
    "11000000101010000000000000000001",
    "00100000000000010000110110111000000000000000000000000000000000000000000000000000100010100010111000000011011100000111001100110100",
    NA_character_
  ))
  expect_equal(from_binary(as_binary(x)), x)

  expect_error(from_binary("abc"))
  expect_warning(from_binary("11000000"))
  expect_error(from_binary("110000001010100000000000000000010"))
})
