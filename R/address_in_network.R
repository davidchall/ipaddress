#' Are IP addresses within IP network(s)?
#'
#' @param address An `ip_address` vector
#' @param network An `ip_network` vector
#'
#' @examples
#' address <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", "1.2.3.4"))
#' network1 <- ip_network(c("192.168.0.0/16", "2001:db8::/36", "0.0.0.0/30"))
#' network2 <- ip_network(c("2001:db8::/36", "192.168.0.0/16", "0.0.0.0/30"))
#'
#' is_within(address, network1)
#' is_within(address, network2)
#'
#' is_within_any(address, network1)
#' is_within_any(address, network2)
#'
#' @name address_in_network
NULL

#' `is_within()`
#'
#' `is_within()` checks if an IP address is within a single IP network
#'
#' @rdname address_in_network
#' @export
is_within <- function(address, network) {
  assertthat::assert_that(is_ip_address(address))
  assertthat::assert_that(is_ip_network(network))
  assertthat::assert_that(length(address) == length(network))

  is_within_wrapper(address, network)
}

#' `is_within_any()`
#'
#' `is_within_any()` checks if an IP address is within a vector of IP networks
#'
#' @rdname address_in_network
#' @export
is_within_any <- function(address, network) {
  assertthat::assert_that(is_ip_address(address))
  assertthat::assert_that(is_ip_network(network))

  is_within_any_wrapper(address, network)
}
