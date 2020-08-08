test_that("is_multicast works", {
  expect_reserved(is_multicast, ip_network("224.0.0.0/4"))
  expect_reserved(is_multicast, ip_network("ff00::/8"))

  expect_equal(is_multicast(ip_address()), logical())
  expect_equal(is_multicast(ip_network()), logical())

  expect_equal(is_multicast(ip_address(NA)), NA)
  expect_equal(is_multicast(ip_network(NA)), NA)

  expect_error(is_multicast("hello"))
})

test_that("is_unspecified works", {
  expect_reserved(is_unspecified, ip_network("0.0.0.0/32"))
  expect_reserved(is_unspecified, ip_network("::/128"))

  expect_equal(is_unspecified(ip_address()), logical())
  expect_equal(is_unspecified(ip_network()), logical())

  expect_equal(is_unspecified(ip_address(NA)), NA)
  expect_equal(is_unspecified(ip_network(NA)), NA)

  expect_error(is_unspecified("hello"))
})

test_that("is_loopback works", {
  expect_reserved(is_loopback, ip_network("127.0.0.0/8"))
  expect_reserved(is_loopback, ip_network("::1/128"))

  expect_equal(is_loopback(ip_address()), logical())
  expect_equal(is_loopback(ip_network()), logical())

  expect_equal(is_loopback(ip_address(NA)), NA)
  expect_equal(is_loopback(ip_network(NA)), NA)

  expect_error(is_loopback("hello"))
})

test_that("is_link_local works", {
  expect_reserved(is_link_local, ip_network("169.254.0.0/16"))
  expect_reserved(is_link_local, ip_network("fe80::/10"))

  expect_equal(is_link_local(ip_address()), logical())
  expect_equal(is_link_local(ip_network()), logical())

  expect_equal(is_link_local(ip_address(NA)), NA)
  expect_equal(is_link_local(ip_network(NA)), NA)

  expect_error(is_link_local("hello"))
})

test_that("is_site_local works", {
  expect_false(is_site_local(ip_address("0.0.0.0")))
  expect_false(is_site_local(ip_network("0.0.0.0/0")))
  expect_reserved(is_site_local, ip_network("fec0::/10"))

  expect_equal(is_site_local(ip_address()), logical())
  expect_equal(is_site_local(ip_network()), logical())

  expect_equal(is_site_local(ip_address(NA)), NA)
  expect_equal(is_site_local(ip_network(NA)), NA)

  expect_error(is_site_local("hello"))
})
