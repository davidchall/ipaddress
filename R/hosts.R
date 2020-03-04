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
#' @seealso
#' To get the IP address range of a network without generating all addresses,
#' use [network_address()] and [broadcast_address()].
#'
#' @name hosts
NULL

#' `seq()`
#'
#' `seq()` returns _all_ hosts
#'
#' @examples
#' seq(ip_network("192.0.2.0/30"))
#'
#' seq(ip_network("2001:db8::/126"))
#'
#' @rdname hosts
#' @export
seq.ip_network <- function(x, ...) {
  assertthat::assert_that(assertthat::is.scalar(x))
  assertthat::assert_that(
    all(field(x, "prefix") >= ifelse(field(x, "is_ipv6"), 128L, 32L) - 30L, na.rm = TRUE),
    msg = "Network too large"
  )

  y <- hosts_wrapper(x, FALSE)

  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}

#' `hosts()`
#'
#' `hosts()` returns only _usable_ hosts
#'
#' @examples
#' hosts(ip_network("192.0.2.0/30"))
#'
#' hosts(ip_network("2001:db8::/126"))
#'
#' @rdname hosts
#' @export
hosts <- function(x) {
  assertthat::assert_that(
    is_ip_network(x),
    assertthat::is.scalar(x)
  )
  assertthat::assert_that(
    all(field(x, "prefix") >= ifelse(field(x, "is_ipv6"), 128L, 32L) - 30L, na.rm = TRUE),
    msg = "Network too large"
  )

  y <- hosts_wrapper(x, TRUE)

  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}
