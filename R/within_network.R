#' Network membership of IP addresses
#'
#' These functions check whether an IP address falls within the range
#' of an IP network.
#'
#' @param address An \code{\link{ip_address}} vector
#' @param network An \code{\link{ip_network}} vector
#'
#' @name address_in_network
NULL

#' `is_within()`
#'
#' `is_within()` performs a one-to-one matching between addresses and networks.
#'
#' @examples
#' is_within(ip_address("192.0.2.6"), ip_network("192.0.2.0/28"))
#'
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
#' `is_within_any()` checks if each IP address falls within _any_ of the IP networks.
#'
#' @examples
#' is_within_any(ip_address("192.0.3.6"), ip_network(c("192.0.2.0/28", "192.0.3.0/28")))
#'
#' @rdname address_in_network
#' @export
is_within_any <- function(address, network) {
  assertthat::assert_that(is_ip_address(address))
  assertthat::assert_that(is_ip_network(network))

  is_within_any_wrapper(address, network)
}


#' Network membership of other IP networks
#'
#' These functions check if an IP network is a subnet or supernet
#' of another network.
#'
#' @param network1 An \code{\link{ip_network}} vector
#' @param network2 An \code{\link{ip_network}} vector
#'
#' @examples
#' net1 <- ip_network("192.168.1.0/24")
#' net2 <- ip_network("192.168.1.128/30")
#'
#' is_subnet(net2, net1)
#'
#' is_supernet(net1, net2)
#'
#' @name network_in_network
NULL

#' @rdname network_in_network
#' @export
is_subnet <- function(network1, network2) {
  assertthat::assert_that(is_ip_network(network1))
  assertthat::assert_that(is_ip_network(network2))
  assertthat::assert_that(length(network1) == length(network2))

  is_subnet_wrapper(network1, network2)
}

#' @rdname network_in_network
#' @export
is_supernet <- function(network1, network2) {
  assertthat::assert_that(is_ip_network(network1))
  assertthat::assert_that(is_ip_network(network2))
  assertthat::assert_that(length(network1) == length(network2))

  is_subnet_wrapper(network2, network1)
}
