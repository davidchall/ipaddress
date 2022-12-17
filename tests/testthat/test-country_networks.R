test_that("input validation", {
  expect_snapshot(error = TRUE, {
    country_networks(1L)
    country_networks("hello")
    country_networks("A1")
  })
})
