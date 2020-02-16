#' Netmask and hostmask
#'
#' @param x An `ip_network` vector
#' @return An `ip_address` vector corresponding to the netmask
#'
#' @name netmask
NULL

#' `netmask()`
#'
#' `netmask()` extracts the netmask from an IP network
#'
#' @examples
#' netmask(ip_network(c("192.168.1.0/24", "2001:db00::0/24")))
#'
#' @rdname netmask
#' @export
netmask <- function(x) {
  y <- netmask_wrapper(x)
  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}

#' `hostmask()`
#'
#' `hostmask()` extracts the hostmask from an IP network
#'
#' @examples
#' hostmask(ip_network(c("192.168.1.0/24", "2001:db00::0/24")))
#'
#' @rdname netmask
#' @export
hostmask <- function(x) {
  y <- hostmask_wrapper(x)
  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}
