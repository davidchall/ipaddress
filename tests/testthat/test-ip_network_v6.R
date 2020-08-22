x <- c("::/128", "256::/72", "2001:db8::/36", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/128")

test_that("alternative formats accepted", {
  expect_equal(ip_network("2001:0db8:85a3:0000:0000:8a2e:0370:7334/128"), ip_network("2001:db8:85a3::8a2e:370:7334/128"))
  expect_equal(ip_network("2001:db8:85a3:0:0:8a2e:370:7334/128"), ip_network("2001:db8:85a3::8a2e:370:7334/128"))
  expect_equal(ip_network("2001:db8:85a3::8a2e:3.112.115.52/128"), ip_network("2001:db8:85a3::8a2e:370:7334/128"))
})

test_that("construction works", {
  expect_s3_class(ip_network(), c("ip_network", "vctrs_vctr"))
  expect_true(is_ip_network(ip_network(x)))
  expect_length(ip_network(), 0)
  expect_length(ip_network(x), length(x))
  expect_equal(as.character(ip_network(x)), x)

  expect_equal(
    ip_network(x),
    ip_network(ip_address(c("::", "256::", "2001:db8::", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")), c(128L, 72L, 36L, 128L))
  )
})

test_that("formats correctly", {
  expect_equal(format(ip_network(x)), x)
  expect_equal(format(ip_network("2001:0db8:85a3:0000:0000:8a2e:0370:7334/128")), "2001:db8:85a3::8a2e:370:7334/128")
  expect_equal(format(ip_network("2001:db8:85a3::8a2e:370:7334/128"), exploded = TRUE), "2001:0db8:85a3:0000:0000:8a2e:0370:7334/128")
})

test_that("invalid inputs are caught", {
  expect_warning(ip_network("1::2"))
  expect_warning(ip_address("1::g/24"))
  expect_warning(ip_network("1::-2/24"))
  expect_warning(ip_network("1:2/24"))
  expect_warning(ip_network("1::2::3/24"))
  expect_warning(ip_network("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff/24"))
  expect_warning(ip_network("1::2/-1"))
  expect_warning(ip_network("1::2/129"))
  expect_warning(ip_network("1::2/a"))
  expect_warning(ip_network("1::2/24/24"))

  expect_error(ip_network(ip_address("2001:db8::"), 24.5), "`prefix_length` must be an integer vector")
  expect_warning(ip_network(ip_address("2001:db8::"), -1L))
  expect_warning(ip_network(ip_address("2001:db8::"), 129L))
})

test_that("strict argument works", {
  expect_error(ip_network("2001:db8::/36", strict = "yes"), "`strict` be must TRUE or FALSE")
  expect_error(ip_network("2001:db8::/36", strict = NA), "`strict` be must TRUE or FALSE")

  expect_warning(ip_network("2001:db8::8a2e:370:7334/36"), "host bits set")
  expect_equal(ip_network("2001:db8::8a2e:370:7334/36", strict = FALSE), ip_network("2001:db8::/36"))

  expect_warning(ip_network(ip_address("2001:db8::8a2e:370:7334"), 36L), "host bits set")
  expect_equal(ip_network(ip_address("2001:db8::8a2e:370:7334"), 36L, strict = FALSE), ip_network("2001:db8::/36"))
})

test_that("equality operations work", {
  expect_true(all(ip_network(x) == ip_network(x)))
  expect_false(any(ip_network(x) == ip_network(rev(x))))
  expect_false(ip_network("2001:db8::/36") == ip_network("2001:db8::/42"))
})

test_that("comparison operations work", {
  shifter <- function(x, n = 1L) {
    if (n == 0) x else c(tail(x, -n), head(x, n))
  }
  expect_equal(
    vec_compare(ip_network(x), ip_network(shifter(x, 1L))),
    c(rep(-1L, length(x) - 1L), 1L)
  )
  expect_equal(
    vec_compare(ip_network(x), ip_network(shifter(x, -1L))),
    c(-1L, rep(1L, length(x) - 1L))
  )
  expect_equal(vec_compare(ip_network("2001:db8::/36"), ip_network(NA)), NA_integer_)
})
