#' Network membership of addresses
#'
#' These functions check whether an address falls within a network.
#'
#' @param address An [`ip_address`] vector
#' @param network An [`ip_network`] vector
#' @return A logical vector
#'
#' @examples
#' is_within(ip_address("192.168.2.6"), ip_network("192.168.2.0/28"))
#'
#' is_within(ip_address("192.168.3.6"), ip_network("192.168.2.0/28"))
#'
#' is_within_any(ip_address("192.168.3.6"), ip_network(c("192.168.2.0/28", "192.168.3.0/28")))
#' @seealso
#' Use [is_subnet()] to check if an [`ip_network`] is within another
#' [`ip_network`].
#' @name address_in_network
NULL

#' `is_within()`
#'
#' `is_within()` performs a one-to-one matching between addresses and networks.
#' @rdname address_in_network
#' @export
is_within <- function(address, network) {
  if (!is_ip_address(address)) {
    abort("`address` must be an ip_address vector")
  }
  if (!is_ip_network(network)) {
    abort("`network` must be an ip_network vector")
  }

  # vector recycling
  args <- vec_recycle_common(address, network)
  address <- args[[1L]]
  network <- args[[2L]]

  wrap_is_within(address, network)
}

#' `is_within_any()`
#'
#' `is_within_any()` checks if each address falls within _any_ of the networks.
#' @rdname address_in_network
#' @export
is_within_any <- function(address, network) {
  if (!is_ip_address(address)) {
    abort("`address` must be an ip_address vector")
  }
  if (!is_ip_network(network)) {
    abort("`network` must be an ip_network vector")
  }

  wrap_is_within_any(address, network)
}


#' Network membership of other networks
#'
#' `is_supernet()` and `is_subnet()` check if one network is a true supernet or
#' subnet of another network; `overlaps()` checks for any overlap between two
#' networks.
#'
#' @param network An [`ip_network`] vector
#' @param other An [`ip_network`] vector
#' @return A logical vector
#'
#' @examples
#' net1 <- ip_network("192.168.1.128/30")
#' net2 <- ip_network("192.168.1.0/24")
#'
#' is_supernet(net1, net2)
#'
#' is_subnet(net1, net2)
#'
#' overlaps(net1, net2)
#' @seealso
#' Use [is_within()] to check if an [`ip_address`] is within an [`ip_network`].
#'
#' Use [supernet()] and [subnets()] to traverse the network hierarchy.
#' @name network_in_network
NULL

#' @rdname network_in_network
#' @export
is_supernet <- function(network, other) {
  if (!is_ip_network(network)) {
    abort("`network` must be an ip_network vector")
  }
  if (!is_ip_network(other)) {
    abort("`other` must be an ip_network vector")
  }

  # vector recycling
  args <- vec_recycle_common(network, other)
  network <- args[[1L]]
  other <- args[[2L]]

  wrap_is_within(network_address(other), network) & (prefix_length(other) >= prefix_length(network))
}

#' @rdname network_in_network
#' @export
is_subnet <- function(network, other) {
  if (!is_ip_network(network)) {
    abort("`network` must be an ip_network vector")
  }
  if (!is_ip_network(other)) {
    abort("`other` must be an ip_network vector")
  }

  # vector recycling
  args <- vec_recycle_common(network, other)
  network <- args[[1L]]
  other <- args[[2L]]

  wrap_is_within(network_address(network), other) & (prefix_length(network) >= prefix_length(other))
}

#' @rdname network_in_network
#' @export
overlaps <- function(network, other) {
  if (!is_ip_network(network)) {
    abort("`network` must be an ip_network vector")
  }
  if (!is_ip_network(other)) {
    abort("`other` must be an ip_network vector")
  }

  # vector recycling
  args <- vec_recycle_common(network, other)
  network <- args[[1L]]
  other <- args[[2L]]

  wrap_is_within(network_address(network), other) | wrap_is_within(network_address(other), network)
}
