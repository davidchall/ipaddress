test_that("pretty printing works", {
  x <- ip_interface(c(
    "29.71.126.113/6",
    NA,
    "::/0",
    "9401:b71a:4193:9b47:4d74:f55b:fdd9:b2ba/101",
    "2642:2f46:2d65:b800::/55"
  ))

  verify_output(test_path("test-pillar.txt"), {
    "# Without truncation"
    pillar::pillar_shaft(x)
    pillar::pillar_shaft(as_ip_network(x))
    pillar::pillar_shaft(as_ip_address(x))

    "# With truncation"
    print(pillar::pillar_shaft(x), width = 20)
    print(pillar::pillar_shaft(as_ip_network(x)), width = 20)
    print(pillar::pillar_shaft(as_ip_address(x)), width = 20)
  })

  expect_error(print(pillar::pillar_shaft(x), width = 5))
})
