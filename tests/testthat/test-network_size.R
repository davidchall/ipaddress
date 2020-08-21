x <- ip_network(c("0.0.0.0/32", "192.168.100.0/22", "::/128", "2001:db8::/36"))

test_that("num_addresses works", {
  expect_equal(num_addresses(x), c(1, 1024, 1, 2^92))

  expect_error(num_addresses(ip_address("192.168.0.1")), "`x` must be an ip_network vector")
  expect_equal(num_addresses(ip_network(NA)), NA_real_)
})

test_that("network_address works", {
  expect_equal(network_address(x), ip_address(c("0.0.0.0", "192.168.100.0", "::", "2001:db8::")))
  expect_equal(x, ip_network(network_address(x), prefix_length(x)))

  expect_error(network_address(ip_address("192.168.0.1")), "`x` must be an ip_network vector")
  expect_equal(network_address(ip_network(NA)), ip_address(NA))
})

test_that("broadcast_address works", {
  expect_equal(broadcast_address(x), ip_address(c("0.0.0.0", "192.168.103.255", "::", "2001:db8:fff:ffff:ffff:ffff:ffff:ffff")))

  expect_error(broadcast_address(ip_address("192.168.0.1")), "`x` must be an ip_network vector")
  expect_equal(broadcast_address(ip_network(NA)), ip_address(NA))
})
