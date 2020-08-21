test_that("common network found", {
  # addresses are network boundaries
  expect_equal(common_network(ip_address("192.168.0.0"), ip_address("192.168.7.255")), ip_network("192.168.0.0/21"))
  expect_equal(common_network(ip_address("192.168.7.255"), ip_address("192.168.0.0")), ip_network("192.168.0.0/21"))
  expect_equal(common_network(ip_address("2001:db8::"), ip_address("2001:db8::7ff")), ip_network("2001:db8::/117"))
  expect_equal(common_network(ip_address("2001:db8::7ff"), ip_address("2001:db8::")), ip_network("2001:db8::/117"))

  # addresses are not network boundaries
  expect_equal(common_network(ip_address("192.168.0.0") + 1L, ip_address("192.168.7.255") - 1L), ip_network("192.168.0.0/21"))
  expect_equal(common_network(ip_address("192.168.7.255") - 1L, ip_address("192.168.0.0") + 1L), ip_network("192.168.0.0/21"))
  expect_equal(common_network(ip_address("2001:db8::") + 1L, ip_address("2001:db8::7ff") - 1L), ip_network("2001:db8::/117"))
  expect_equal(common_network(ip_address("2001:db8::7ff") - 1L, ip_address("2001:db8::") + 1L), ip_network("2001:db8::/117"))

  # single-host networks
  expect_equal(common_network(ip_address("1.2.3.4"), ip_address("1.2.3.4")), ip_network("1.2.3.4/32"))
  expect_equal(common_network(ip_address("2001:db8::8a2e:370:7334"), ip_address("2001:db8::8a2e:370:7334")), ip_network("2001:db8::8a2e:370:7334/128"))

  # edge cases
  expect_equal(common_network(ip_address("0.0.0.0"), ip_address("0.0.0.0")), ip_network("0.0.0.0/32"))
  expect_equal(common_network(ip_address("255.255.255.255"), ip_address("255.255.255.255")), ip_network("255.255.255.255/32"))
  expect_equal(common_network(ip_address("0.0.0.0"), ip_address("255.255.255.255")), ip_network("0.0.0.0/0"))
  expect_equal(common_network(ip_address("::"), ip_address("::")), ip_network("::/128"))
  expect_equal(common_network(ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"), ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")), ip_network("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/128"))
  expect_equal(common_network(ip_address("::"), ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")), ip_network("::/0"))
})

test_that("vector recycling works", {
  expect_equal(
    common_network(ip_address("192.168.0.0"), ip_address(c("192.168.0.15", "192.168.7.255"))),
    ip_network(c("192.168.0.0/28", "192.168.0.0/21"))
  )
  expect_equal(
    common_network(ip_address(c("192.168.0.15", "192.168.7.255")), ip_address("192.168.0.0")),
    ip_network(c("192.168.0.0/28", "192.168.0.0/21"))
  )
})

test_that("incompatible address spaces identified", {
  expect_equal(common_network(ip_address("1.2.3.4"), ip_address("abcd::1234")), ip_network(NA))
})

test_that("missing values work", {
  expect_equal(common_network(ip_address("1.2.3.4"), ip_address(NA)), ip_network(NA))
  expect_equal(common_network(ip_address(NA), ip_address("1.2.3.4")), ip_network(NA))
})

test_that("input validation", {
  expect_error(
    common_network(ip_address(), ip_network()),
    "`address2` must be an ip_address vector"
  )
  expect_error(
    common_network(ip_network(), ip_address()),
    "`address1` must be an ip_address vector"
  )
  expect_error(
    common_network(ip_address(rep("1.2.3.4", 3)), ip_address(rep("1.2.3.4", 2))),
    class = "vctrs_error_incompatible_size"
  )
})
