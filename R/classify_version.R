#' Classify version of IP address space
#'
#' @param x An `ip_address` or `ip_network` vector
#'
#' @examples
#' tibble(ip = ip_address(c("0.0.0.1", "192.168.0.1", "2001:db8::7334"))) %>%
#'   mutate(ipv4 = is_ipv4(ip), ipv6 = is_ipv6(ip))
#'
#' @name classify_version
NULL

#' `is_ipv4`
#'
#' `is_ipv4` identifies IPv4 addresses/networks
#'
#' @rdname classify_version
#' @export
is_ipv4 <- function(x) {
  !field(x, "is_ipv6")
}

#' `is_ipv6`
#'
#' `is_ipv6` identifies IPv6 addresses/networks
#'
#' @rdname classify_version
#' @export
is_ipv6 <- function(x) {
  field(x, "is_ipv6")
}
