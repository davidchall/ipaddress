#' Subnet masking
#'
#' These functions yield different representations of the IP network mask.
#'
#' @param prefix_length An integer vector
#' @param is_ipv6 A logical vector
#' @param network An \code{\link{ip_network}} vector
#' @param ... Arguments to be passed to other methods
#' @return An \code{\link{ip_address}} vector
#'
#' @examples
#' x <- ip_network(c("192.168.0.0/22", "2001:db00::0/26"))
#'
#' netmask(x)
#'
#' hostmask(x)
#'
#' netmask(c(22L, 26L), c(FALSE, TRUE))
#'
#' hostmask(c(22L, 26L), c(FALSE, TRUE))
#' @seealso The netmask can equivalently be represented by the [prefix_length()].
#'
#' @name netmask
NULL

#' @rdname netmask
#' @export
netmask <- function(...) {
  UseMethod("netmask")
}

#' @rdname netmask
#' @export
hostmask <- function(...) {
  UseMethod("hostmask")
}

#' @rdname netmask
#' @export
netmask.ip_network <- function(network, ...) {
  new_ip_address_encode(netmask_wrapper(
    field(network, "prefix"),
    field(network, "is_ipv6")
  ))
}

#' @rdname netmask
#' @export
hostmask.ip_network <- function(network, ...) {
  new_ip_address_encode(hostmask_wrapper(
    field(network, "prefix"),
    field(network, "is_ipv6")
  ))
}

#' @rdname netmask
#' @export
netmask.default <- function(prefix_length = integer(), is_ipv6 = logical(), ...) {
  assertthat::assert_that(
    is.integer(prefix_length),
    is.logical(is_ipv6),
    length(is_ipv6) == length(prefix_length)
  )
  assertthat::assert_that(
    all(prefix_length >= 0L, na.rm = TRUE),
    all(prefix_length[!is_ipv6] <= 32L, na.rm = TRUE),
    all(prefix_length[is_ipv6] <= 128L, na.rm = TRUE),
    msg = "Found out-of-bounds prefix length"
  )

  new_ip_address_encode(netmask_wrapper(prefix_length, is_ipv6))
}

#' @rdname netmask
#' @export
hostmask.default <- function(prefix_length = integer(), is_ipv6 = logical(), ...) {
  assertthat::assert_that(
    is.integer(prefix_length),
    is.logical(is_ipv6),
    length(is_ipv6) == length(prefix_length)
  )
  assertthat::assert_that(
    all(prefix_length >= 0L, na.rm = TRUE),
    all(prefix_length[!is_ipv6] <= 32L, na.rm = TRUE),
    all(prefix_length[is_ipv6] <= 128L, na.rm = TRUE),
    msg = "Found out-of-bounds prefix length"
  )

  new_ip_address_encode(hostmask_wrapper(prefix_length, is_ipv6))
}
