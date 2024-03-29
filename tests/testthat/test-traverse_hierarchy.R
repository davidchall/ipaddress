test_that("supernet() works", {
  expect_equal(supernet(ip_network("192.168.0.0/24")), ip_network("192.168.0.0/23"))
  expect_equal(supernet(ip_network("2001:db8::/36")), ip_network("2001:db8::/35"))

  expect_equal(supernet(ip_network("192.168.0.0/24"), new_prefix = 10L), ip_network("192.128.0.0/10"))
  expect_equal(supernet(ip_network("2001:db8::/36"), new_prefix = 10L), ip_network("2000::/10"))

  expect_snapshot(error = TRUE, {
    supernet(ip_network("0.0.0.0/0"))
    supernet(ip_network("::/0"))
  })
})

test_that("subnets() works", {
  expect_equal(
    subnets(ip_network(c("192.168.0.0/24", "2001:db8::/36"))),
    list_of(
      ip_network(c("192.168.0.0/25", "192.168.0.128/25")),
      ip_network(c("2001:db8::/37", "2001:db8:800::/37"))
    )
  )

  expect_equal(
    subnets(ip_network(c("192.168.0.0/24", "2001:db8::/36")), new_prefix = c(26L, 38L)),
    list_of(
      ip_network(c("192.168.0.0/26", "192.168.0.64/26", "192.168.0.128/26", "192.168.0.192/26")),
      ip_network(c("2001:db8::/38", "2001:db8:400::/38", "2001:db8:800::/38", "2001:db8:c00::/38"))
    )
  )

  expect_equal(
    sapply(subnets(ip_network(c("192.168.0.0/24", "2001:db8::/120")), new_prefix = c(32L, 128L)), length),
    num_addresses(ip_network(c("192.168.0.0/24", "2001:db8::/120")))
  )

  expect_equal(
    subnets(ip_network("ffff:ffff:ffff:ffff:ffff:ffff:ffff:fffe/127")),
    list_of(ip_network(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:fffe/128", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/128")))
  )

  expect_snapshot(error = TRUE, {
    subnets(ip_network("0.0.0.0/32"))
    subnets(ip_network("::/128"))
  })
})

test_that("vector recycling works", {
  expect_equal(
    supernet(ip_network("192.168.0.0/24"), new_prefix = c(23L, 10L)),
    ip_network(c("192.168.0.0/23", "192.128.0.0/10"))
  )
  expect_equal(
    subnets(ip_network("192.168.0.0/24"), new_prefix = c(25L, 26L)),
    list_of(
      ip_network(c("192.168.0.0/25", "192.168.0.128/25")),
      ip_network(c("192.168.0.0/26", "192.168.0.64/26", "192.168.0.128/26", "192.168.0.192/26"))
    )
  )
})

test_that("missing values work", {
  expect_equal(supernet(ip_network(NA)), ip_network(NA))
  expect_equal(subnets(ip_network(NA)), list_of(ip_network(NA)))

  expect_snapshot(error = TRUE, {
    supernet(ip_network("192.168.0.0/24"), new_prefix = NA)
  })
  expect_snapshot(error = TRUE, {
    subnets(ip_network("192.168.0.0/24"), new_prefix = NA)
  })
  expect_equal(supernet(ip_network("192.168.0.0/24"), new_prefix = NA_integer_), ip_network(NA))
  expect_equal(subnets(ip_network("192.168.0.0/24"), new_prefix = NA_integer_), list_of(ip_network(NA)))
})

test_that("input validation", {
  expect_snapshot(error = TRUE, {
    supernet(ip_address("1.2.3.4"))

    supernet(ip_network("192.168.0.0/20"), new_prefix = "yes")

    supernet(ip_network("192.168.0.0/20"), new_prefix = -1L)
    supernet(ip_network("192.168.0.0/20"), new_prefix = 21L)
  })
  expect_snapshot(error = TRUE, {
    subnets(ip_address("1.2.3.4"))

    subnets(ip_network("192.168.0.0/20"), new_prefix = "yes")

    subnets(ip_network("192.168.0.0/20"), new_prefix = -1L)
    subnets(ip_network("192.168.0.0/20"), new_prefix = 33L)
    subnets(ip_network("192.168.0.0/20"), new_prefix = 19L)
  })

  expect_error(subnets(ip_network("0.0.0.0/0"), new_prefix = 32L), "Too many subnets")
  expect_error(subnets(ip_network("::/97"), new_prefix = 128L), "Too many subnets")
})
