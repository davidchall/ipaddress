test_that("bitwise NOT works", {
  expect_equal(
    !ip_address(c("0.0.0.0", "255.255.255.255", "192.168.0.1")),
    ip_address(c("255.255.255.255", "0.0.0.0", "63.87.255.254"))
  )
  expect_equal(
    !ip_address(c("::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "2001:db8::8a2e:370:7334")),
    ip_address(c("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff", "::", "dffe:f247:ffff:ffff:ffff:75d1:fc8f:8ccb"))
  )

  # missing or empty values
  expect_equal(!ip_address(), ip_address())
  expect_equal(!ip_address(NA), ip_address(NA))
})

test_that("bitwise AND works", {
  expect_equal(
    ip_address("192.168.0.1") & ip_address("100.2.0.3"),
    ip_address("64.0.0.1")
  )
  expect_equal(
    ip_address("2001:db8::8a2e:370:7334") & ip_address("101:18::54"),
    ip_address("1:18::14")
  )

  # vector recycling
  expect_equal(
    ip_address(c("192.168.0.1", "255.255.255.255")) & ip_address("100.2.0.3"),
    ip_address(c("64.0.0.1", "100.2.0.3"))
  )
  expect_error(ip_address(rep("0.0.0.0", 2)) & ip_address(rep("0.0.0.0", 3)))

  # missing or empty values
  expect_equal(ip_address() & ip_address(), ip_address())
  expect_equal(ip_address(NA) & ip_address("::"), ip_address(NA))
  expect_equal(ip_address("::") & ip_address(NA), ip_address(NA))

  # incompatible address spaces
  expect_equal(ip_address("1.2.3.4") & ip_address("::1"), ip_address(NA))
})

test_that("bitwise OR works", {
  expect_equal(
    ip_address("192.168.0.1") | ip_address("100.2.0.3"),
    ip_address("228.170.0.3")
  )
  expect_equal(
    ip_address("2001:db8::8a2e:370:7334") | ip_address("101:18::54"),
    ip_address("2101:db8::8a2e:370:7374")
  )

  # vector recycling
  expect_equal(
    ip_address(c("192.168.0.1", "255.255.255.255")) | ip_address("100.2.0.3"),
    ip_address(c("228.170.0.3", "255.255.255.255"))
  )
  expect_error(ip_address(rep("0.0.0.0", 2)) | ip_address(rep("0.0.0.0", 3)))

  # missing or empty values
  expect_equal(ip_address() | ip_address(), ip_address())
  expect_equal(ip_address(NA) | ip_address("::"), ip_address(NA))
  expect_equal(ip_address("::") | ip_address(NA), ip_address(NA))

  # incompatible address spaces
  expect_equal(ip_address("1.2.3.4") | ip_address("::1"), ip_address(NA))
})

test_that("bitwise XOR works", {
  expect_equal(
    ip_address("192.168.0.1") ^ ip_address("100.2.0.3"),
    ip_address("164.170.0.2")
  )
  expect_equal(
    ip_address("2001:db8::8a2e:370:7334") ^ ip_address("101:18::54"),
    ip_address("2100:da0::8a2e:370:7360")
  )

  # vector recycling
  expect_equal(
    ip_address(c("192.168.0.1", "255.255.255.255")) ^ ip_address("100.2.0.3"),
    ip_address(c("164.170.0.2", "155.253.255.252"))
  )
  expect_error(ip_address(rep("0.0.0.0", 2)) ^ ip_address(rep("0.0.0.0", 3)))

  # missing or empty values
  expect_equal(ip_address() ^ ip_address(), ip_address())
  expect_equal(ip_address(NA) ^ ip_address("::"), ip_address(NA))
  expect_equal(ip_address("::") ^ ip_address(NA), ip_address(NA))

  # incompatible address spaces
  expect_equal(ip_address("1.2.3.4") ^ ip_address("::1"), ip_address(NA))
})

test_that("addition and subtraction work", {
  expect_equal(ip_address("192.168.0.1") + 5L, ip_address("192.168.0.6"))
  expect_equal(ip_address("192.168.0.1") - 5L, ip_address("192.167.255.252"))
  expect_equal(ip_address("2001:db8::7334") + 5L, ip_address("2001:db8::7339"))
  expect_equal(ip_address("2001:db8::7334") - 5L, ip_address("2001:db8::732f"))

  # integerish accepted
  expect_equal(ip_address("192.168.0.1") + 5, ip_address("192.168.0.6"))
  expect_equal(ip_address("192.168.0.1") - 5, ip_address("192.167.255.252"))

  # vector recycling
  expect_equal(
    ip_address("192.168.0.1") + -2:2,
    ip_address(c("192.167.255.255", "192.168.0.0", "192.168.0.1", "192.168.0.2", "192.168.0.3"))
  )
  expect_equal(
    ip_address(c("192.168.0.1", "255.255.255.254")) + 1L,
    ip_address(c("192.168.0.2", "255.255.255.255"))
  )
  expect_error(ip_address(c("0.0.0.0", "1.2.3.4")) + c(1L, 2L, 3L))

  # missing values
  expect_equal(ip_address(NA) + 1L, ip_address(NA))
  expect_equal(ip_address(NA) - 1L, ip_address(NA))
  expect_equal(ip_address("192.168.0.1") + NA_integer_, ip_address(NA))
  expect_equal(ip_address("192.168.0.1") - NA_integer_, ip_address(NA))
  expect_equal(ip_address("192.168.0.1") + NA_real_, ip_address(NA))
  expect_equal(ip_address("192.168.0.1") - NA_real_, ip_address(NA))

  # invalid arguments
  expect_warning(ip_address("0.0.0.0") - 1L, "out-of-range")
  expect_warning(ip_address("255.255.255.255") + 1L, "out-of-range")
  expect_warning(ip_address("::") - 1L, "out-of-range")
  expect_warning(ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff") + 1L, "out-of-range")

  # address must come first
  expect_error(1L + ip_address("0.0.0.0"))
})

test_that("other operations fail", {
  expect_error(ip_address() + ip_address())
  expect_error(-ip_address())
  expect_error(ip_address() + 1.5)
  expect_error(ip_address() * 1L)
})
