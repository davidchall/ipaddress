ipv4 <- c("0.0.0.0/0", "192.168.1.0/22", "129.168.1.0/24", "1.2.3.4/32")
ipv6 <- c("::/0", "2001:db00::0/22", "2001:db00::0/73", "::/128")

test_that("prefix length works", {
  expect_equal(prefix_length(ip_network(ipv4)), c(0L, 22L, 24L, 32L))
  expect_equal(prefix_length(ip_network(ipv6)), c(0L, 22L, 73L, 128L))
})

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
    ip_address(c("::", "ffff:fc00::", "ffff:ffff:ffff:ffff:ff80::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))
  )
  expect_equal(
    hostmask(ip_network(ipv6)),
    ip_address(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "0:3ff:ffff:ffff:ffff:ffff:ffff:ffff", "::7f:ffff:ffff:ffff", "::"))
  )
})
