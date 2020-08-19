x <- c("::", "256::", "2001:db8::8a2e:370:7334", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff")

test_that("alternative formats accepted", {
  expect_equal(ip_address("2001:0db8:85a3:0000:0000:8a2e:0370:7334"), ip_address("2001:db8:85a3::8a2e:370:7334"))
  expect_equal(ip_address("2001:db8:85a3:0:0:8a2e:370:7334"), ip_address("2001:db8:85a3::8a2e:370:7334"))
  expect_equal(ip_address("2001:db8:85a3::8a2e:3.112.115.52"), ip_address("2001:db8:85a3::8a2e:370:7334"))
})

test_that("formats correctly", {
  expect_equal(format(ip_address(x)), x)
  expect_equal(format(ip_address("2001:0db8:85a3:0000:0000:8a2e:0370:7334")), "2001:db8:85a3::8a2e:370:7334")
  expect_equal(format(ip_address("2001:db8:85a3::8a2e:370:7334"), exploded = TRUE), "2001:0db8:85a3:0000:0000:8a2e:0370:7334")
})

test_that("invalid inputs are caught", {
  expect_warning(ip_address("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))
  expect_warning(ip_address("1::g"))
  expect_warning(ip_address("1::-2"))
  expect_warning(ip_address("1::2.5"))

  # Windows accepts IP addresses in alternative formats: https://superuser.com/a/486936
  skip_on_os("windows")
  expect_warning(ip_address("1:2"))
})

test_that("equality operations work", {
  expect_true(all(ip_address(x) == ip_address(x)))
  expect_false(any(ip_address(x) == ip_address(rev(x))))
})

test_that("comparison operations work", {
  shifter <- function(x, n = 1L) {
    if (n == 0) x else c(tail(x, -n), head(x, n))
  }
  expect_equal(
    vec_compare(ip_address(x), ip_address(shifter(x, 1L))),
    c(rep(-1L, length(x) - 1L), 1L)
  )
  expect_equal(
    vec_compare(ip_address(x), ip_address(shifter(x, -1L))),
    c(-1L, rep(1L, length(x) - 1L))
  )
  expect_equal(vec_compare(ip_address("2001:db8::8a2e:370:7334"), ip_address(NA)), NA_integer_)

  # not effected by machine byte-endianness
  expect_true(ip_address("256::") > ip_address("0:128::"))
})
