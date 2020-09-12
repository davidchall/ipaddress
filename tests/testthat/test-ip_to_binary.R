x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("binary encoding/decoding works", {
  expect_error(ip_to_binary("hello"), "`x` must be an ip_address vector")
  expect_error(binary_to_ip(x), "`x` must be a character vector")

  expect_type(ip_to_binary(x), "character")
  expect_equal(ip_to_binary(x), c(
    "11000000101010000000000000000001",
    "00100000000000010000110110111000000000000000000000000000000000000000000000000000100010100010111000000011011100000111001100110100",
    NA_character_
  ))
  expect_equal(binary_to_ip(ip_to_binary(x)), x)

  # zero padding
  expect_equal(ip_to_binary(ip_address("0.0.0.0")), strrep("0", 32))
  expect_equal(ip_to_binary(ip_address("::")), strrep("0", 128))

  expect_warning(binary_to_ip(strrep("a", 32)), "contains non-binary characters")
  expect_warning(binary_to_ip("11000000"), "incorrect number of bits")
  expect_warning(binary_to_ip("110000001010100000000000000000010"), "incorrect number of bits")
})
