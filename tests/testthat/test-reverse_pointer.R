test_that("reverse pointer works", {
  expect_equal(reverse_pointer(ip_address("127.0.0.1")), "1.0.0.127.in-addr.arpa")
  expect_equal(
    reverse_pointer(ip_address("2001:db8::1")),
    "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.8.b.d.0.1.0.0.2.ip.arpa"
  )

  expect_error(reverse_pointer(ip_network()), "`x` must be an ip_address vector")
  expect_equal(reverse_pointer(ip_address(NA)), NA_character_)
})
