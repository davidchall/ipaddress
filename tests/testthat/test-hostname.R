test_that("DNS resolution works", {
  skip_if_offline()
  # localhost is a reserved top-level domain (suitable for unit testing?)
  expect_true(is_loopback(from_hostname("localhost")))
  expect_equal(as_hostname(from_hostname("localhost")), "localhost")
})
