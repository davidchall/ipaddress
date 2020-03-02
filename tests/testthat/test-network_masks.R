ipv4 <- c("0.0.0.0/0", "192.168.128.0/22", "129.168.1.0/24", "1.2.3.4/32")
ipv6 <- c("::/0", "2001:db00::/35", "2001:db00::/73", "::/128")

test_that("empty arguments work", {
  expect_equal(netmask(), ip_address())
  expect_equal(hostmask(), ip_address())
})

test_that("masking works", {
  expect_equal(
    netmask(ip_network(ipv4)),
    ip_address(c("0.0.0.0", "255.255.252.0", "255.255.255.0", "255.255.255.255"))
  )
  expect_equal(
    netmask(c(0L, 22L, 24L, 32L), c(FALSE, FALSE, FALSE, FALSE)),
    netmask(ip_network(ipv4))
  )
  expect_equal(
    hostmask(ip_network(ipv4)),
    ip_address(c("255.255.255.255", "0.0.3.255", "0.0.0.255", "0.0.0.0"))
  )
  expect_equal(
    hostmask(c(0L, 22L, 24L, 32L), c(FALSE, FALSE, FALSE, FALSE)),
    hostmask(ip_network(ipv4))
  )
  expect_equal(
    netmask(ip_network(ipv6)),
    ip_address(c("::", "ffff:ffff:e000::", "ffff:ffff:ffff:ffff:ff80::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))
  )
  expect_equal(
    netmask(c(0L, 35L, 73L, 128L), c(TRUE, TRUE, TRUE, TRUE)),
    netmask(ip_network(ipv6))
  )
  expect_equal(
    hostmask(ip_network(ipv6)),
    ip_address(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "::1fff:ffff:ffff:ffff:ffff:ffff", "::7f:ffff:ffff:ffff", "::"))
  )
  expect_equal(
    hostmask(c(0L, 35L, 73L, 128L), c(TRUE, TRUE, TRUE, TRUE)),
    hostmask(ip_network(ipv6))
  )
})

test_that("input validation works", {
  expect_error(netmask(ip_address("1.2.3.4")))
  expect_error(hostmask(ip_address("1.2.3.4")))

  expect_error(netmask(1, FALSE))
  expect_error(hostmask(1, FALSE))
  expect_error(netmask(1L, "yes"))
  expect_error(hostmask(1L, "yes"))
  expect_error(netmask(c(1L), c(FALSE, TRUE)))
  expect_error(hostmask(c(1L), c(FALSE, TRUE)))

  expect_error(netmask(-1L, FALSE))
  expect_error(hostmask(-1L, FALSE))
  expect_error(netmask(33L, FALSE))
  expect_error(hostmask(33L, FALSE))
  expect_error(netmask(129L, TRUE))
  expect_error(hostmask(129L, TRUE))
})

test_that("missing values work", {
  expect_equal(netmask(ip_network(NA)), ip_address(NA))
  expect_equal(hostmask(ip_network(NA)), ip_address(NA))
  expect_equal(netmask(c(1L, NA), c(NA, TRUE)), ip_address(c(NA, NA)))
  expect_equal(hostmask(c(1L, NA), c(NA, TRUE)), ip_address(c(NA, NA)))
})
