#' List addresses within a network
#'
#' @param x An [`ip_network`] scalar
#' @param ... Included for generic consistency
#' @return An [`ip_address`] vector
#'
#' @details
#' In IPv4, the unusable hosts are the network address and the broadcast
#' address (i.e. the first and last addresses in the network).
#' In IPv6, the only unusable host is the subnet router anycast address
#' (i.e. the first address in the network).
#'
#' For networks with a prefix length of 31 (for IPv4) or 127 (for IPv6),
#' the unusable hosts are included in the results of `hosts()`.
#'
#' The ipaddress package does not support \link[base:LongVectors]{long vectors}
#' (i.e. vectors with more than 2^31 - 1 elements). As a result, these two
#' functions do not support networks larger than this size. This corresponds
#' to prefix lengths less than 2 (for IPv4) or 98 (for IPv6). However, you
#' might find that machine memory imposes stricter limitations.
#'
#' @examples
#' seq(ip_network("192.168.0.0/30"))
#'
#' seq(ip_network("2001:db8::/126"))
#'
#' hosts(ip_network("192.168.0.0/30"))
#'
#' hosts(ip_network("2001:db8::/126"))
#' @seealso
#' Use [network_address()] and [broadcast_address()] to get the first and last
#' address of a network.
#'
#' Use [sample_network()] to randomly sample addresses from a network.
#'
#' Use [subnets()] to list the subnetworks within a network.
#' @name sequence
NULL

#' `seq()`
#'
#' `seq()` returns _all_ hosts
#' @rdname sequence
#' @export
seq.ip_network <- function(x, ...) {
  if (length(x) != 1) {
    abort("`x` must be an ip_network scalar")
  }
  if (any(max_prefix_length(x) - prefix_length(x) > 30L, na.rm = TRUE)) {
    abort("Network too large")
  }

  wrap_network_hosts(x, FALSE)
}

#' `hosts()`
#'
#' `hosts()` returns only _usable_ hosts
#' @rdname sequence
#' @export
hosts <- function(x) {
  if (!(is_ip_network(x) && length(x) == 1)) {
    abort("`x` must be an ip_network scalar")
  }
  if (any(max_prefix_length(x) - prefix_length(x) > 30L, na.rm = TRUE)) {
    abort("Network too large")
  }

  wrap_network_hosts(x, TRUE)
}
