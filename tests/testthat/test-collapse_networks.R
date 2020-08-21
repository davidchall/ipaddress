test_that("contiguous collapsed", {
  expect_equal(
    collapse_networks(ip_network(c("192.168.0.0/24", "192.168.1.0/24"))),
    ip_network("192.168.0.0/23")
  )
  expect_equal(
    collapse_networks(ip_network(c("2001:db8::/117", "2001:db8::800/117"))),
    ip_network("2001:db8::/116")
  )
})

test_that("overlaps collapsed", {
  expect_equal(
    collapse_networks(ip_network(c("192.168.0.0/23", "192.168.0.0/24"))),
    ip_network("192.168.0.0/23")
  )
  expect_equal(
    collapse_networks(ip_network(c("2001:db8::/116", "2001:db8::800/117"))),
    ip_network("2001:db8::/116")
  )
})

test_that("duplicates removed", {
  expect_equal(
    collapse_networks(ip_network(c("192.168.0.0/24", "192.168.0.0/24"))),
    ip_network("192.168.0.0/24")
  )
  expect_equal(
    collapse_networks(ip_network(c("2001:db8::/117", "2001:db8::/117"))),
    ip_network("2001:db8::/117")
  )
})

test_that("non-contiguous not collapsed", {
  expect_equal(
    collapse_networks(ip_network(c("192.168.0.0/24", "192.168.2.0/24"))),
    ip_network(c("192.168.0.0/24", "192.168.2.0/24"))
  )
  expect_equal(
    collapse_networks(ip_network(c("2001:db8::/117", "2001:db8::1000/117"))),
    ip_network(c("2001:db8::/117", "2001:db8::1000/117"))
  )
})

test_that("single network unaffected", {
  expect_equal(collapse_networks(ip_network("0.0.0.0/8")), ip_network("0.0.0.0/8"))
  expect_equal(collapse_networks(ip_network("::/8")), ip_network("::/8"))
  expect_equal(collapse_networks(ip_network(c("0.0.0.0/8", "::/8"))), ip_network(c("0.0.0.0/8", "::/8")))
})

test_that("missing values work", {
  expect_equal(collapse_networks(ip_network(NA)), ip_network())
})

test_that("input validation", {
  expect_error(
    collapse_networks(ip_address("192.168.0.1")),
    "`network` must be an ip_network vector"
  )
})
