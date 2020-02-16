test_that("masking works", {
  expect_equal(
    netmask(ip_network(c("192.168.1.0/22", "2001:db00::0/22"))),
    ip_address(c("255.255.252.0", "ffff:fc00::"))
  )
  expect_equal(
    hostmask(ip_network(c("192.168.1.0/22", "2001:db00::0/22"))),
    ip_address(c("0.0.3.255", "0:3ff:ffff:ffff:ffff:ffff:ffff:ffff"))
  )
})
