#' Extract netmask from IP network
#'
#' @param network An `ip_network` vector
#' @return An `ip_address` vector corresponding to the netmask
#'
#' @examples
#' netmask(ip_network(c("192.168.1.0/24", "2001:db00::0/24")))
#' @export
netmask <- function(network) {
  y <- netmask_wrapper(network)
  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}
