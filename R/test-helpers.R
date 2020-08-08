expect_reserved_address_range <- function(reserved_func, network) {
  act <- quasi_label(enquo(reserved_func), arg = "reserved_func")

  block_start <- network_address(network)
  block_end <- broadcast_address(network)
  space_start <- ip_address(c("0.0.0.0", "::"))
  space_end <- ip_address(c("255.255.255.255", "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))

  boundaries <- vec_c(
    if (all(block_start != space_start)) block_start - 1,
    block_start,
    block_end,
    if (all(block_end != space_end)) block_end + 1
  )

  expected <- c(
    if (all(block_start != space_start)) FALSE,
    TRUE,
    TRUE,
    if (all(block_end != space_end)) FALSE
  )

  expect(
    all(act$val(boundaries) == expected),
    sprintf("%s doesn't match address range '%s'", act$lab, as.character(network))
  )

  invisible(act$val)
}

expect_reserved_network <- function(reserved_func, network) {
  act <- quasi_label(enquo(reserved_func), arg = "reserved_func")

  other_networks <- vec_c(
    network,
    if (prefix_length(network) != max_prefix_length(network)) subnets(network),
    if (prefix_length(network) != 0) supernet(network)
  )
  expected <- c(
    TRUE,
    if (prefix_length(network) != max_prefix_length(network)) c(TRUE, TRUE),
    if (prefix_length(network) != 0) FALSE
  )

  expect(
    all(act$val(other_networks) == expected),
    sprintf("%s doesn't match network '%s'", act$lab, as.character(network))
  )

  invisible(act$val)
}

expect_reserved <- function(reserved_func, network) {
  func <- enquo(reserved_func)
  expect_reserved_address_range(!!func, network)
  expect_reserved_network(!!func, network)
}
