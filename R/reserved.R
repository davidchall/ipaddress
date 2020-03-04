#' Reserved addresses
#'
#' Check if an address or network is reserved for special use.
#'
#' @details
#' These special use addresses are documented in IETF documents
#' [RFC 5735](https://tools.ietf.org/html/rfc5735.html) (for IPv4) and
#' [RFC 4291](https://tools.ietf.org/html/rfc4291) (for IPv6).
#'
#' @param x An \code{\link{ip_address}} or \code{\link{ip_network}} vector
#' @return A logical vector
#'
#' @name is_reserved
NULL

#' @examples
#' is_multicast(ip_network(c("224.0.0.0/4", "ff00::/8")))
#'
#' @rdname is_reserved
#' @export
is_multicast <- function(x) {
  if (is_ip_address(x)) {
    is_multicast_address_wrapper(x)
  } else if (is_ip_network(x)) {
    is_multicast_network_wrapper(x)
  } else {
    stop("argument must be an ip_address vector or an ip_network vector")
  }
}

#' @examples
#' is_unspecified(ip_address(c("0.0.0.0", "::")))
#'
#' @rdname is_reserved
#' @export
is_unspecified <- function(x) {
  if (is_ip_address(x)) {
    is_unspecified_address_wrapper(x)
  } else if (is_ip_network(x)) {
    is_unspecified_network_wrapper(x)
  } else {
    stop("argument must be an ip_address vector or an ip_network vector")
  }
}

#' @examples
#' is_loopback(ip_network(c("127.0.0.0/8", "::1/128")))
#'
#' @rdname is_reserved
#' @export
is_loopback <- function(x) {
  if (is_ip_address(x)) {
    is_loopback_address_wrapper(x)
  } else if (is_ip_network(x)) {
    is_loopback_network_wrapper(x)
  } else {
    stop("argument must be an ip_address vector or an ip_network vector")
  }
}

#' @examples
#' is_link_local(ip_network(c("169.254.0.0/16", "fe80::/10")))
#'
#' @rdname is_reserved
#' @export
is_link_local <- function(x) {
  if (is_ip_address(x)) {
    is_link_local_address_wrapper(x)
  } else if (is_ip_network(x)) {
    is_link_local_network_wrapper(x)
  } else {
    stop("argument must be an ip_address vector or an ip_network vector")
  }
}
