#' Network size
#'
#' `network_address()` and `broadcast_address()` yield the first and last
#' addresses of the network; `num_addresses()` gives the total number of
#' addresses in the network.
#'
#' @param x An [`ip_network`] vector
#' @return
#' * `network_address()` and `broadcast_address()` return an
#'   [`ip_address`] vector
#' * `num_addresses()` returns a numeric vector
#'
#' @examples
#' x <- ip_network(c("192.168.0.0/22", "2001:db8::/33"))
#'
#' network_address(x)
#'
#' broadcast_address(x)
#'
#' num_addresses(x)
#' @seealso
#' Use [seq.ip_network()] to generate all addresses in a network.
#' @name network_size
NULL

#' @rdname network_size
#' @export
network_address <- function(x) {
  if (!is_ip_network(x)) {
    abort("`x` must be an ip_network vector")
  }

  new_ip_address(
    field(x, "address1"),
    field(x, "address2"),
    field(x, "address3"),
    field(x, "address4"),
    field(x, "is_ipv6")
  )
}

#' @details
#' The broadcast address is a special address at which any host connected
#' to the network can receive messages. That is, packets sent to this address
#' are received by all hosts on the network.
#' In IPv4, the last address of a network is the broadcast address.
#' Although IPv6 does not follow this approach to broadcast addresses, the
#' `broadcast_address()` function still returns the last address of the network.
#'
#' @rdname network_size
#' @export
broadcast_address <- function(x) {
  if (!is_ip_network(x)) {
    abort("`x` must be an ip_network vector")
  }

  wrap_broadcast_address(x)
}

#' @rdname network_size
#' @export
num_addresses <- function(x) {
  if (!is_ip_network(x)) {
    abort("`x` must be an ip_network vector")
  }

  2L^(max_prefix_length(x) - prefix_length(x))
}
