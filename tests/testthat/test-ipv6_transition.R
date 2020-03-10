x <- ip_address(c("192.168.0.1", "::ffff:192.0.2.128", "2001:db8::"))

test_that("is_ipv4_mapped works", {
  # IPv4: none
  expect_false(is_ipv4_mapped(ip_address("0.0.0.0")))
  expect_false(is_ipv4_mapped(ip_network("0.0.0.0/32")))

  # IPv6: ::ffff:0.0.0.0/96
  expect_equal(
    is_ipv4_mapped(ip_address(c("::fffe:ffff:ffff", "::ffff:0.0.0.0", "::ffff:255.255.255.255"))),
    c(FALSE, TRUE, TRUE)
  )
  expect_equal(
    is_ipv4_mapped(ip_network(c("::ffff:0.0.0.0/96", "::ffff:0.0.0.0/97", "::fffe:0.0.0.0/95"))),
    c(TRUE, TRUE, FALSE)
  )

  expect_equal(is_ipv4_mapped(ip_address()), logical())
  expect_equal(is_ipv4_mapped(ip_network()), logical())

  expect_equal(is_ipv4_mapped(ip_address(NA)), NA)
  expect_equal(is_ipv4_mapped(ip_network(NA)), NA)

  expect_error(is_ipv4_mapped("hello"))
})

test_that("extract_ipv4_mapped() works", {
  expect_equal(extract_ipv4_mapped(ip_address()), ip_address())
  expect_equal(
    extract_ipv4_mapped(x),
    ip_address(c("192.168.0.1", "192.0.2.128", NA))
  )
  expect_equal(
    extract_ipv4_mapped(x, keep_ipv6 = TRUE),
    ip_address(c("192.168.0.1", "192.0.2.128", "2001:db8::"))
  )
})

test_that("input validation works", {
  expect_error(extract_ipv4_mapped(ip_network()))
  expect_error(extract_ipv4_mapped(NA))

  expect_error(extract_ipv4_mapped(ip_address(), c(TRUE, FALSE)))
  expect_error(extract_ipv4_mapped(ip_address(), NA))
})
