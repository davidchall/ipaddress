#' @importFrom methods setOldClass
methods::setOldClass(c("ip_interface", "vctrs_vctr"))

#' Vector of IP interfaces
#'
#' @param x An `ip_interface` vector
#' @param ... Arguments to be passed to other methods
#'
#' @seealso [ip_address()], [ip_network()]
#' @name ip_interface
NULL


# Construction ------------------------------------------------------------

#' `ip_interface()`
#'
#' `ip_interface()` constructs a vector of IP interfaces.
#'
#' @param ip Character vector of IP addresses, in dot-decimal notation (IPv4)
#'   or hexadecimal notation (IPv6).
#' @param address An \code{\link{ip_address}} vector
#' @param prefix_length An integer vector
#' @return An `ip_interface` vector
#'
#' @rdname ip_interface
#' @export
ip_interface <- function(...) {
  UseMethod("ip_interface")
}

#' @rdname ip_interface
#' @export
ip_interface.default <- function(ip = character(), ...) {
  new_ip_interface_encode(parse_interface_wrapper(ip))
}

#' @rdname ip_interface
#' @export
ip_interface.ip_address <- function(address, prefix_length, ...) {
  assertthat::assert_that(is.integer(prefix_length))

  # vector recycling
  args <- vec_recycle_common(address, prefix_length)
  address <- args[[1L]]
  prefix_length <- args[[2L]]

  new_ip_interface_encode(construct_interface_wrapper(address, prefix_length))
}

#' Low-level constructor that accepts the encoded data from C++
#' @noRd
new_ip_interface_encode <- function(x) {
  new_ip_interface(
    x$address1, x$address2, x$address3, x$address4,
    x$prefix,
    x$is_ipv6
  )
}

#' Low-level constructor that accepts the underlying data types being stored
#' @noRd
new_ip_interface <- function(address1 = integer(), address2 = integer(), address3 = integer(), address4 = integer(), prefix = integer(), is_ipv6 = logical()) {
  vec_assert(address1, ptype = integer())
  vec_assert(address2, ptype = integer())
  vec_assert(address3, ptype = integer())
  vec_assert(address4, ptype = integer())
  vec_assert(prefix, ptype = integer())
  vec_assert(is_ipv6, ptype = logical())

  new_rcrd(list(
    address1 = address1, address2 = address2, address3 = address3, address4 = address4,
    prefix = prefix,
    is_ipv6 = is_ipv6
  ), class = c("ip_interface", "ip_address"))
}

#' `as_ip_interface()`
#'
#' `as_ip_interface()` casts an object to `ip_interface`.
#'
#' @rdname ip_interface
#' @export
as_ip_interface <- function(x) vec_cast(x, ip_interface())

#' `is_ip_interface()`
#'
#' `is_ip_interface()` checks if an object is of class `ip_interface`.
#'
#' @rdname ip_interface
#' @export
is_ip_interface <- function(x) inherits(x, "ip_interface")

assertthat::on_failure(is_ip_interface) <- function(call, env) {
  paste0(deparse(call$x), " is not an ip_interface vector")
}

#' @rdname ip_interface
#' @export
format.ip_interface <- function(x, ...) as.character(x)

#' @rdname ip_interface
#' @export
as.character.ip_interface <- function(x, ...) vec_cast(x, character())


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_interface <- function(x, ...) {
  "ip_intf"
}
