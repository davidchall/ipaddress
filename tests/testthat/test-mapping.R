x <- ip_address(c("192.168.0.1", "::ffff:192.0.2.128", "2001:db8::"))

test_that("ipv4_mapped() works", {
  expect_equal(ipv4_mapped(ip_address()), ip_address())
  expect_equal(
    ipv4_mapped(x),
    ip_address(c("192.168.0.1", "192.0.2.128", NA))
  )
  expect_equal(
    ipv4_mapped(x, keep_ipv6 = TRUE),
    ip_address(c("192.168.0.1", "192.0.2.128", "2001:db8::"))
  )
})

test_that("ipv6_mapped() works", {
  expect_equal(ipv6_mapped(ip_address()), ip_address())
  expect_equal(
    ipv6_mapped(x),
    ip_address(c("::ffff:192.168.0.1", "::ffff:192.0.2.128", "2001:db8::"))
  )
  expect_equal(
    ipv6_mapped(ipv4_mapped(x)),
    ip_address(c("::ffff:192.168.0.1", "::ffff:192.0.2.128", NA))
  )
})

test_that("input validation works", {
  expect_error(ipv4_mapped(ip_network()))
  expect_error(ipv6_mapped(ip_network()))
  expect_error(ipv4_mapped(NA))
  expect_error(ipv6_mapped(NA))

  expect_error(ipv4_mapped(ip_address(), c(TRUE, FALSE)))
  expect_error(ipv4_mapped(ip_address(), NA))
})
