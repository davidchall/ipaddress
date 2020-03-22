#' Reserved addresses
#'
#' Check if an address or network is reserved for special use.
#' A network is considered reserved if both the `network_address()`
#' and `broadcast_address()` are reserved.
#'
#' @details
#' These special use addresses are documented in IETF documents
#' [RFC 5735](https://tools.ietf.org/html/rfc5735.html) (for IPv4) and
#' [RFC 4291](https://tools.ietf.org/html/rfc4291) (for IPv6).
#'
#' @param x An \code{\link{ip_address}} or \code{\link{ip_network}} vector
#' @return A logical vector
#'
#' @examples
#' # these examples show the reserved networks
#'
#' is_multicast(ip_network(c("224.0.0.0/4", "ff00::/8")))
#'
#' is_unspecified(ip_network(c("0.0.0.0/32", "::/128")))
#'
#' is_loopback(ip_network(c("127.0.0.0/8", "::1/128")))
#'
#' is_link_local(ip_network(c("169.254.0.0/16", "fe80::/10")))
#' @seealso
#' Addresses reserved by IPv6 transition mechanisms can be identified
#' by functions described in \link{ipv6_transition}.
#' @name is_reserved
NULL

#' @rdname is_reserved
#' @export
is_multicast <- function(x) {
  assertthat::assert_that(is_ip_address(x) || is_ip_network(x))
  wrap_is_multicast(x)
}

#' @rdname is_reserved
#' @export
is_unspecified <- function(x) {
  assertthat::assert_that(is_ip_address(x) || is_ip_network(x))
  wrap_is_unspecified(x)
}

#' @rdname is_reserved
#' @export
is_loopback <- function(x) {
  assertthat::assert_that(is_ip_address(x) || is_ip_network(x))
  wrap_is_loopback(x)
}

#' @rdname is_reserved
#' @export
is_link_local <- function(x) {
  assertthat::assert_that(is_ip_address(x) || is_ip_network(x))
  wrap_is_link_local(x)
}
