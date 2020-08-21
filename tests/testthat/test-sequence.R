test_that("input validation works", {
  expect_error(seq(ip_network(rep("192.168.0.0/24", 2))), "`x` must be an ip_network scalar")
  expect_error(hosts(ip_network(rep("192.168.0.0/24", 2))), "`x` must be an ip_network scalar")
  expect_error(seq(ip_network()), "`x` must be an ip_network scalar")
  expect_error(hosts(ip_network()), "`x` must be an ip_network scalar")
  expect_error(hosts(ip_address("192.168.0.0")), "`x` must be an ip_network scalar")

  expect_error(seq(ip_network("0.0.0.0/1")), "Network too large")
  expect_error(seq(ip_network("::/97")), "Network too large")
  expect_error(hosts(ip_network("0.0.0.0/1")), "Network too large")
  expect_error(hosts(ip_network("::/97")), "Network too large")
})

test_that("missing values work", {
  expect_equal(seq(ip_network(NA)), ip_address(NA))
  expect_equal(hosts(ip_network(NA)), ip_address(NA))
})

test_that("seq works", {
  expect_equal(
    seq(ip_network("192.168.0.0/32")),
    ip_address("192.168.0.0")
  )
  expect_equal(
    seq(ip_network("192.168.0.0/31")),
    ip_address(c("192.168.0.0", "192.168.0.1"))
  )
  expect_equal(
    seq(ip_network("192.168.0.0/30")),
    ip_address(c("192.168.0.0", "192.168.0.1", "192.168.0.2", "192.168.0.3"))
  )

  expect_equal(
    seq(ip_network("2001:db8::/128")),
    ip_address("2001:db8::")
  )
  expect_equal(
    seq(ip_network("2001:db8::/127")),
    ip_address(c("2001:db8::", "2001:db8::1"))
  )
  expect_equal(
    seq(ip_network("2001:db8::/126")),
    ip_address(c("2001:db8::", "2001:db8::1", "2001:db8::2", "2001:db8::3"))
  )
})

test_that("hosts works", {
  expect_equal(
    hosts(ip_network("192.168.0.0/32")),
    ip_address()
  )
  expect_equal(
    hosts(ip_network("192.168.0.0/31")),
    ip_address(c("192.168.0.0", "192.168.0.1"))
  )
  expect_equal(
    hosts(ip_network("192.168.0.0/30")),
    ip_address(c("192.168.0.1", "192.168.0.2"))
  )

  expect_equal(
    hosts(ip_network("2001:db8::/128")),
    ip_address()
  )
  expect_equal(
    hosts(ip_network("2001:db8::/127")),
    ip_address(c("2001:db8::", "2001:db8::1"))
  )
  expect_equal(
    hosts(ip_network("2001:db8::/126")),
    ip_address(c("2001:db8::1", "2001:db8::2", "2001:db8::3"))
  )
})
