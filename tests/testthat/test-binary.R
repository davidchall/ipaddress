x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("encoding and decoding works", {
  expect_equal(unpack(packed(x)), x)
})

test_that("decoding unrecognized input fails", {
  expect_warning(unpack(blob::blob(as.raw(10))), "unable to decode")
})
