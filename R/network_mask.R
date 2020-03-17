#' Network mask
#'
#' These functions yield equivalent representations of the network mask.
#'
#' @param x An \code{\link{ip_network}} or \code{\link{ip_interface}} vector
#' @param prefix_length An integer vector
#' @param is_ipv6 A logical vector
#' @param ... Arguments to be passed to other methods
#' @return
#' * `prefix_length()` returns an integer vector
#' * `netmask()` and `hostmask()` return an \code{\link{ip_address}} vector
#'
#' @examples
#' x <- ip_network(c("192.168.0.0/22", "2001:db00::0/26"))
#'
#' prefix_length(x)
#'
#' netmask(x)
#'
#' hostmask(x)
#'
#' netmask(c(22L, 26L), c(FALSE, TRUE))
#'
#' hostmask(c(22L, 26L), c(FALSE, TRUE))
#' @seealso
#' [max_prefix_length()]
#' @name netmask
NULL

#' @rdname netmask
#' @export
prefix_length <- function(x) {
  assertthat::assert_that(is_ip_network(x) || is_ip_interface(x))
  field(x, "prefix")
}

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
netmask.ip_network <- function(x, ...) {
  new_ip_address_encode(netmask_wrapper(
    field(x, "prefix"),
    field(x, "is_ipv6")
  ))
}

#' @rdname netmask
#' @export
hostmask.ip_network <- function(x, ...) {
  new_ip_address_encode(hostmask_wrapper(
    field(x, "prefix"),
    field(x, "is_ipv6")
  ))
}

#' @rdname netmask
#' @export
netmask.ip_interface <- function(x, ...) {
  new_ip_address_encode(netmask_wrapper(
    field(x, "prefix"),
    field(x, "is_ipv6")
  ))
}

#' @rdname netmask
#' @export
hostmask.ip_interface <- function(x, ...) {
  new_ip_address_encode(hostmask_wrapper(
    field(x, "prefix"),
    field(x, "is_ipv6")
  ))
}

#' @rdname netmask
#' @export
netmask.default <- function(prefix_length = integer(), is_ipv6 = logical(), ...) {
  subnet_mask(prefix_length, is_ipv6, netmask_wrapper)
}

#' @rdname netmask
#' @export
hostmask.default <- function(prefix_length = integer(), is_ipv6 = logical(), ...) {
  subnet_mask(prefix_length, is_ipv6, hostmask_wrapper)
}

subnet_mask <- function(prefix_length, is_ipv6, mask_func) {
  assertthat::assert_that(
    is.integer(prefix_length),
    is.logical(is_ipv6)
  )

  # vector recycling
  args <- vec_recycle_common(prefix_length, is_ipv6)
  prefix_length <- args[[1L]]
  is_ipv6 <- args[[2L]]

  assertthat::assert_that(
    all(prefix_length >= 0L, na.rm = TRUE),
    msg = "Found prefix length below zero"
  )

  assertthat::assert_that(
    all(prefix_length[!is_ipv6] <= 32L, na.rm = TRUE),
    msg = "Found IPv4 prefix length greater than 32"
  )

  assertthat::assert_that(
    all(prefix_length[is_ipv6] <= 128L, na.rm = TRUE),
    msg = "Found IPv6 prefix length greater than 128"
  )

  x <- do.call(mask_func, list(prefix_length, is_ipv6))
  new_ip_address_encode(x)
}
