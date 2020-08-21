#' Version of the address space
#'
#' @param x An [`ip_address`] or [`ip_network`] vector
#' @return A logical vector
#'
#' @examples
#' ip <- ip_address(c("192.168.0.1", "2001:db8::7334"))
#'
#' is_ipv4(ip)
#'
#' is_ipv6(ip)
#' @seealso
#' [max_prefix_length()]
#' @name is_ipv6
NULL

#' @rdname is_ipv6
#' @export
is_ipv4 <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  # directly returning field enables assignment
  result <- !field(x, "is_ipv6")
  result
}

#' @rdname is_ipv6
#' @export
is_ipv6 <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  # directly returning field enables assignment
  result <- field(x, "is_ipv6")
  result
}

#' Size of the address space
#'
#' The total number of bits available in the address space. IPv4 uses
#' 32-bit addresses and IPv6 uses 128-bit addresses.
#'
#' @param x An [`ip_address`] or [`ip_network`] vector
#' @return An integer vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::7334"))
#'
#' max_prefix_length(x)
#' @seealso [is_ipv4()], [is_ipv6()], [prefix_length()]
#' @export
max_prefix_length <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  ifelse(is_ipv6(x), 128L, 32L)
}
