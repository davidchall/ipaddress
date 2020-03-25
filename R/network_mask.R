#' Network mask
#'
#' These functions yield equivalent representations of the network mask.
#'
#' @param x An [`ip_network`] or [`ip_interface`] vector
#' @param prefix_length An integer vector
#' @param is_ipv6 A logical vector
#' @param ... Arguments to be passed to other methods
#' @return
#' * `prefix_length()` returns an integer vector
#' * `netmask()` and `hostmask()` return an [`ip_address`] vector
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
  if (!(is_ip_network(x) || is_ip_interface(x))) {
    abort("'x' must be an ip_network or ip_interface vector")
  }

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
  wrap_netmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @rdname netmask
#' @export
hostmask.ip_network <- function(x, ...) {
  wrap_hostmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @rdname netmask
#' @export
netmask.ip_interface <- function(x, ...) {
  wrap_netmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @rdname netmask
#' @export
hostmask.ip_interface <- function(x, ...) {
  wrap_hostmask(
    field(x, "prefix"),
    field(x, "is_ipv6")
  )
}

#' @rdname netmask
#' @export
netmask.default <- function(prefix_length = integer(), is_ipv6 = logical(), ...) {
  subnet_mask(prefix_length, is_ipv6, wrap_netmask)
}

#' @rdname netmask
#' @export
hostmask.default <- function(prefix_length = integer(), is_ipv6 = logical(), ...) {
  subnet_mask(prefix_length, is_ipv6, wrap_hostmask)
}

subnet_mask <- function(prefix_length, is_ipv6, mask_func) {
  if (!is_integer(prefix_length)) {
    abort("'prefix_length' must be an integer vector")
  }
  if (!is_logical(is_ipv6)) {
    abort("'is_ipv6' must be a logical vector")
  }

  # vector recycling
  args <- vec_recycle_common(prefix_length, is_ipv6)
  prefix_length <- args[[1L]]
  is_ipv6 <- args[[2L]]

  if (any(prefix_length < 0L, na.rm = TRUE)) {
    abort("'prefix_length' cannot be negative")
  }
  if (any(prefix_length[!is_ipv6] > 32L, na.rm = TRUE)) {
    abort("The maximum 'prefix_length' is 32 for IPv4")
  }
  if (any(prefix_length[is_ipv6] > 128L, na.rm = TRUE)) {
    abort("The maximum 'prefix_length' is 128 for IPv6")
  }

  do.call(mask_func, list(prefix_length, is_ipv6))
}
