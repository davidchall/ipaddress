#' IP network masking
#'
#' These functions yield different representations of the IP network mask.
#'
#' @param x An `ip_network` vector
#' @return An `ip_address` vector corresponding to the netmask
#'
#' @examples
#' ip <- ip_network(c("192.168.1.0/22", "2001:db00::0/26"))
#' prefix_length(ip)
#' netmask(ip)
#' hostmask(ip)
#'
#' @name netmask
NULL

#' @rdname netmask
#' @export
prefix_length <- function(x) {
  assertthat::assert_that(is_ip_network(x))
  field(x, "prefix")
}

#' @rdname netmask
#' @export
netmask <- function(x) {
  assertthat::assert_that(is_ip_network(x))
  y <- netmask_wrapper(x)
  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}

#' @rdname netmask
#' @export
hostmask <- function(x) {
  assertthat::assert_that(is_ip_network(x))
  y <- hostmask_wrapper(x)
  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}
