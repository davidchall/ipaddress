#' Expectation: does the function identify the reserved address range?
#'
#' This tests the addresses either side of the reserved network boundaries.
#'
#' @param reserved_func The function under test. This should return `TRUE` when
#'   an [`ip_address`] is within the reserved network.
#' @param network The reserved network
#' @param ignore_before Do not check if address before network is unreserved.
#'   Used when reserved blocks are contiguous.
#' @param ignore_after Do not check if address after network is unreserved.
#'   Used when reserved blocks are contiguous.
#' @noRd
expect_reserved_address_range <- function(reserved_func, network,
                                          ignore_before = FALSE, ignore_after = FALSE) {
  act <- testthat::quasi_label(enquo(reserved_func), arg = "reserved_func")

  block_start <- network_address(network)
  block_end <- broadcast_address(network)
  space_start <- ip_address(c("0.0.0.0", "::"))
  space_end <- ip_address(c("255.255.255.255", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))

  boundaries <- vec_c(
    if (!(ignore_before || any(block_start == space_start))) block_start - 1,
    block_start,
    block_end,
    if (!(ignore_after || any(block_end == space_end))) block_end + 1
  )

  expected <- c(
    if (!(ignore_before || any(block_start == space_start))) FALSE,
    TRUE,
    TRUE,
    if (!(ignore_after || any(block_end == space_end))) FALSE
  )

  testthat::expect(
    all(act$val(boundaries) == expected),
    sprintf("%s doesn't match address range '%s'", act$lab, as.character(network))
  )

  invisible(act$val)
}

#' Expectation: does the function identify the reserved network?
#'
#' This tests the subnets and supernet of the reserved network.
#'
#' @param reserved_func The function under test. This should return `TRUE` when
#'   an [`ip_network`] is within the reserved network.
#' @param network The reserved network
#' @param ignore_super Do not check if supernet is unreserved. Used when
#'   broadcast address of supernet is reserved.
#' @noRd
expect_reserved_network <- function(reserved_func, network,
                                    ignore_super = FALSE) {
  act <- testthat::quasi_label(enquo(reserved_func), arg = "reserved_func")

  other_networks <- vec_c(
    network,
    if (prefix_length(network) != max_prefix_length(network)) subnets(network),
    if (!(ignore_super || prefix_length(network) == 0)) supernet(network)
  )
  expected <- c(
    TRUE,
    if (prefix_length(network) != max_prefix_length(network)) c(TRUE, TRUE),
    if (!(ignore_super || prefix_length(network) == 0)) FALSE
  )

  testthat::expect(
    all(act$val(other_networks) == expected),
    sprintf("%s doesn't match network '%s'", act$lab, as.character(network))
  )

  invisible(act$val)
}

#' Expectation: does the function identify reserved addresses and networks?
#'
#' @param reserved_func The function under test. This should return `TRUE` when
#'   an [`ip_address`] or [`ip_network`] is within the reserved network.
#' @inheritParams expect_reserved_address_range
#' @inheritParams expect_reserved_network
#' @noRd
expect_reserved <- function(reserved_func, network, ignore_before = FALSE,
                            ignore_after = FALSE, ignore_super = FALSE) {
  func <- enquo(reserved_func)
  expect_reserved_address_range(!!func, network, ignore_before, ignore_after)
  expect_reserved_network(!!func, network, ignore_super)
}
