#' IPv6 transition mechanisms
#'
#' There are multiple mechanisms designed to help with the transition
#' from IPv4 to IPv6, which usually involve embedding an IPv4 address
#' within an IPv6 address. These functions make it possible to extract
#' the embedded IPv4 addresses.
#'
#' @details
#' Addresses already in the target address space are unaffected by
#' these functions.
#'
#' @param x An \code{\link{ip_address}} vector
#' @param keep_ipv6 A logical indicating whether IPv6 addresses that are
#'   not IPv4-mapped should be kept or converted to `NA`. If `FALSE`
#'   (the default), the returned vector will only contain IPv4 addresses.
#' @return An \code{\link{ip_address}} vector
#'
#' @examples
#' is_ipv4_mapped(ip_network("::ffff:0.0.0.0/96"))
#'
#' extract_ipv4_mapped(ip_address("::ffff:192.0.2.128"))
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
extract_ipv4_mapped <- function(x, keep_ipv6 = FALSE) {
  assertthat::assert_that(
    is_ip_address(x),
    assertthat::is.flag(keep_ipv6),
    assertthat::noNA(keep_ipv6)
  )

  new_ip_address_encode(extract_ipv4_mapped_wrapper(x, keep_ipv6))
}
