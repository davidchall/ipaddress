ipv4 <- ip_network("192.128.0.0/12")
ipv6 <- ip_network("2001:db8::/108")

test_that("input validation works", {
  expect_snapshot(error = TRUE, {
    sample_network(rep(ipv4, 2), 1)
    sample_network(ip_network(), 1)
    sample_network(ip_address("192.168.0.0"), 1)
    sample_network(ip_network(NA), 1)
  })

  expect_snapshot(error = TRUE, {
    sample_network(ip_network("0.0.0.0/32"), -1)
    sample_network(ip_network("0.0.0.0/32"), 2^31, replace = TRUE)
    sample_network(ip_network("0.0.0.0/32"), NA)
  })

  expect_snapshot(error = TRUE, {
    sample_network(ip_network("0.0.0.0/32"), 1, replace = NA)
    sample_network(ip_network("0.0.0.0/32"), 1, replace = 1)
  })

  expect_snapshot(error = TRUE, {
    sample_network(ipv4, num_addresses(ipv4) + 1, replace = FALSE)
  })
})

test_that("generates within network", {
  expect_true(all(is_within_any(sample_network(ipv4, 1000, replace = FALSE), ipv4)))
  expect_true(all(is_within_any(sample_network(ipv4, 1000, replace = TRUE), ipv4)))

  expect_true(all(is_within_any(sample_network(ipv6, 1000, replace = FALSE), ipv6)))
  expect_true(all(is_within_any(sample_network(ipv6, 1000, replace = TRUE), ipv6)))
})

test_that("can avoid duplicates", {
  expect_true(any(duplicated(sample_network(ipv4, 1e5, replace = TRUE))))
  expect_true(any(duplicated(sample_network(ipv6, 1e5, replace = TRUE))))
  expect_false(any(duplicated(sample_network(ipv4, 1e5, replace = FALSE))))
  expect_false(any(duplicated(sample_network(ipv6, 1e5, replace = FALSE))))
})

test_that("can sample entire address space", {
  expect_true(all(is_ipv4(sample_ipv4(1000, replace = FALSE))))
  expect_true(all(is_ipv6(sample_ipv6(1000, replace = FALSE))))
  expect_true(all(is_ipv4(sample_ipv4(1000, replace = TRUE))))
  expect_true(all(is_ipv6(sample_ipv6(1000, replace = TRUE))))
})

test_that("sampling is random but reproducible", {
  set.seed(2020)
  x1 <- sample_ipv4(100)
  x2 <- sample_ipv4(100)
  set.seed(2020)
  x3 <- sample_ipv4(100)
  set.seed(NULL)

  expect_false(all(x1 == x2))
  expect_true(all(x1 == x3))
})

test_that("optimize performance for small networks", {
  small_network <- ip_network("192.128.0.0/20")
  expect_true(all(is_within_any(sample_network(small_network, 1000, replace = FALSE), small_network)))
  expect_true(all(is_within_any(sample_network(small_network, 1000, replace = TRUE), small_network)))

  expect_true(any(duplicated(sample_network(small_network, 1000, replace = TRUE))))
  expect_false(any(duplicated(sample_network(small_network, 1000, replace = FALSE))))
})
