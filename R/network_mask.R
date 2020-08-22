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
#' @param x An [`ip_network`] or [`ip_interface`] vector
#' @param mask An [`ip_address`] vector of netmasks and/or hostmasks. Ambiguous
#'   cases (all zeros, all ones) are treated as netmasks.
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

#' @rdname netmask
#' @export
prefix_length <- function(...) {
  UseMethod("prefix_length")
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
prefix_length.ip_network <- function(x, ...) {
  # directly returning field enables assignment
  result <- field(x, "prefix")
  result
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
prefix_length.ip_interface <- function(x, ...) {
  # directly returning field enables assignment
  result <- field(x, "prefix")
  result
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
prefix_length.default <- function(mask, ...) {
  if (!is_ip_address(mask)) {
    abort("prefix_length() accepts an ip_address, ip_network or ip_interface vector")
  }

  wrap_prefix_from_mask(mask)
}

#' @rdname netmask
#' @export
netmask.default <- function(prefix_length, is_ipv6, ...) {
  subnet_mask(prefix_length, is_ipv6, wrap_netmask)
}

#' @rdname netmask
#' @export
hostmask.default <- function(prefix_length, is_ipv6, ...) {
  subnet_mask(prefix_length, is_ipv6, wrap_hostmask)
}

subnet_mask <- function(prefix_length, is_ipv6, mask_func) {
  if (!is_integerish(prefix_length)) {
    abort("`prefix_length` must be an integer vector")
  }
  if (!is_logical(is_ipv6)) {
    abort("`is_ipv6` must be a logical vector")
  }

  # vector recycling
  args <- vec_recycle_common(prefix_length, is_ipv6)
  prefix_length <- args[[1L]]
  is_ipv6 <- args[[2L]]

  if (any(prefix_length < 0L, na.rm = TRUE)) {
    abort("`prefix_length` cannot be negative")
  }
  if (any(prefix_length[!is_ipv6] > 32L, na.rm = TRUE)) {
    abort("`prefix_length` cannot be greater than 32 for IPv4")
  }
  if (any(prefix_length[is_ipv6] > 128L, na.rm = TRUE)) {
    abort("`prefix_length` cannot be greater than 128 for IPv6")
  }

  do.call(mask_func, list(prefix_length, is_ipv6))
}
