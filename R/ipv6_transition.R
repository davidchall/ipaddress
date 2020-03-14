#' IPv6 transition mechanisms
#'
#' There are multiple mechanisms designed to help with the transition
#' from IPv4 to IPv6. These functions make it possible to extract the
#' embedded IPv4 address from an IPv6 address.
#'
#' @details
#' The IPv6 transition mechanisms are described in the IETF memos:
#' * IPv4-mapped: [RFC 4291](https://tools.ietf.org/html/rfc4291)
#' * 6to4: [RFC 3056](https://tools.ietf.org/html/rfc3056.html)
#' * Teredo: [RFC 4380](https://tools.ietf.org/html/rfc4380)
#'
#' @param x An \code{\link{ip_address}} vector
#' @return The `is_xxx()` functions return a logical vector and the
#'   `extract_xxx()` functions return an \code{\link{ip_address}} vector.
#'
#' @examples
#' is_ipv4_mapped(ip_network("::ffff:0.0.0.0/96"))
#'
#' extract_ipv4_mapped(ip_address("::ffff:192.0.2.128"))
#'
#' is_6to4(ip_network("2002::/16"))
#'
#' extract_6to4(ip_address("2002:c000:0204::"))
#'
#' is_teredo(ip_network("2001::/32"))
#'
#' extract_teredo_server(ip_address("2001:0000:4136:e378:8000:63bf:3fff:fdd2"))
#'
#' extract_teredo_client(ip_address("2001:0000:4136:e378:8000:63bf:3fff:fdd2"))
#' @name ipv6_transition
NULL

#' @rdname ipv6_transition
#' @export
is_ipv4_mapped <- function(x) {
  if (is_ip_address(x)) {
    is_ipv4_mapped_address_wrapper(x)
  } else if (is_ip_network(x)) {
    is_ipv4_mapped_network_wrapper(x)
  } else {
    stop("argument must be an ip_address vector or an ip_network vector")
  }
}

#' @rdname ipv6_transition
#' @export
extract_ipv4_mapped <- function(x) {
  assertthat::assert_that(is_ip_address(x))

  new_ip_address_encode(extract_ipv4_mapped_wrapper(x))
}

#' @rdname ipv6_transition
#' @export
is_6to4 <- function(x) {
  if (is_ip_address(x)) {
    is_6to4_address_wrapper(x)
  } else if (is_ip_network(x)) {
    is_6to4_network_wrapper(x)
  } else {
    stop("argument must be an ip_address vector or an ip_network vector")
  }
}

#' @rdname ipv6_transition
#' @export
extract_6to4 <- function(x) {
  assertthat::assert_that(is_ip_address(x))

  new_ip_address_encode(extract_6to4_wrapper(x))
}

#' @rdname ipv6_transition
#' @export
is_teredo <- function(x) {
  if (is_ip_address(x)) {
    is_teredo_address_wrapper(x)
  } else if (is_ip_network(x)) {
    is_teredo_network_wrapper(x)
  } else {
    stop("argument must be an ip_address vector or an ip_network vector")
  }
}

#' @rdname ipv6_transition
#' @export
extract_teredo_server <- function(x) {
  assertthat::assert_that(is_ip_address(x))

  new_ip_address_encode(extract_teredo_server_wrapper(x))
}

#' @rdname ipv6_transition
#' @export
extract_teredo_client <- function(x) {
  assertthat::assert_that(is_ip_address(x))

  new_ip_address_encode(extract_teredo_client_wrapper(x))
}
