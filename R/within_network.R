#' Are IP addresses within IP network(s)?
#'
#' @param address An `ip_address` vector
#' @param network An `ip_network` vector
#'
#' @name address_in_network
NULL

#' `is_within()`
#'
#' `is_within()` checks if an IP address is within a single IP network
#'
#' @examples
#' is_within(ip_address("192.0.2.6"), ip_network("192.0.2.0/28"))
#' is_within(ip_address("192.0.3.6"), ip_network("192.0.2.0/28"))
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
#' @examples
#' is_within_any(ip_address("192.0.3.6"), ip_network(c("192.0.2.0/28", "192.0.2.0/28")))
#'
#' @rdname address_in_network
#' @export
is_within_any <- function(address, network) {
  assertthat::assert_that(is_ip_address(address))
  assertthat::assert_that(is_ip_network(network))

  is_within_any_wrapper(address, network)
}


#' Are IP networks within other networks?
#'
#' @param network1 An `ip_network` vector
#' @param network2 An `ip_network` vector
#'
#' @examples
#' net1 <- ip_network("192.168.1.0/24")
#' net2 <- ip_network("192.168.1.128/30")
#'
#' is_subnet(net2, net1)
#' is_supernet(net1, net2)
#'
#' @name network_in_network
NULL

#' `is_subnet()`
#'
#' `is_subnet()` checks if `network1` is a subnet of `network2`?
#'
#' @rdname network_in_network
#' @export
is_subnet <- function(network1, network2) {
  assertthat::assert_that(is_ip_network(network1))
  assertthat::assert_that(is_ip_network(network2))
  assertthat::assert_that(length(network1) == length(network2))

  is_subnet_wrapper(network1, network2)
}

#' `is_supernet()`
#'
#' `is_supernet()` checks if `network1` is a supernet of `network2`?
#'
#' @rdname network_in_network
#' @export
is_supernet <- function(network1, network2) {
  assertthat::assert_that(is_ip_network(network1))
  assertthat::assert_that(is_ip_network(network2))
  assertthat::assert_that(length(network1) == length(network2))

  is_subnet_wrapper(network2, network1)
}
