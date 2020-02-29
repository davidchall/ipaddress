#' IP network masking
#'
#' These functions yield different representations of the IP network mask.
#'
#' @param x An \code{\link{ip_network}} vector
#' @return An \code{\link{ip_address}} vector.
#'
#' @examples
#' x <- ip_network(c("192.168.0.0/22", "2001:db00::0/26"))
#'
#' netmask(x)
#'
#' hostmask(x)
#'
#' @seealso The netmask can equivalently be represented by the [prefix_length()].
#'
#' @name netmask
NULL

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
