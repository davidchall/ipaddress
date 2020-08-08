check_reserved <- function(check_func, net) {

  # check ip_address version of function
  net_start <- network_address(net)
  net_end <- broadcast_address(net)
  space_start <- ip_address(c("0.0.0.0", "::"))
  space_end <- ip_address(c("255.255.255.255", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))

  boundaries <- vec_c(
    if (all(net_start != space_start)) net_start - 1,
    net_start,
    net_end,
    if (all(net_end != space_end)) net_end + 1
  )
  expected <- c(
    if (all(net_start != space_start)) FALSE,
    TRUE,
    TRUE,
    if (all(net_end != space_end)) FALSE
  )

  expect_equal(check_func(boundaries), expected)

  # check ip_network version of function
  other_networks <- vec_c(
    net,
    if (prefix_length(net) != max_prefix_length(net)) subnets(net),
    if (prefix_length(net) != 0) supernet(net)
  )
  expected <- c(
    TRUE,
    if (prefix_length(net) != max_prefix_length(net)) c(TRUE, TRUE),
    if (prefix_length(net) != 0) FALSE
  )

  expect_equal(check_func(other_networks), expected)
}

test_that("is_multicast works", {
  check_reserved(is_multicast, ip_network("224.0.0.0/4"))
  check_reserved(is_multicast, ip_network("ff00::/8"))

  expect_equal(is_multicast(ip_address()), logical())
  expect_equal(is_multicast(ip_network()), logical())

  expect_equal(is_multicast(ip_address(NA)), NA)
  expect_equal(is_multicast(ip_network(NA)), NA)

  expect_error(is_multicast("hello"))
})

test_that("is_unspecified works", {
  check_reserved(is_unspecified, ip_network("0.0.0.0/32"))
  check_reserved(is_unspecified, ip_network("::/128"))

  expect_equal(is_unspecified(ip_address()), logical())
  expect_equal(is_unspecified(ip_network()), logical())

  expect_equal(is_unspecified(ip_address(NA)), NA)
  expect_equal(is_unspecified(ip_network(NA)), NA)

  expect_error(is_unspecified("hello"))
})

test_that("is_loopback works", {
  check_reserved(is_loopback, ip_network("127.0.0.0/8"))
  check_reserved(is_loopback, ip_network("::1/128"))

  expect_equal(is_loopback(ip_address()), logical())
  expect_equal(is_loopback(ip_network()), logical())

  expect_equal(is_loopback(ip_address(NA)), NA)
  expect_equal(is_loopback(ip_network(NA)), NA)

  expect_error(is_loopback("hello"))
})

test_that("is_link_local works", {
  check_reserved(is_link_local, ip_network("169.254.0.0/16"))
  check_reserved(is_link_local, ip_network("fe80::/10"))

  expect_equal(is_link_local(ip_address()), logical())
  expect_equal(is_link_local(ip_network()), logical())

  expect_equal(is_link_local(ip_address(NA)), NA)
  expect_equal(is_link_local(ip_network(NA)), NA)

  expect_error(is_link_local("hello"))
})
