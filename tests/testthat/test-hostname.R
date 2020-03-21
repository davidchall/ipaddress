test_that("DNS resolution works", {
  skip_if_offline()

  # expected type
  expect_s3_class(from_hostname("localhost", multiple = FALSE), "ip_address")
  expect_type(from_hostname("localhost", multiple = TRUE), "list")
  expect_type(as_hostname(ip_address("::1"), multiple = FALSE), "character")
  expect_type(as_hostname(ip_address("::1"), multiple = TRUE), "list")

  # expected size
  expect_length(from_hostname("localhost", multiple = FALSE), 1)
  expect_length(from_hostname("localhost", multiple = TRUE), 1)
  expect_length(from_hostname(c("localhost", "www.r-project.org"), multiple = FALSE), 2)
  expect_length(from_hostname(c("localhost", "www.r-project.org"), multiple = TRUE), 2)

  expect_length(as_hostname(ip_address("::1"), multiple = FALSE), 1)
  expect_length(as_hostname(ip_address("::1"), multiple = TRUE), 1)
  expect_length(as_hostname(ip_address(c("::1", "::2")), multiple = FALSE), 2)
  expect_length(as_hostname(ip_address(c("::1", "::2")), multiple = TRUE), 2)

  # input validation
  expect_warning(from_hostname("unknown"))

  # localhost is a reserved top-level domain (suitable for unit testing?)
  expect_true(is_loopback(from_hostname("localhost")))
  expect_equal(as_hostname(ip_address("127.0.0.1")), "localhost")
  expect_equal(as_hostname(ip_address("::1")), "localhost")
})

test_that("internal pluck_first_of_each() function works", {
  # works with character vectors
  expect_equal(
    pluck_first_of_each(list("a")),
    "a"
  )
  expect_equal(
    pluck_first_of_each(list(c("a", "b"))),
    "a"
  )
  expect_equal(
    pluck_first_of_each(list("a", "b")),
    c("a", "b")
  )
  expect_equal(
    pluck_first_of_each(list(c("a", "b"), "c")),
    c("a", "c")
  )

  # works with ip_address vectors
  expect_equal(
    pluck_first_of_each(list(ip_address("::a"))),
    ip_address("::a")
  )
  expect_equal(
    pluck_first_of_each(list(ip_address(c("::a", "::b")))),
    ip_address("::a")
  )
  expect_equal(
    pluck_first_of_each(list(ip_address("::a"), ip_address("::b"))),
    ip_address(c("::a", "::b"))
  )
  expect_equal(
    pluck_first_of_each(list(ip_address(c("::a", "::b")), ip_address("::c"))),
    ip_address(c("::a", "::c"))
  )
})
