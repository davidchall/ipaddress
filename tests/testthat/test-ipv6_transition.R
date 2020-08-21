test_that("IPv4-mapped IPv6 addresses work", {
  expect_false(is_ipv4_mapped(ip_address("0.0.0.0")))
  expect_false(is_ipv4_mapped(ip_network("0.0.0.0/0")))
  expect_reserved(is_ipv4_mapped, ip_network("::ffff:0.0.0.0/96"))
  expect_equal(
    extract_ipv4_mapped(ip_address(c("192.168.0.1", "::ffff:192.0.2.128", "2001:db8::"))),
    ip_address(c(NA, "192.0.2.128", NA))
  )

  expect_equal(is_ipv4_mapped(ip_address()), logical())
  expect_equal(is_ipv4_mapped(ip_network()), logical())
  expect_equal(extract_ipv4_mapped(ip_address()), ip_address())

  expect_equal(is_ipv4_mapped(ip_address(NA)), NA)
  expect_equal(is_ipv4_mapped(ip_network(NA)), NA)
  expect_equal(extract_ipv4_mapped(ip_address(NA)), ip_address(NA))

  expect_error(is_ipv4_mapped("hello"), "`x` must be an ip_address or ip_network vector")
  expect_error(extract_ipv4_mapped("hello"), "`x` must be an ip_address vector")
  expect_error(extract_ipv4_mapped(ip_network()), "`x` must be an ip_address vector")
  expect_error(extract_ipv4_mapped(NA), "`x` must be an ip_address vector")
})

test_that("6to4 IPv6 addresses work", {
  expect_false(is_6to4(ip_address("0.0.0.0")))
  expect_false(is_6to4(ip_network("0.0.0.0/0")))
  expect_reserved(is_6to4, ip_network("2002::/16"))
  expect_equal(
    extract_6to4(ip_address(c("192.168.0.1", "2002:c000:0280::", "2001:db8::"))),
    ip_address(c(NA, "192.0.2.128", NA))
  )

  expect_equal(is_6to4(ip_address()), logical())
  expect_equal(is_6to4(ip_network()), logical())
  expect_equal(extract_6to4(ip_address()), ip_address())

  expect_equal(is_6to4(ip_address(NA)), NA)
  expect_equal(is_6to4(ip_network(NA)), NA)
  expect_equal(extract_6to4(ip_address(NA)), ip_address(NA))

  expect_error(is_6to4("hello"), "`x` must be an ip_address or ip_network vector")
  expect_error(extract_6to4("hello"), "`x` must be an ip_address vector")
  expect_error(extract_6to4(ip_network()), "`x` must be an ip_address vector")
  expect_error(extract_6to4(NA), "`x` must be an ip_address vector")
})

test_that("Teredo IPv6 addresses work", {
  expect_false(is_teredo(ip_address("0.0.0.0")))
  expect_false(is_teredo(ip_network("0.0.0.0/0")))
  expect_reserved(is_teredo, ip_network("2001::/32"))
  expect_equal(
    extract_teredo_server(ip_address(c("192.168.0.1", "2001:0000:4136:e378:8000:63bf:3fff:fdd2", "2001:db8::"))),
    ip_address(c(NA, "65.54.227.120", NA))
  )
  expect_equal(
    extract_teredo_client(ip_address(c("192.168.0.1", "2001:0000:4136:e378:8000:63bf:3fff:fdd2", "2001:db8::"))),
    ip_address(c(NA, "192.0.2.45", NA))
  )

  expect_equal(is_teredo(ip_address()), logical())
  expect_equal(is_teredo(ip_network()), logical())
  expect_equal(extract_teredo_server(ip_address()), ip_address())
  expect_equal(extract_teredo_client(ip_address()), ip_address())

  expect_equal(is_teredo(ip_address(NA)), NA)
  expect_equal(is_teredo(ip_network(NA)), NA)
  expect_equal(extract_teredo_server(ip_address(NA)), ip_address(NA))
  expect_equal(extract_teredo_client(ip_address(NA)), ip_address(NA))

  expect_error(is_teredo("hello"), "`x` must be an ip_address or ip_network vector")
  expect_error(extract_teredo_server("hello"), "`x` must be an ip_address vector")
  expect_error(extract_teredo_server(ip_network()), "`x` must be an ip_address vector")
  expect_error(extract_teredo_server(NA), "`x` must be an ip_address vector")
  expect_error(extract_teredo_client("hello"), "`x` must be an ip_address vector")
  expect_error(extract_teredo_client(ip_network()), "`x` must be an ip_address vector")
  expect_error(extract_teredo_client(NA), "`x` must be an ip_address vector")
})
