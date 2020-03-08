#' Mapping between address spaces
#'
#' @details
#' Addresses already in the target address space are unaffected by
#' these functions.
#'
#' @param x An \code{\link{ip_address}} vector
#' @param keep_ipv6 A logical indicating whether IPv6 addresses that are
#'   not IPv4-mapped should be kept or converted to `NA`. If `FALSE`
#'   (the default), the returned vector will only contain IPv4 addresses.
#' @return An \code{\link{ip_address}}
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "::ffff:192.0.2.128", "2001:db8::"))
#'
#' ipv4_mapped(x)
#'
#' ipv6_mapped(x)
#'
#' # keep_ipv6 option prevents lossy mappings
#' ipv6_mapped(ipv4_mapped(x, keep_ipv6 = TRUE))
#' @seealso [is_ipv4_mapped()]
#' @name mapping
NULL

#' `ipv4_mapped()`
#'
#' `ipv4_mapped()` extracts an IPv4 address from an IPv4-mapped IPv6 address
#' @rdname mapping
#' @export
ipv4_mapped <- function(x, keep_ipv6 = FALSE) {
  assertthat::assert_that(
    is_ip_address(x),
    assertthat::is.flag(keep_ipv6),
    assertthat::noNA(keep_ipv6)
  )

  new_ip_address_encode(map_to_ipv4_wrapper(x, keep_ipv6))
}

#' `ipv6_mapped()`
#'
#' `ipv6_mapped()` embeds an IPv4 address within an IPv4-mapped IPv6 address
#' @rdname mapping
#' @export
ipv6_mapped <- function(x) {
  assertthat::assert_that(is_ip_address(x))

  new_ip_address_encode(map_to_ipv6_wrapper(x))
}
