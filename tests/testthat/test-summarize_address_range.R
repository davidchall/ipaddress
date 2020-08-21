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

test_that("missing values work", {
  expect_equal(summarize_address_range(ip_address("1.2.3.4"), ip_address(NA)), list(ip_network(NA)))
  expect_equal(summarize_address_range(ip_address(NA), ip_address("1.2.3.4")), list(ip_network(NA)))
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
})
