test_that("masking works", {
  ipv4 <- c("0.0.0.0/0", "192.168.128.1/22", "129.168.1.1/24", "1.2.3.4/32")
  ipv6 <- c("::/0", "2001:db00::1/35", "2001:db00::1/73", "::/128")

  expected <- c(0L, 22L, 24L, 32L)
  expect_equal(prefix_length(ip_network(ipv4, strict = FALSE)), expected)
  expect_equal(prefix_length(ip_interface(ipv4)), expected)

  expected <- c(0L, 35L, 73L, 128L)
  expect_equal(prefix_length(ip_network(ipv6, strict = FALSE)), expected)
  expect_equal(prefix_length(ip_interface(ipv6)), expected)

  expected <- ip_address(c("0.0.0.0", "255.255.252.0", "255.255.255.0", "255.255.255.255"))
  expect_equal(netmask(ip_network(ipv4, strict = FALSE)), expected)
  expect_equal(netmask(ip_interface(ipv4)), expected)
  expect_equal(netmask(c(0L, 22L, 24L, 32L), FALSE), expected)

  expected <- ip_address(c("255.255.255.255", "0.0.3.255", "0.0.0.255", "0.0.0.0"))
  expect_equal(hostmask(ip_network(ipv4, strict = FALSE)), expected)
  expect_equal(hostmask(ip_interface(ipv4)), expected)
  expect_equal(hostmask(c(0L, 22L, 24L, 32L), FALSE), expected)

  expected <- ip_address(c("::", "ffff:ffff:e000::", "ffff:ffff:ffff:ffff:ff80::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))
  expect_equal(netmask(ip_network(ipv6, strict = FALSE)), expected)
  expect_equal(netmask(ip_interface(ipv6)), expected)
  expect_equal(netmask(c(0L, 35L, 73L, 128L), TRUE), expected)

  expected <- ip_address(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "::1fff:ffff:ffff:ffff:ffff:ffff", "::7f:ffff:ffff:ffff", "::"))
  expect_equal(hostmask(ip_network(ipv6, strict = FALSE)), expected)
  expect_equal(hostmask(ip_interface(ipv6)), expected)
  expect_equal(hostmask(c(0L, 35L, 73L, 128L), TRUE), expected)
})

test_that("prefix_length calculated correctly", {
  expect_equal(
    prefix_length(ip_address(c("255.255.255.0", "0.255.255.255", "255.255.255.128", "0.0.0.127"))),
    c(24L, 8L, 25L, 25L)
  )
  expect_equal(
    prefix_length(ip_address(c("ffff::", "::ffff", "fff8::", "::7:ffff"))),
    c(16L, 112L, 13L, 109L)
  )

  # ambiguous cases (assumes netmask)
  expect_equal(prefix_length(ip_address(c("0.0.0.0", "255.255.255.255"))), c(0L, 32L))
  expect_equal(prefix_length(ip_address(c("::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))), c(0L, 128L))

  # invalid netmask/hostmask
  expect_warning(prefix_length(ip_address("1.2.3.4")))
  expect_warning(prefix_length(ip_address("abcd::1")))
})

test_that("vector recycling works", {
  expect_equal(
    netmask(10L, c(TRUE, FALSE)),
    ip_address(c("ffc0::", "255.192.0.0"))
  )
  expect_equal(
    hostmask(10L, c(TRUE, FALSE)),
    ip_address(c("3f:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "0.63.255.255"))
  )

  expect_error(netmask(rep(0L, 3), rep(TRUE, 2)), class = "vctrs_error_incompatible_size")
  expect_error(hostmask(rep(0L, 3), rep(TRUE, 2)), class = "vctrs_error_incompatible_size")
})

test_that("default is_ipv6 works", {
  expect_equal(
    netmask(c(32L, 33L)),
    ip_address(c("255.255.255.255", "ffff:ffff:8000::"))
  )
  expect_equal(
    hostmask(c(32L, 33L)),
    ip_address(c("0.0.0.0", "::7fff:ffff:ffff:ffff:ffff:ffff"))
  )
})

test_that("input validation works", {
  expect_snapshot(error = TRUE, {
    prefix_length(1L)
  })
  expect_snapshot(error = TRUE, {
    netmask(ip_address("1.2.3.4"))

    netmask(1.5, FALSE)
    netmask(1L, "yes")

    netmask(-1L, FALSE)
    netmask(33L, FALSE)
    netmask(129L, TRUE)
  })
  expect_snapshot(error = TRUE, {
    hostmask(ip_address("1.2.3.4"))

    hostmask(1.5, FALSE)
    hostmask(1L, "yes")

    hostmask(-1L, FALSE)
    hostmask(33L, FALSE)
    hostmask(129L, TRUE)
  })
})

test_that("missing values work", {
  expect_equal(prefix_length(ip_network(NA)), NA_integer_)
  expect_equal(prefix_length(ip_interface(NA)), NA_integer_)
  expect_equal(prefix_length(ip_address(NA)), NA_integer_)
  expect_equal(netmask(ip_network(NA)), ip_address(NA))
  expect_equal(hostmask(ip_network(NA)), ip_address(NA))
  expect_equal(netmask(ip_interface(NA)), ip_address(NA))
  expect_equal(hostmask(ip_interface(NA)), ip_address(NA))
  expect_equal(netmask(c(1L, NA), c(NA, TRUE)), ip_address(c(NA, NA)))
  expect_equal(hostmask(c(1L, NA), c(NA, TRUE)), ip_address(c(NA, NA)))
})
