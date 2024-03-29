test_that("download works", {
  skip_if_not_installed("tibble")
  skip_if(is_offline(), "offline")

  out <- country_networks(c("GB", "US"))
  expect_s3_class(out, "tbl_df")
  expect_equal(nrow(out), 2L)
  expect_equal(colnames(out), c("country", "networks"))
  expect_equal(out$country, c("GB", "US"))
  expect_s3_class(out$networks, class(list_of(ip_network())))
  expect_s3_class(out$networks[[1]], class(ip_network()))
})

test_that("download fails", {
  skip_if_not_installed("tibble")
  skip_if(is_offline(), "offline")

  # invalid country: single
  hide_length <- function(x) gsub("\\[[\\d,]+\\]", "[n]", x, perl = TRUE)
  expect_snapshot(country_networks(c("US", "AA")), transform = hide_length)

  # invalid country: all
  expect_snapshot(error = TRUE, country_networks("AA"))
})

test_that("input validation", {
  skip_if_not_installed("tibble")

  expect_snapshot(error = TRUE, {
    country_networks(1L)
    country_networks("hello")
    country_networks("A1")
    country_networks("US", FALSE)
    country_networks("US", collapse = "TRUE")
  })
})
