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

test_that("excluded networks are removed", {
  expect_equal(
    exclude_networks(ip_network("192.0.2.0/28"), ip_network("192.0.2.1/32")),
    ip_network(c("192.0.2.0/32", "192.0.2.2/31", "192.0.2.4/30", "192.0.2.8/29"))
  )
  expect_equal(
    exclude_networks(ip_network("192.0.2.0/28"), ip_network("192.0.2.15/32")),
    ip_network(c("192.0.2.0/29", "192.0.2.8/30", "192.0.2.12/31", "192.0.2.14/32"))
  )
  expect_equal(
    exclude_networks(ip_network("2001:db8::/32"), ip_network("2001:db8:1000::/36")),
    ip_network(c("2001:db8::/36", "2001:db8:2000::/35", "2001:db8:4000::/34", "2001:db8:8000::/33"))
  )
  expect_equal(
    exclude_networks(ip_network("2001:db8::/32"), ip_network("2001:db8:f000::/36")),
    ip_network(c("2001:db8::/33", "2001:db8:8000::/34", "2001:db8:c000::/35", "2001:db8:e000::/36"))
  )
})

test_that("single network unaffected", {
  expect_equal(collapse_networks(ip_network("0.0.0.0/8")), ip_network("0.0.0.0/8"))
  expect_equal(collapse_networks(ip_network("::/8")), ip_network("::/8"))
  expect_equal(collapse_networks(ip_network(c("0.0.0.0/8", "::/8"))), ip_network(c("0.0.0.0/8", "::/8")))
})

test_that("empty values work", {
  expect_equal(collapse_networks(ip_network()), ip_network())
  expect_equal(exclude_networks(ip_network(), ip_network("0.0.0.0/8")), ip_network())
  expect_equal(exclude_networks(ip_network("0.0.0.0/8"), ip_network()), ip_network("0.0.0.0/8"))
})

test_that("missing values work", {
  expect_equal(collapse_networks(ip_network(NA)), ip_network())
  expect_equal(exclude_networks(ip_network(NA), ip_network("0.0.0.0/8")), ip_network())
  expect_equal(exclude_networks(ip_network("0.0.0.0/8"), ip_network(NA)), ip_network("0.0.0.0/8"))
})

test_that("input validation", {
  expect_error(
    collapse_networks(ip_address("192.168.0.1")),
    "`network` must be an ip_network vector"
  )
  expect_error(
    exclude_networks(ip_address("192.168.0.1"), ip_network("192.168.0.0/24")),
    "`include` must be an ip_network vector"
  )
  expect_error(
    exclude_networks(ip_network("192.168.0.0/24"), ip_address("192.168.0.1")),
    "`exclude` must be an ip_network vector"
  )
})
