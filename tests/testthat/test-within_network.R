test_that("input validation works", {
  expect_error(is_within(ip_network(), ip_network()), "not an ip_address vector")
  expect_error(is_within(ip_address(), ip_address()), "not an ip_network vector")
  expect_error(is_within(ip_address("1.2.3.4"), ip_network()), "not equal to length")

  expect_error(is_within_any(ip_network(), ip_network()), "not an ip_address vector")
  expect_error(is_within_any(ip_address(), ip_address()), "not an ip_network vector")

  expect_error(is_subnet(ip_address(), ip_network()), "not an ip_network vector")
  expect_error(is_subnet(ip_network(), ip_address()), "not an ip_network vector")
  expect_error(is_subnet(ip_network("1.2.3.4/32"), ip_network()), "not equal to length")

  expect_error(is_supernet(ip_address(), ip_network()), "not an ip_network vector")
  expect_error(is_supernet(ip_network(), ip_address()), "not an ip_network vector")
  expect_error(is_supernet(ip_network("1.2.3.4/32"), ip_network()), "not equal to length")
})

test_that("is_within works", {
  expect_equal(
    is_within(
      ip_address(rep("192.168.0.1", 4)),
      ip_network(c("192.168.0.0/24", "192.168.0.0/22", "192.168.0.0/32", "192.169.0.0/24"))
    ),
    c(TRUE, TRUE, FALSE, FALSE)
  )
  expect_equal(
    is_within(
      ip_address(rep("2001:db8::8a2e:370:7334", 4)),
      ip_network(c("2001:db8::/36", "2001:db8::/64", "2001:db8::8a2e:370:7335/128", "2001:db9::/36"))
    ),
    c(TRUE, TRUE, FALSE, FALSE)
  )
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
})

test_that("is_subnet and is_supernet work", {
  net1 <- ip_network("192.168.1.0/24")
  net2 <- ip_network("192.168.1.128/30")

  expect_equal(is_subnet(net1, net2), FALSE)
  expect_equal(is_subnet(net2, net1), TRUE)
  expect_equal(is_supernet(net1, net2), TRUE)
  expect_equal(is_supernet(net2, net1), FALSE)

  net1 <- ip_network("2001:db8::/36")
  net2 <- ip_network("2001:db8::8a2e:370:7334/128")

  expect_equal(is_subnet(net1, net2), FALSE)
  expect_equal(is_subnet(net2, net1), TRUE)
  expect_equal(is_supernet(net1, net2), TRUE)
  expect_equal(is_supernet(net2, net1), FALSE)
})

test_that("multi-space comparisons fail", {
  expect_false(is_within(ip_address("192.168.0.1"), ip_network("2001:db8::/36")))
  expect_false(is_within(ip_address("2001:db8::8a2e:370:7334"), ip_network("192.168.0.0/22")))

  expect_true(is_within_any(ip_address("192.168.0.1"), ip_network(c("2001:db8::/36", "192.168.0.0/22"))))
  expect_false(is_within_any(ip_address("192.168.0.1"), ip_network(c("2001:db8::/36", "192.168.0.0/32"))))
  expect_false(is_within_any(ip_address("192.168.0.1"), ip_network(c("2001:db8::/36", "2001:db8::/64"))))

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

  expect_equal(is_subnet(ip_network(NA), ip_network("192.168.0.0/24")), NA)
  expect_equal(is_subnet(ip_network("192.168.0.0/24"), ip_network(NA)), NA)

  expect_equal(is_supernet(ip_network(NA), ip_network("192.168.0.0/24")), NA)
  expect_equal(is_supernet(ip_network("192.168.0.0/24"), ip_network(NA)), NA)
})
