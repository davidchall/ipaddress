#' Network membership of IP addresses
#'
#' These functions check whether an IP address falls within the range
#' of an IP network.
#'
#' @param address An \code{\link{ip_address}} vector
#' @param network An \code{\link{ip_network}} vector
#' @return A logical vector
#'
#' @examples
#' is_within(ip_address("192.0.2.6"), ip_network("192.0.2.0/28"))
#'
#' is_within(ip_address("192.0.3.6"), ip_network("192.0.2.0/28"))
#'
#' is_within_any(ip_address("192.0.3.6"), ip_network(c("192.0.2.0/28", "192.0.3.0/28")))
#' @name address_in_network
NULL

#' `is_within()`
#'
#' `is_within()` performs a one-to-one matching between addresses and networks.
#' @rdname address_in_network
#' @export
is_within <- function(address, network) {
  assertthat::assert_that(
    is_ip_address(address),
    is_ip_network(network)
  )

  # vector recycling
  args <- vec_recycle_common(address, network)
  address <- args[[1L]]
  network <- args[[2L]]

  is_within_wrapper(address, network)
}

#' `is_within_any()`
#'
#' `is_within_any()` checks if each IP address falls within _any_ of the IP networks.
#' @rdname address_in_network
#' @export
is_within_any <- function(address, network) {
  assertthat::assert_that(
    is_ip_address(address),
    is_ip_network(network)
  )

  is_within_any_wrapper(address, network)
}


#' Network membership of other IP networks
#'
#' @description
#' `overlaps()` checks for any overlap between two networks.
#'
#' `is_subnet()` and `is_supernet()` check if one network is a true
#' subnet or supernet of another network.
#'
#' @param network An \code{\link{ip_network}} vector
#' @param other An \code{\link{ip_network}} vector
#' @return A logical vector
#'
#' @examples
#' net1 <- ip_network("192.168.1.128/30")
#' net2 <- ip_network("192.168.1.0/24")
#'
#' overlaps(net1, net2)
#'
#' is_subnet(net1, net2)
#'
#' is_supernet(net1, net2)
#' @seealso
#' Use [is_within()] to check if an \code{\link{ip_address}} is within
#' an \code{\link{ip_network}}.
#' @name network_in_network
NULL

#' @rdname network_in_network
#' @export
overlaps <- function(network, other) {
  assertthat::assert_that(
    is_ip_network(network),
    is_ip_network(other)
  )

  # vector recycling
  args <- vec_recycle_common(network, other)
  network <- args[[1L]]
  other <- args[[2L]]

  is_within_wrapper(network_address(network), other) | is_within_wrapper(network_address(other), network)
}

#' @rdname network_in_network
#' @export
is_subnet <- function(network, other) {
  assertthat::assert_that(
    is_ip_network(network),
    is_ip_network(other)
  )

  # vector recycling
  args <- vec_recycle_common(network, other)
  network <- args[[1L]]
  other <- args[[2L]]

  is_within_wrapper(network_address(network), other) & (prefix_length(network) >= prefix_length(other))
}

#' @rdname network_in_network
#' @export
is_supernet <- function(network, other) {
  assertthat::assert_that(
    is_ip_network(network),
    is_ip_network(other)
  )

  # vector recycling
  args <- vec_recycle_common(network, other)
  network <- args[[1L]]
  other <- args[[2L]]

  is_within_wrapper(network_address(other), network) & (prefix_length(other) >= prefix_length(network))
}
