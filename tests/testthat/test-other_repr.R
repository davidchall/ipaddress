x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))

test_that("integer encoding/decoding works", {
  expect_error(ip_to_integer("hello"), "`x` must be an ip_address vector")
  expect_error(integer_to_ip(1.5), "`x` must be a character vector")
  expect_error(integer_to_ip(x), "`x` must be a character vector")
  expect_error(integer_to_ip("1", is_ipv6 = "true"), "`is_ipv6` must be a logical vector or NULL")

  expect_type(ip_to_integer(x), "character")
  expect_s3_class(integer_to_ip("1"), "ip_address")

  expect_equal(
    ip_to_integer(x),
    c("3232235521", "42540766411282592856904136881884656436", NA)
  )
  expect_equal(
    ip_to_integer(x, base = "hex"),
    c("0xC0A80001", "0x20010DB80000000000008A2E03707334", NA)
  )
  expect_equal(ip_to_integer(x, base = "bin"), ip_to_binary(x))

  # zero padding
  expect_equal(ip_to_integer(ip_address("0.0.0.0"), base = "hex"), paste0("0x", strrep("0", 8)))
  expect_equal(ip_to_integer(ip_address("::"), base = "hex"), paste0("0x", strrep("0", 32)))

  expect_equal(integer_to_ip("1", is_ipv6 = NULL), ip_address("0.0.0.1"))
  expect_equal(integer_to_ip("1", is_ipv6 = c(FALSE, TRUE)), ip_address(c("0.0.0.1", "::1")))
  expect_equal(integer_to_ip(ip_to_integer(x)), x)
  expect_equal(integer_to_ip(c(0, 3232235521, 4294967295)), ip_address(c("0.0.0.0", "192.168.0.1", "255.255.255.255")))

  expect_warning(integer_to_ip("hello"))
  expect_warning(integer_to_ip("-1"))
  expect_warning(integer_to_ip(as.character(2^32), is_ipv6 = FALSE))
  expect_warning(integer_to_ip("-1", is_ipv6 = TRUE))
})

test_that("bytes encoding/decoding works", {
  expect_error(ip_to_bytes("hello"), "`x` must be an ip_address vector")
  expect_error(bytes_to_ip("hello"), "`x` must be a blob object")
  expect_error(bytes_to_ip(x), "`x` must be a blob object")

  expect_s3_class(ip_to_bytes(x), c("blob", "vctrs_vctr"))
  expect_equal(
    ip_to_bytes(x),
    blob::blob(
      as.raw(c(0xc0, 0xa8, 0x00, 0x01)),
      as.raw(c(0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34)),
      NULL
    )
  )
  expect_equal(bytes_to_ip(ip_to_bytes(x)), x)

  expect_warning(bytes_to_ip(blob::blob(as.raw(10))), "unable to decode")
})

test_that("binary encoding/decoding works", {
  expect_error(ip_to_binary("hello"), "`x` must be an ip_address vector")
  expect_error(binary_to_ip(x), "`x` must be a character vector")

  expect_type(ip_to_binary(x), "character")
  expect_equal(ip_to_binary(x), c(
    "11000000101010000000000000000001",
    "00100000000000010000110110111000000000000000000000000000000000000000000000000000100010100010111000000011011100000111001100110100",
    NA_character_
  ))
  expect_equal(binary_to_ip(ip_to_binary(x)), x)

  # zero padding
  expect_equal(ip_to_binary(ip_address("0.0.0.0")), strrep("0", 32))
  expect_equal(ip_to_binary(ip_address("::")), strrep("0", 128))

  expect_warning(binary_to_ip(strrep("a", 32)), "contains non-binary characters")
  expect_warning(binary_to_ip("11000000"), "incorrect number of bits")
  expect_warning(binary_to_ip("110000001010100000000000000000010"), "incorrect number of bits")
})

test_that("hostname encoding/decoding works", {
  expect_error(ip_to_hostname(ip_network("192.168.0.0/24")), "`x` must be an ip_address vector")
  expect_error(ip_to_hostname("127.0.0.1"), "`x` must be an ip_address vector")
  expect_error(ip_to_hostname(ip_address("127.0.0.1"), multiple = "yes"), "`multiple` must be TRUE or FALSE")
  expect_error(ip_to_hostname(ip_address("127.0.0.1"), multiple = NA), "`multiple` must be TRUE or FALSE")

  expect_error(hostname_to_ip(123), "`x` must be a character vector")
  expect_error(hostname_to_ip(ip_address("127.0.0.1")), "`x` must be a character vector")
  expect_error(hostname_to_ip("localhost", multiple = "yes"), "`multiple` must be TRUE or FALSE")
  expect_error(hostname_to_ip("localhost", multiple = NA), "`multiple` must be TRUE or FALSE")

  skip_if_offline()

  expect_s3_class(hostname_to_ip("localhost", multiple = FALSE), "ip_address")
  expect_type(hostname_to_ip("localhost", multiple = TRUE), "list")
  expect_type(ip_to_hostname(ip_address("::1"), multiple = FALSE), "character")
  expect_type(ip_to_hostname(ip_address("::1"), multiple = TRUE), "list")

  expect_length(hostname_to_ip("localhost", multiple = FALSE), 1)
  expect_length(hostname_to_ip("localhost", multiple = TRUE), 1)
  expect_length(hostname_to_ip(c("localhost", "www.r-project.org"), multiple = FALSE), 2)
  expect_length(hostname_to_ip(c("localhost", "www.r-project.org"), multiple = TRUE), 2)

  expect_length(ip_to_hostname(ip_address("::1"), multiple = FALSE), 1)
  expect_length(ip_to_hostname(ip_address("::1"), multiple = TRUE), 1)
  expect_length(ip_to_hostname(ip_address(c("::1", "::2")), multiple = FALSE), 2)
  expect_length(ip_to_hostname(ip_address(c("::1", "::2")), multiple = TRUE), 2)

  expect_equal(hostname_to_ip("unknown"), ip_address(NA))
  expect_equal(ip_to_hostname(ip_address("0.0.0.0")), NA_character_)

  # localhost is a reserved top-level domain (suitable for unit testing?)
  expect_true(is_loopback(hostname_to_ip("localhost")))
  expect_match(ip_to_hostname(ip_address("127.0.0.1")), "localhost")
  expect_match(ip_to_hostname(ip_address("::1")), "localhost")

  # missing values
  expect_equal(hostname_to_ip(NA_character_), ip_address(NA))
  expect_equal(ip_to_hostname(ip_address(NA), multiple = FALSE), NA_character_)
  expect_equal(ip_to_hostname(ip_address(NA), multiple = TRUE), list(NA_character_))
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

test_that("reverse pointer works", {
  expect_equal(reverse_pointer(ip_address("127.0.0.1")), "1.0.0.127.in-addr.arpa")
  expect_equal(
    reverse_pointer(ip_address("2001:db8::1")),
    "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.8.b.d.0.1.0.0.2.ip.arpa"
  )

  expect_error(reverse_pointer(ip_network()), "`x` must be an ip_address vector")
  expect_equal(reverse_pointer(ip_address(NA)), NA_character_)
})
