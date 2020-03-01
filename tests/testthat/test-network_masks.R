ipv4 <- c("0.0.0.0/0", "192.168.128.0/22", "129.168.1.0/24", "1.2.3.4/32")
ipv6 <- c("::/0", "2001:db00::/35", "2001:db00::/73", "::/128")

test_that("masking works", {
  expect_equal(
    netmask(ip_network(ipv4)),
    ip_address(c("0.0.0.0", "255.255.252.0", "255.255.255.0", "255.255.255.255"))
  )
  expect_equal(
    hostmask(ip_network(ipv4)),
    ip_address(c("255.255.255.255", "0.0.3.255", "0.0.0.255", "0.0.0.0"))
  )
  expect_equal(
    netmask(ip_network(ipv6)),
    ip_address(c("::", "ffff:ffff:e000::", "ffff:ffff:ffff:ffff:ff80::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))
  )
  expect_equal(
    hostmask(ip_network(ipv6)),
    ip_address(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "::1fff:ffff:ffff:ffff:ffff:ffff", "::7f:ffff:ffff:ffff", "::"))
  )
})

test_that("only accepts networks", {
  expect_error(netmask(ip_address("1.2.3.4")), "not an ip_network")
  expect_error(hostmask(ip_address("1.2.3.4")), "not an ip_network")
})

test_that("missing values work", {
  expect_equal(netmask(ip_network(NA)), ip_address(NA))
  expect_equal(hostmask(ip_network(NA)), ip_address(NA))
})
