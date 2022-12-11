test_that("hostname encoding/decoding works", {
  expect_error(ip_to_hostname(ip_network("192.168.0.0/24")), "`x` must be an ip_address vector")
  expect_error(ip_to_hostname("127.0.0.1"), "`x` must be an ip_address vector")

  expect_error(hostname_to_ip(123), "`x` must be a character vector")
  expect_error(hostname_to_ip(ip_address("127.0.0.1")), "`x` must be a character vector")

  skip_if_offline()

  # missing values
  expect_equal(hostname_to_ip(NA_character_), ip_address(NA))
  expect_equal(hostname_to_ip_all(NA_character_), list_of(ip_address(NA)))
  expect_equal(ip_to_hostname(ip_address(NA)), NA_character_)
  expect_equal(ip_to_hostname_all(ip_address(NA)), list_of(NA_character_))

  expect_s3_class(hostname_to_ip("localhost"), "ip_address")
  expect_s3_class(hostname_to_ip_all("localhost"), "vctrs_list_of")
  expect_type(ip_to_hostname(ip_address("::1")), "character")
  expect_s3_class(ip_to_hostname_all(ip_address("::1")), "vctrs_list_of")

  expect_length(hostname_to_ip("localhost"), 1)
  expect_length(hostname_to_ip_all("localhost"), 1)
  expect_length(hostname_to_ip(c("localhost", "www.r-project.org")), 2)
  expect_length(hostname_to_ip_all(c("localhost", "www.r-project.org")), 2)

  expect_length(ip_to_hostname(ip_address("::1")), 1)
  expect_length(ip_to_hostname_all(ip_address("::1")), 1)
  expect_length(ip_to_hostname(ip_address(c("::1", "::2"))), 2)
  expect_length(ip_to_hostname_all(ip_address(c("::1", "::2"))), 2)

  skip_on_cran()

  expect_equal(hostname_to_ip("unknown"), ip_address(NA))
  expect_equal(ip_to_hostname(ip_address("0.0.0.0")), NA_character_)

  # localhost is a reserved top-level domain (suitable for unit testing?)
  expect_true(is_loopback(hostname_to_ip("localhost")))
  expect_match(ip_to_hostname(ip_address("127.0.0.1")), "localhost")
  expect_match(ip_to_hostname(ip_address("::1")), "localhost")
})

test_that("DNS resolution errors if offline", {
  local_mock("ipaddress:::is_offline" = function() TRUE)
  expect_error(ip_to_hostname(ip_address("127.0.0.1")), "DNS resolution requires an internet connection")
  expect_error(hostname_to_ip("localhost"), "DNS resolution requires an internet connection")
})

test_that("internal function pluck_first_of_each() works", {
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
