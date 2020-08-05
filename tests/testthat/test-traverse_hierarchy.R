test_that("supernet() works", {
  expect_equal(supernet(ip_network("192.168.0.0/24")), ip_network("192.168.0.0/23"))
  expect_equal(supernet(ip_network("2001:db8::/36")), ip_network("2001:db8::/35"))

  expect_equal(supernet(ip_network("192.168.0.0/24"), new_prefix = 10L), ip_network("192.128.0.0/10"))
  expect_equal(supernet(ip_network("2001:db8::/36"), new_prefix = 10L), ip_network("2000::/10"))

  expect_error(supernet(ip_network("0.0.0.0/0")))
  expect_error(supernet(ip_network("::/0")))
})

test_that("subnets() works", {
  expect_equal(subnets(ip_network("192.168.0.0/24")), ip_network(c("192.168.0.0/25", "192.168.0.128/25")))
  expect_equal(subnets(ip_network("2001:db8::/36")), ip_network(c("2001:db8::/37", "2001:db8:800::/37")))

  expect_equal(subnets(ip_network("192.168.0.0/24"), new_prefix = 26L), ip_network(c("192.168.0.0/26", "192.168.0.64/26", "192.168.0.128/26", "192.168.0.192/26")))
  expect_equal(subnets(ip_network("2001:db8::/36"), new_prefix = 38L), ip_network(c("2001:db8::/38", "2001:db8:400::/38", "2001:db8:800::/38", "2001:db8:c00::/38")))
  expect_length(subnets(ip_network("192.168.0.0/24"), new_prefix = 32L), num_addresses(ip_network("192.168.0.0/24")))
  expect_length(subnets(ip_network("2001:db8::/120"), new_prefix = 128L), num_addresses(ip_network("2001:db8::/120")))

  expect_equal(
    subnets(ip_network("ffff:ffff:ffff:ffff:ffff:ffff:ffff:fffe/127")),
    ip_network(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:fffe/128", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/128"))
  )

  expect_error(subnets(ip_network("0.0.0.0/32")))
  expect_error(subnets(ip_network("::/128")))
})

test_that("vector recycling works", {
  expect_equal(
    supernet(ip_network("192.168.0.0/24"), new_prefix = c(23L, 10L)),
    ip_network(c("192.168.0.0/23", "192.128.0.0/10"))
  )
})

test_that("missing values work", {
  expect_equal(supernet(ip_network(NA)), ip_network(NA))
  expect_equal(subnets(ip_network(NA)), ip_network(NA))

  expect_error(supernet(ip_network("192.168.0.0/24"), new_prefix = NA))
  expect_equal(supernet(ip_network("192.168.0.0/24"), new_prefix = NA_integer_), ip_network(NA))
  expect_error(subnets(ip_network("192.168.0.0/24"), new_prefix = NA))
  expect_equal(subnets(ip_network("192.168.0.0/24"), new_prefix = NA_integer_), ip_network(NA))
})

test_that("input validation", {
  expect_error(supernet(ip_address("1.2.3.4")))
  expect_error(subnets(ip_address("1.2.3.4")))
  expect_error(subnets(ip_network(c("192.168.0.0/20", "192.168.0.0/20"))))

  expect_error(supernet(ip_network("192.168.0.0/20"), new_prefix = "yes"))
  expect_error(subnets(ip_network("192.168.0.0/20"), new_prefix = "yes"))
  expect_error(subnets(ip_network("192.168.0.0/20"), new_prefix = c(1L, 2L)))

  expect_error(supernet(ip_network("192.168.0.0/20"), new_prefix = -1L))
  expect_error(subnets(ip_network("192.168.0.0/20"), new_prefix = -1L))
  expect_error(supernet(ip_network("192.168.0.0/20"), new_prefix = 33L))
  expect_error(subnets(ip_network("192.168.0.0/20"), new_prefix = 33L))
  expect_error(supernet(ip_network("192.168.0.0/20"), new_prefix = 21L))
  expect_error(subnets(ip_network("192.168.0.0/20"), new_prefix = 19L))

  expect_error(subnets(ip_network("0.0.0.0/0"), new_prefix = 32L))
  expect_error(subnets(ip_network("::/97"), new_prefix = 128L))
})
