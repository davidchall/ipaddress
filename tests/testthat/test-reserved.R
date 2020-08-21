test_that("is_private works", {
  expect_reserved(is_private, ip_network("0.0.0.0/8"))
  expect_reserved(is_private, ip_network("10.0.0.0/8"))
  expect_reserved(is_private, ip_network("127.0.0.0/8"))
  expect_reserved(is_private, ip_network("169.254.0.0/16"))
  expect_reserved(is_private, ip_network("172.16.0.0/12"))
  expect_reserved(is_private, ip_network("192.0.0.0/29"))
  expect_reserved(is_private, ip_network("192.0.0.170/31"))
  expect_reserved(is_private, ip_network("192.0.2.0/24"))
  expect_reserved(is_private, ip_network("192.168.0.0/16"))
  expect_reserved(is_private, ip_network("198.18.0.0/15"))
  expect_reserved(is_private, ip_network("198.51.100.0/24"))
  expect_reserved(is_private, ip_network("203.0.113.0/24"))
  expect_reserved(is_private, ip_network("240.0.0.0/4"))
  expect_reserved(is_private, ip_network("::/127"))
  expect_reserved(is_private, ip_network("::ffff:0:0/96"))
  expect_reserved(is_private, ip_network("100::/64"))
  expect_reserved(is_private, ip_network("2001::/23"))
  expect_reserved(is_private, ip_network("2001:db8::/32"))
  expect_reserved(is_private, ip_network("fc00::/7"))
  expect_reserved(is_private, ip_network("fe80::/10"))

  expect_equal(is_private(ip_address()), logical())
  expect_equal(is_private(ip_network()), logical())

  expect_equal(is_private(ip_address(NA)), NA)
  expect_equal(is_private(ip_network(NA)), NA)

  expect_error(is_private("hello"), "`x` must be an ip_address or ip_network vector")
})

test_that("is_global works", {
  expect_reserved(is_global, ip_network("1.0.0.0/8"), ignore_after = TRUE)
  expect_reserved(is_global, ip_network("2.0.0.0/7"), ignore_before = TRUE, ignore_after = TRUE)
  expect_reserved(is_global, ip_network("4.0.0.0/6"), ignore_before = TRUE, ignore_after = TRUE)
  expect_reserved(is_global, ip_network("8.0.0.0/7"), ignore_before = TRUE, ignore_super = TRUE)
  expect_reserved(is_global, ip_network("2001:db9::/32"), ignore_after = TRUE)

  expect_equal(is_global(ip_address()), logical())
  expect_equal(is_global(ip_network()), logical())

  expect_equal(is_global(ip_address(NA)), NA)
  expect_equal(is_global(ip_network(NA)), NA)

  expect_error(is_global("hello"), "`x` must be an ip_address or ip_network vector")
})

test_that("is_multicast works", {
  expect_reserved(is_multicast, ip_network("224.0.0.0/4"))
  expect_reserved(is_multicast, ip_network("ff00::/8"))

  expect_equal(is_multicast(ip_address()), logical())
  expect_equal(is_multicast(ip_network()), logical())

  expect_equal(is_multicast(ip_address(NA)), NA)
  expect_equal(is_multicast(ip_network(NA)), NA)

  expect_error(is_multicast("hello"), "`x` must be an ip_address or ip_network vector")
})

test_that("is_unspecified works", {
  expect_reserved(is_unspecified, ip_network("0.0.0.0/32"))
  expect_reserved(is_unspecified, ip_network("::/128"))

  expect_equal(is_unspecified(ip_address()), logical())
  expect_equal(is_unspecified(ip_network()), logical())

  expect_equal(is_unspecified(ip_address(NA)), NA)
  expect_equal(is_unspecified(ip_network(NA)), NA)

  expect_error(is_unspecified("hello"), "`x` must be an ip_address or ip_network vector")
})

test_that("is_reserved works", {
  expect_reserved(is_reserved, ip_network("240.0.0.0/4"))
  expect_reserved(is_reserved, ip_network("::/3"))
  expect_reserved(is_reserved, ip_network("4000::/2"), ignore_after = TRUE, ignore_super = TRUE)
  expect_reserved(is_reserved, ip_network("8000::/2"), ignore_before = TRUE, ignore_after = TRUE)
  expect_reserved(is_reserved, ip_network("c000::/3"), ignore_before = TRUE, ignore_after = TRUE)
  expect_reserved(is_reserved, ip_network("e000::/4"), ignore_before = TRUE, ignore_after = TRUE)
  expect_reserved(is_reserved, ip_network("f000::/5"), ignore_before = TRUE, ignore_after = TRUE)
  expect_reserved(is_reserved, ip_network("f800::/6"), ignore_before = TRUE)
  expect_reserved(is_reserved, ip_network("fe00::/9"))

  expect_equal(is_reserved(ip_address()), logical())
  expect_equal(is_reserved(ip_network()), logical())

  expect_equal(is_reserved(ip_address(NA)), NA)
  expect_equal(is_reserved(ip_network(NA)), NA)

  expect_error(is_reserved("hello"), "`x` must be an ip_address or ip_network vector")
})

test_that("is_loopback works", {
  expect_reserved(is_loopback, ip_network("127.0.0.0/8"))
  expect_reserved(is_loopback, ip_network("::1/128"))

  expect_equal(is_loopback(ip_address()), logical())
  expect_equal(is_loopback(ip_network()), logical())

  expect_equal(is_loopback(ip_address(NA)), NA)
  expect_equal(is_loopback(ip_network(NA)), NA)

  expect_error(is_loopback("hello"), "`x` must be an ip_address or ip_network vector")
})

test_that("is_link_local works", {
  expect_reserved(is_link_local, ip_network("169.254.0.0/16"))
  expect_reserved(is_link_local, ip_network("fe80::/10"))

  expect_equal(is_link_local(ip_address()), logical())
  expect_equal(is_link_local(ip_network()), logical())

  expect_equal(is_link_local(ip_address(NA)), NA)
  expect_equal(is_link_local(ip_network(NA)), NA)

  expect_error(is_link_local("hello"), "`x` must be an ip_address or ip_network vector")
})

test_that("is_site_local works", {
  expect_false(is_site_local(ip_address("0.0.0.0")))
  expect_false(is_site_local(ip_network("0.0.0.0/0")))
  expect_reserved(is_site_local, ip_network("fec0::/10"))

  expect_equal(is_site_local(ip_address()), logical())
  expect_equal(is_site_local(ip_network()), logical())

  expect_equal(is_site_local(ip_address(NA)), NA)
  expect_equal(is_site_local(ip_network(NA)), NA)

  expect_error(is_site_local("hello"), "`x` must be an ip_address or ip_network vector")
})
