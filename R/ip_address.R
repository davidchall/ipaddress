#' @importFrom methods setOldClass
methods::setOldClass(c("ip_address", "vctrs_vctr"))

#' Class for storing IP addresses (IPv4 or IPv6)
#'
#' @details
#' Addresses in IPv4 space are 32-bits long. They are usually represented
#' as 4 groups of 8 bits, each shown as decimal digits (e.g. "192.168.0.1").
#' This is known as dot-decimal notation.
#'
#' Addresses in IPv6 space are 128-bits long. They are usually represented
#' as 8 groups of 16 bits, each shown as hexadecimal digits
#' (e.g. "2001:0db8:85a3:0000:0000:8a2e:0370:7334"). This representation can
#' also be compressed by removing leading zeros and replacing consecutive
#' groups of zeros with double-colon (e.g. "2001:db8:85a3::8a2e:370:7334").
#'
#' @param x Vector of IP addresses
#' @param ... Other parameters passed on
#'
#' @name ip_address
NULL

# Construction ------------------------------------------------------------

#' `ip_address()`
#'
#' `ip_address()` is a high-level constructor that accepts character vectors
#' representing the IP address in dotted-decimal notation.
#'
#' @rdname ip_address
#' @export
ip_address <- function(x = character()) {
  y <- address_aton(x)
  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}

# `new_ip_address()` is a low-level constructor that accepts the data type
# stored in the background, [integer].
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
is_ip_address <- function(x) {
  inherits(x, "ip_address")
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
vec_cast.character.ip_address <- function(x, to, ...) {
  address_ntoa(x)
}


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
vec_proxy_compare.ip_address <- function(x, ...) {
  left_mask <- bitwShiftL(1L, 16L) - 1L
  right_mask <- bitwXor(bitwNot(0L), left_mask)

  data.frame(
    right = bitwShiftR(bitwAnd(field(x, "address1"), right_mask), 16L),
    left = bitwAnd(field(x, "address1"), left_mask)
  )
}


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_address <- function(x, ...) {
  "ip_addr"
}

#' @export
vec_ptype_full.ip_address <- function(x, ...) {
  "ip_address"
}
