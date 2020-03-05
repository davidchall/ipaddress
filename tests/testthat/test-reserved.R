test_that("is_multicast works", {
  # IPv4: 224.0.0.0/4
  expect_equal(
    is_multicast(ip_address(c("223.255.255.255", "224.0.0.0", "239.255.255.255", "240.0.0.0"))),
    c(FALSE, TRUE, TRUE, FALSE)
  )
  expect_equal(
    is_multicast(ip_network(c("224.0.0.0/4", "224.0.0.0/5", "224.0.0.0/3"))),
    c(TRUE, TRUE, FALSE)
  )

  # IPv6: ff00::/8
  expect_equal(
    is_multicast(ip_address(c("feff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "ff00::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))),
    c(FALSE, TRUE, TRUE)
  )
  expect_equal(
    is_multicast(ip_network(c("ff00::/8", "ff00::/9", "fe00::/7"))),
    c(TRUE, TRUE, FALSE)
  )

  expect_equal(is_multicast(ip_address()), logical())
  expect_equal(is_multicast(ip_network()), logical())

  expect_equal(is_multicast(ip_address(NA)), NA)
  expect_equal(is_multicast(ip_network(NA)), NA)

  expect_error(is_multicast("hello"))
})

test_that("is_unspecified works", {
  # IPv4: 0.0.0.0
  expect_equal(
    is_unspecified(ip_address(c("0.0.0.0", "0.0.0.1"))),
    c(TRUE, FALSE)
  )
  expect_equal(
    is_unspecified(ip_network(c("0.0.0.0/32", "0.0.0.0/31"))),
    c(TRUE, FALSE)
  )

  # IPv6: ::
  expect_equal(
    is_unspecified(ip_address(c("::", "::1"))),
    c(TRUE, FALSE)
  )
  expect_equal(
    is_unspecified(ip_network(c("::/128", "::/127"))),
    c(TRUE, FALSE)
  )

  expect_equal(is_unspecified(ip_address()), logical())
  expect_equal(is_unspecified(ip_network()), logical())

  expect_equal(is_unspecified(ip_address(NA)), NA)
  expect_equal(is_unspecified(ip_network(NA)), NA)

  expect_error(is_unspecified("hello"))
})

test_that("is_loopback works", {
  # IPv4: 127.0.0.0/8
  expect_equal(
    is_loopback(ip_address(c("126.255.255.255", "127.0.0.0", "127.255.255.255", "128.0.0.0"))),
    c(FALSE, TRUE, TRUE, FALSE)
  )
  expect_equal(
    is_loopback(ip_network(c("127.0.0.0/8", "127.0.0.0/9", "126.0.0.0/7"))),
    c(TRUE, TRUE, FALSE)
  )

  # IPv6: ::1/128
  expect_equal(
    is_loopback(ip_address(c("::", "::1", "::2"))),
    c(FALSE, TRUE, FALSE)
  )
  expect_equal(
    is_loopback(ip_network(c("::1/128", "::/127"))),
    c(TRUE, FALSE)
  )

  expect_equal(is_loopback(ip_address()), logical())
  expect_equal(is_loopback(ip_network()), logical())

  expect_equal(is_loopback(ip_address(NA)), NA)
  expect_equal(is_loopback(ip_network(NA)), NA)

  expect_error(is_loopback("hello"))
})

test_that("is_link_local works", {
  # IPv4: 169.254.0.0/16
  expect_equal(
    is_link_local(ip_address(c("169.253.255.255", "169.254.0.0", "169.254.255.255", "169.255.0.0"))),
    c(FALSE, TRUE, TRUE, FALSE)
  )
  expect_equal(
    is_link_local(ip_network(c("169.254.0.0/16", "169.254.0.0/17", "169.254.0.0/15"))),
    c(TRUE, TRUE, FALSE)
  )

  # IPv6: fe80::/10
  expect_equal(
    is_link_local(ip_address(c("fe7f:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "fe80::", "febf:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "fec0::"))),
    c(FALSE, TRUE, TRUE, FALSE)
  )
  expect_equal(
    is_link_local(ip_network(c("fe80::/10", "fe80::/11", "fe80::/9"))),
    c(TRUE, TRUE, FALSE)
  )

  expect_equal(is_link_local(ip_address()), logical())
  expect_equal(is_link_local(ip_network()), logical())

  expect_equal(is_link_local(ip_address(NA)), NA)
  expect_equal(is_link_local(ip_network(NA)), NA)

  expect_error(is_link_local("hello"))
})
