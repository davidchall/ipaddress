test_that("input validation works", {
  expect_error(is_within(ip_network(), ip_network()), "`address` must be an ip_address vector")
  expect_error(is_within(ip_address(), ip_address()), "`network` must be an ip_network vector")
  expect_error(is_within(ip_address(rep("1.2.3.4", 3)), ip_network(rep("1.2.3.4/32", 2))), class = "vctrs_error_incompatible_size")

  expect_error(is_within_any(ip_network(), ip_network()), "`address` must be an ip_address vector")
  expect_error(is_within_any(ip_address(), ip_address()), "`network` must be an ip_network vector")

  expect_error(overlaps(ip_address(), ip_network()), "`network` must be an ip_network vector")
  expect_error(overlaps(ip_network(), ip_address()), "`other` must be an ip_network vector")
  expect_error(overlaps(ip_network(rep("1.2.3.4/32", 3)), ip_network(rep("1.2.3.4/32", 2))), class = "vctrs_error_incompatible_size")

  expect_error(is_subnet(ip_address(), ip_network()), "`network` must be an ip_network vector")
  expect_error(is_subnet(ip_network(), ip_address()), "`other` must be an ip_network vector")
  expect_error(is_subnet(ip_network(rep("1.2.3.4/32", 3)), ip_network(rep("1.2.3.4/32", 2))), class = "vctrs_error_incompatible_size")

  expect_error(is_supernet(ip_address(), ip_network()), "`network` must be an ip_network vector")
  expect_error(is_supernet(ip_network(), ip_address()), "`other` must be an ip_network vector")
  expect_error(is_supernet(ip_network(rep("1.2.3.4/32", 3)), ip_network(rep("1.2.3.4/32", 2))), class = "vctrs_error_incompatible_size")
})

test_that("is_within works", {
  addr <- ip_address(c(
    "192.167.255.255",
    "192.168.0.0",
    "192.168.3.255",
    "192.168.4.0"
  ))
  netw <- ip_network("192.168.0.0/22")
  expect_equal(is_within(addr, rep(netw, 4)), c(FALSE, TRUE, TRUE, FALSE))
  expect_equal(is_within(addr, netw), c(FALSE, TRUE, TRUE, FALSE))

  addr <- ip_address(c(
    "2001:db7:fff:ffff:ffff:ffff:ffff:ffff",
    "2001:db8::",
    "2001:db8:fff:ffff:ffff:ffff:ffff:ffff",
    "2001:db9::"
  ))
  netw <- ip_network("2001:db8::/36")
  expect_equal(is_within(addr, rep(netw, 4)), c(FALSE, TRUE, TRUE, FALSE))
  expect_equal(is_within(addr, netw), c(FALSE, TRUE, TRUE, FALSE))
})

test_that("is_within_any works", {
  expect_equal(
    is_within_any(
      ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", "1.2.3.4")),
      ip_network(c("192.168.0.0/24", "2001:db8::/36"))
    ),
    c(TRUE, TRUE, FALSE)
  )
  expect_equal(
    is_within_any(
      ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", "1.2.3.4")),
      ip_network(c("2001:db8::/36", "192.168.0.0/24"))
    ),
    c(TRUE, TRUE, FALSE)
  )
  expect_equal(
    is_within_any(ip_address("::1"), ip_network("2001:db8::/80")),
    FALSE
  )
})

test_that("network-in-network works", {
  net1 <- ip_network(c(
    "192.167.255.255/32",
    "192.168.0.0/32",
    "192.168.3.255/32",
    "192.168.4.0/32",
    "192.168.0.0/20"
  ))
  net2 <- ip_network("192.168.0.0/22")

  expect_equal(overlaps(net1, net2), c(FALSE, TRUE, TRUE, FALSE, TRUE))
  expect_equal(overlaps(net2, net1), c(FALSE, TRUE, TRUE, FALSE, TRUE))
  expect_equal(is_subnet(net1, net2), c(FALSE, TRUE, TRUE, FALSE, FALSE))
  expect_equal(is_subnet(net2, net1), c(FALSE, FALSE, FALSE, FALSE, TRUE))
  expect_equal(is_supernet(net1, net2), c(FALSE, FALSE, FALSE, FALSE, TRUE))
  expect_equal(is_supernet(net2, net1), c(FALSE, TRUE, TRUE, FALSE, FALSE))

  net1 <- ip_network(c(
    "2001:db7:fff:ffff:ffff:ffff:ffff:ffff/128",
    "2001:db8::/128",
    "2001:db8:fff:ffff:ffff:ffff:ffff:ffff/128",
    "2001:db9::/128",
    "2001:db8::/30"
  ))
  net2 <- ip_network("2001:db8::/36")

  expect_equal(overlaps(net1, net2), c(FALSE, TRUE, TRUE, FALSE, TRUE))
  expect_equal(overlaps(net2, net1), c(FALSE, TRUE, TRUE, FALSE, TRUE))
  expect_equal(is_subnet(net1, net2), c(FALSE, TRUE, TRUE, FALSE, FALSE))
  expect_equal(is_subnet(net2, net1), c(FALSE, FALSE, FALSE, FALSE, TRUE))
  expect_equal(is_supernet(net1, net2), c(FALSE, FALSE, FALSE, FALSE, TRUE))
  expect_equal(is_supernet(net2, net1), c(FALSE, TRUE, TRUE, FALSE, FALSE))
})

test_that("multi-space comparisons fail", {
  expect_false(is_within(ip_address("192.168.0.1"), ip_network("2001:db8::/36")))
  expect_false(is_within(ip_address("2001:db8::8a2e:370:7334"), ip_network("192.168.0.0/22")))

  expect_true(is_within_any(ip_address("192.168.0.1"), ip_network(c("2001:db8::/36", "192.168.0.0/22"))))
  expect_false(is_within_any(ip_address("192.168.0.1"), ip_network(c("2001:db8::/36", "192.168.0.0/32"))))
  expect_false(is_within_any(ip_address("192.168.0.1"), ip_network(c("2001:db8::/36", "2001:db8::/64"))))

  expect_false(overlaps(ip_network("2001:db8::/36"), ip_network("192.168.0.0/22")))
  expect_false(overlaps(ip_network("192.168.0.0/22"), ip_network("2001:db8::/36")))

  expect_false(is_subnet(ip_network("2001:db8::/36"), ip_network("192.168.0.0/22")))
  expect_false(is_subnet(ip_network("192.168.0.0/22"), ip_network("2001:db8::/36")))

  expect_false(is_supernet(ip_network("2001:db8::/36"), ip_network("192.168.0.0/22")))
  expect_false(is_supernet(ip_network("192.168.0.0/22"), ip_network("2001:db8::/36")))
})

test_that("missing values work", {
  expect_equal(is_within(ip_address(NA), ip_network("192.168.0.0/24")), NA)
  expect_equal(is_within(ip_address("192.168.0.1"), ip_network(NA)), NA)

  expect_equal(is_within_any(ip_address(NA), ip_network(c("192.168.0.0/24", "1.2.3.4/31"))), NA)
  expect_true(is_within_any(ip_address("192.168.0.1"), ip_network(c("192.168.0.0/24", NA))))
  expect_false(is_within_any(ip_address("192.168.0.1"), ip_network(c("192.168.0.0/32", NA))))

  expect_equal(overlaps(ip_network(NA), ip_network("192.168.0.0/24")), NA)
  expect_equal(overlaps(ip_network("192.168.0.0/24"), ip_network(NA)), NA)

  expect_equal(is_subnet(ip_network(NA), ip_network("192.168.0.0/24")), NA)
  expect_equal(is_subnet(ip_network("192.168.0.0/24"), ip_network(NA)), NA)

  expect_equal(is_supernet(ip_network(NA), ip_network("192.168.0.0/24")), NA)
  expect_equal(is_supernet(ip_network("192.168.0.0/24"), ip_network(NA)), NA)
})
