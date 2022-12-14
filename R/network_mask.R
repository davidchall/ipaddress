#' Network mask
#'
#' @description
#' `prefix_length()`, `netmask()` and `hostmask()` extract different (but
#' equivalent) representations of the network mask. They accept an
#' [`ip_network`] or [`ip_interface`] vector.
#'
#' The functions can also convert between these alternative representations.
#' For example, `prefix_length()` can infer the prefix length from an
#' [`ip_address`] vector of netmasks and/or hostmasks, while `netmask()` and
#' `hostmask()` can accept a vector of prefix lengths.
#'
#' @param x
#'  * An [`ip_network`] vector.
#'  * An [`ip_interface`] vector.
#'  * `prefix_length()`: An [`ip_address`] vector of netmasks and/or hostmasks. Ambiguous cases
#'  (all zeros, all ones) are treated as netmasks.
#'  * `netmask()` and `hostmask()`: An integer vector of prefix lengths.
#' @param is_ipv6 A logical vector indicating whether to construct an IPv4 or
#'   IPv6 address. If `NULL` (the default), then IPv4 is preferred but an IPv6
#'   address is constructed when `x` is too large for the IPv4 address space.
#' @inheritParams rlang::args_dots_used
#'
#' @return
#' * `prefix_length()`: An integer vector
#' * `netmask()`: An [`ip_address`] vector
#' * `hostmask()`: An [`ip_address`] vector
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
#' # construct netmask/hostmask from prefix length
#' netmask(c(22L, 26L), c(FALSE, TRUE))
#'
#' hostmask(c(22L, 26L), c(FALSE, TRUE))
#'
#' # extract prefix length from netmask/hostmask
#' prefix_length(ip_address(c("255.255.255.0", "0.255.255.255")))
#'
#' # invalid netmask/hostmask raise a warning and return NA
#' prefix_length(ip_address("255.255.255.1"))
#' @seealso
#' [max_prefix_length()]
#' @name netmask
NULL


# prefix_length ----------------------------------------------------------------

#' @rdname netmask
#' @export
prefix_length <- function(x) {
  UseMethod("prefix_length")
}

#' @export
prefix_length.ip_network <- function(x) {
  # directly returning field enables assignment
  result <- field(x, "prefix")
  result
}

#' @export
prefix_length.ip_interface <- function(x) {
  # directly returning field enables assignment
  result <- field(x, "prefix")
  result
}

#' @export
prefix_length.ip_address <- function(x) {
  wrap_prefix_from_mask(x)
}

#' @export
prefix_length.default <- function(x) {
  cli::cli_abort("{.arg x} must be an {.cls ip_network}, {.cls ip_interface} or {.cls ip_address} vector")
}


# netmask ----------------------------------------------------------------------

#' @rdname netmask
#' @export
netmask <- function(x, ...) {
  check_dots_used()
  UseMethod("netmask")
}

#' @export
netmask.ip_network <- function(x, ...) {
  wrap_netmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @export
netmask.ip_interface <- function(x, ...) {
  wrap_netmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @rdname netmask
#' @export
netmask.numeric <- function(x, is_ipv6 = NULL, ...) {
  subnet_mask(x, is_ipv6, wrap_netmask)
}

#' @export
netmask.default <- function(x, ...) {
  cli::cli_abort("{.arg x} must be an {.cls ip_network}, {.cls ip_interface} or integer vector")
}


# hostmask ---------------------------------------------------------------------

#' @rdname netmask
#' @export
hostmask <- function(x, ...) {
  check_dots_used()
  UseMethod("hostmask")
}

#' @export
hostmask.ip_network <- function(x, ...) {
  wrap_hostmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @export
hostmask.ip_interface <- function(x, ...) {
  wrap_hostmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @rdname netmask
#' @export
hostmask.numeric <- function(x, is_ipv6 = NULL, ...) {
  subnet_mask(x, is_ipv6, wrap_hostmask)
}

#' @export
hostmask.default <- function(x, ...) {
  cli::cli_abort("{.arg x} must be an {.cls ip_network}, {.cls ip_interface} or integer vector")
}


# prefix to mask ---------------------------------------------------------------

subnet_mask <- function(prefix_length, is_ipv6, mask_func) {
  force(is_ipv6)
  check_integer(prefix_length)

  if (!(is_null(is_ipv6) || is_logical(is_ipv6))) {
    cli::cli_abort("{.arg is_ipv6} must be a logical vector or NULL")
  }

  if (is_null(is_ipv6)) {
    is_ipv6 <- prefix_length > 32L
  } else {
    args <- vec_recycle_common(prefix_length, is_ipv6)
    prefix_length <- args[[1L]]
    is_ipv6 <- args[[2L]]
  }

  check_all(prefix_length >=   0L,            "prefix_length", "must be positive")
  check_all(prefix_length <=  32L |  is_ipv6, "prefix_length", "must not be greater than 32 for IPv4")
  check_all(prefix_length <= 128L | !is_ipv6, "prefix_length", "must not be greater than 128 for IPv6")

  do.call(mask_func, list(prefix_length, is_ipv6))
}
