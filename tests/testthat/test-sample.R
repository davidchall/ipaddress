ipv4 <- ip_network("192.168.0.0/22")
ipv6 <- ip_network("2001:db8::/118")

test_that("input validation works", {
  expect_error(sample_ip(ip_network(rep(ipv4, 2)), 1))
  expect_error(sample_ip(ip_network(), 1))
  expect_error(sample_ip(ip_address("192.168.0.0"), 1))
  expect_error(sample_ip(ip_network("0.0.0.0/32"), 0))
  expect_error(sample_ip(ip_network("0.0.0.0/32"), NA))
  expect_error(sample_ip(ip_network("0.0.0.0/32"), 1, NA))
  expect_error(sample_ip(ip_network("0.0.0.0/32"), 1, 1))
  expect_error(sample_ip("IPv8", 1))
  expect_error(sample_ip(ip_network(NA), 1))

  expect_error(sample_ip(ipv4, num_addresses(ipv4) + 1, replace = FALSE))
})

test_that("generates within network", {
  expect_true(all(is_within_any(sample_ip(ipv4, 1000, replace = FALSE), ipv4)))
  expect_true(all(is_within_any(sample_ip(ipv4, 1000, replace = TRUE), ipv4)))

  expect_true(all(is_within_any(sample_ip(ipv6, 1000, replace = FALSE), ipv6)))
  expect_true(all(is_within_any(sample_ip(ipv6, 1000, replace = TRUE), ipv6)))
})

test_that("avoids duplicates", {
  expect_false(any(duplicated(sample_ip(ipv4, 1000, replace = FALSE))))
  expect_false(any(duplicated(sample_ip(ipv6, 1000, replace = FALSE))))
})
