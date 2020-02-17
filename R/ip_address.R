#' @importFrom methods setOldClass
methods::setOldClass(c("ip_address", "vctrs_vctr"))

#' Class for storing IP addresses
#'
#' @details
#' Addresses in IPv4 space use 32-bits. They are usually represented
#' as 4 groups of 8 bits, each shown as decimal digits (e.g. "192.168.0.1").
#' This is known as dot-decimal notation.
#'
#' Addresses in IPv6 space use 128-bits. They are usually represented
#' as 8 groups of 16 bits, each shown as hexadecimal digits
#' (e.g. "2001:0db8:85a3:0000:0000:8a2e:0370:7334"). This representation can
#' also be compressed by removing leading zeros and replacing consecutive
#' groups of zeros with double-colon (e.g. "2001:db8:85a3::8a2e:370:7334").
#'
#' @param x An object
#' @param ... Additional arguments to be passed to or from methods
#'
#' @name ip_address
NULL


# Construction ------------------------------------------------------------

#' `ip_address()`
#'
#' `ip_address()` constructs a vector of IP addresses.
#'
#' @param ip Character vector of IP addresses, in dot-decimal notation (IPv4)
#'   or hexadecimal notation (IPv6).
#'
#' @examples
#' # supports IPv4 and IPv6 simultaneously
#' ip_address(c("0.0.0.1", "192.168.0.1", "2001:db8::8a2e:370:7334"))
#'
#' # validates inputs and replaces with NA
#' ip_address(c("1.2.3.4", "255.255.255.256", "1.2.3.4/5"))
#'
#' @rdname ip_address
#' @export
ip_address <- function(ip = character()) {
  y <- parse_address_wrapper(ip)
  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}

# low-level constructor that accepts the underlying data types being stored
new_ip_address <- function(address1 = integer(), address2 = integer(), address3 = integer(), address4 = integer(), is_ipv6 = logical()) {
  vec_assert(address1, ptype = integer())
  vec_assert(address2, ptype = integer())
  vec_assert(address3, ptype = integer())
  vec_assert(address4, ptype = integer())
  vec_assert(is_ipv6, ptype = logical())

  new_rcrd(list(
    address1 = address1, address2 = address2, address3 = address3, address4 = address4,
    is_ipv6 = is_ipv6
  ), class = "ip_address")
}

#' `is_ip_address()`
#'
#' `is_ip_address()` checks if an object is of class `ip_address`.
#'
#' @rdname ip_address
#' @export
is_ip_address <- function(x) inherits(x, "ip_address")

assertthat::on_failure(is_ip_address) <- function(call, env) {
  paste0(deparse(call$x), " is not an ip_address vector")
}

#' @rdname ip_address
#' @export
format.ip_address <- function(x, ...) as.character(x)


# Casting ------------------------------------------------------------

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast ip_address
#' @export
#' @export vec_cast.ip_address
vec_cast.ip_address <- function(x, to, ...) UseMethod("vec_cast.ip_address")

#' @method vec_cast.ip_address default
#' @export
vec_cast.ip_address.default <- function(x, to, ...) vec_default_cast(x, to)

#' @method vec_cast.ip_address ip_address
#' @export
vec_cast.ip_address.ip_address <- function(x, to, ...) x

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast.ip_address character
#' @export
vec_cast.ip_address.character <- function(x, to, ...) ip_address(x)

#' @method vec_cast.character ip_address
#' @export
vec_cast.character.ip_address <- function(x, to, ...) print_address_wrapper(x)

#' @rdname ip_address
#' @export
as.character.ip_address <- function(x, ...) vec_cast(x, character())


# Coercion ------------------------------------------------------------

#' Coercion
#'
#' Double dispatch methods to support [vctrs::vec_ptype2()].
#' @inheritParams vctrs::vec_ptype2
#' @rdname vctrs-compat
#'
#' @method vec_ptype2 ip_address
#' @export
#' @export vec_ptype2.ip_address
vec_ptype2.ip_address <- function(x, y, ...) UseMethod("vec_ptype2.ip_address", y)

#' @method vec_ptype2.ip_address default
#' @export
vec_ptype2.ip_address.default <- function(x, y, ..., x_arg = "x", y_arg = "y") {
  vec_default_ptype2(x, y, x_arg = x_arg, y_arg = y_arg)
}

#' @method vec_ptype2.ip_address ip_address
#' @export
vec_ptype2.ip_address.ip_address <- function(x, y, ...) new_ip_address()

#' @method vec_ptype2.ip_address character
#' @export
vec_ptype2.ip_address.character <- function(x, y, ...) new_ip_address()

#' @method vec_ptype2.character ip_address
#' @export
vec_ptype2.character.ip_address <- function(x, y, ...) new_ip_address()


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_address <- function(x, ...) compare_address_wrapper(x)


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_address <- function(x, ...) {
  "ip_addr"
}
