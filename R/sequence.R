#' List addresses within a network
#'
#' @param x An \code{\link{ip_network}} scalar
#' @param ... Included for generic consistency
#' @return An \code{\link{ip_address}} vector
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
#' The `ipaddress` package does not support \link[base:LongVectors]{long vectors}
#' (i.e. vectors with more than 2^31 - 1 elements). As a result, these two
#' functions do not support networks larger than this size. This corresponds
#' to prefix lengths less than 2 (for IPv4) or 98 (for IPv6). However, you
#' might find that machine memory imposes stricter limitations.
#'
#' @examples
#' seq(ip_network("192.0.2.0/30"))
#'
#' seq(ip_network("2001:db8::/126"))
#'
#' hosts(ip_network("192.0.2.0/30"))
#'
#' hosts(ip_network("2001:db8::/126"))
#' @seealso
#' Use [network_address()] and [broadcast_address()] to get the IP address
#' range of a network without generating all addresses.
#'
#' Use [sample_network()] to randomly sample addresses.
#'
#' @name sequence
NULL

#' `seq()`
#'
#' `seq()` returns _all_ hosts
#' @rdname sequence
#' @export
seq.ip_network <- function(x, ...) {
  assertthat::assert_that(assertthat::is.scalar(x))
  assertthat::assert_that(
    all(field(x, "prefix") >= (max_prefix_length(x) - 30L), na.rm = TRUE),
    msg = "Network too large"
  )

  new_ip_address_encode(hosts_wrapper(x, FALSE))
}

#' `hosts()`
#'
#' `hosts()` returns only _usable_ hosts
#' @rdname sequence
#' @export
hosts <- function(x) {
  assertthat::assert_that(
    is_ip_network(x),
    assertthat::is.scalar(x)
  )
  assertthat::assert_that(
    all(field(x, "prefix") >= (max_prefix_length(x) - 30L), na.rm = TRUE),
    msg = "Network too large"
  )

  new_ip_address_encode(hosts_wrapper(x, TRUE))
}
