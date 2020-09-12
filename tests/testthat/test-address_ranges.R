test_that("blocks calculated correctly", {
  # single-host networks
  expect_equal(summarize_address_range(ip_address("1.2.3.4"), ip_address("1.2.3.4")), list(ip_network("1.2.3.4/32")))
  expect_equal(summarize_address_range(ip_address("2001:db8::8a2e:370:7334"), ip_address("2001:db8::8a2e:370:7334")), list(ip_network("2001:db8::8a2e:370:7334/128")))

  # difficult examples (validated against Python ipaddress module)
  expect_equal(
    summarize_address_range(ip_address("192.0.1.129"), ip_address("192.0.2.139")),
    list(ip_network(c(
      "192.0.1.129/32", "192.0.1.130/31", "192.0.1.132/30", "192.0.1.136/29", "192.0.1.144/28", "192.0.1.160/27", "192.0.1.192/26", "192.0.2.0/25", "192.0.2.128/29", "192.0.2.136/30"
    )))
  )
  expect_equal(
    summarize_address_range(ip_address("2001:db8::181"), ip_address("2001:db8::28b")),
    list(ip_network(c(
      "2001:db8::181/128", "2001:db8::182/127", "2001:db8::184/126", "2001:db8::188/125", "2001:db8::190/124", "2001:db8::1a0/123", "2001:db8::1c0/122", "2001:db8::200/121", "2001:db8::280/125", "2001:db8::288/126"
    )))
  )

  # edge cases
  expect_equal(summarize_address_range(ip_address("0.0.0.0"), ip_address("0.0.0.0")), list(ip_network("0.0.0.0/32")))
  expect_equal(summarize_address_range(ip_address("255.255.255.255"), ip_address("255.255.255.255")), list(ip_network("255.255.255.255/32")))
  expect_equal(summarize_address_range(ip_address("0.0.0.0"), ip_address("255.255.255.255")), list(ip_network("0.0.0.0/0")))
  expect_equal(summarize_address_range(ip_address("::"), ip_address("::")), list(ip_network("::/128")))
  expect_equal(summarize_address_range(ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"), ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")), list(ip_network("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/128")))
  expect_equal(summarize_address_range(ip_address("::"), ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")), list(ip_network("::/0")))
})

test_that("vector recycling works", {
  expect_equal(
    summarize_address_range(ip_address("192.168.0.0"), ip_address(c("192.168.0.15", "192.168.7.255"))),
    list(ip_network("192.168.0.0/28"), ip_network("192.168.0.0/21"))
  )
  expect_equal(
    summarize_address_range(ip_address(c("192.168.0.15", "192.168.7.255")), ip_address("192.168.0.0")),
    list(ip_network("192.168.0.0/28"), ip_network("192.168.0.0/21"))
  )
})

test_that("incompatible address spaces identified", {
  expect_equal(summarize_address_range(ip_address("1.2.3.4"), ip_address("abcd::1234")), list(ip_network(NA)))
})

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
  expect_equal(
    exclude_networks(ip_network("192.0.2.0/32"), ip_network("192.0.2.0/32")),
    ip_network()
  )
  expect_equal(
    exclude_networks(ip_network("192.0.2.0/28"), ip_network("192.0.2.0/28")),
    ip_network()
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
  expect_equal(summarize_address_range(ip_address("1.2.3.4"), ip_address(NA)), list(ip_network(NA)))
  expect_equal(summarize_address_range(ip_address(NA), ip_address("1.2.3.4")), list(ip_network(NA)))
  expect_equal(collapse_networks(ip_network(NA)), ip_network())
  expect_equal(exclude_networks(ip_network(NA), ip_network("0.0.0.0/8")), ip_network())
  expect_equal(exclude_networks(ip_network("0.0.0.0/8"), ip_network(NA)), ip_network("0.0.0.0/8"))
})

test_that("input validation", {
  expect_error(
    summarize_address_range(ip_address(), ip_network()),
    "`address2` must be an ip_address vector"
  )
  expect_error(
    summarize_address_range(ip_network(), ip_address()),
    "`address1` must be an ip_address vector"
  )
  expect_error(
    summarize_address_range(ip_address(rep("1.2.3.4", 3)), ip_address(rep("1.2.3.4", 2))),
    class = "vctrs_error_incompatible_size"
  )
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
