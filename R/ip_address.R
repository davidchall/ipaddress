#' @importFrom methods setOldClass
methods::setOldClass(c("ip_address", "vctrs_vctr"))

#' Vector of IP addresses
#'
#' @details
#' An address in IPv4 space uses 32-bits. It is usually represented
#' as 4 groups of 8 bits, each shown as decimal digits (e.g. `192.168.0.1`).
#' This is known as dot-decimal notation.
#'
#' An address in IPv6 space uses 128-bits. It is usually represented
#' as 8 groups of 16 bits, each shown as hexadecimal digits
#' (e.g. `2001:0db8:85a3:0000:0000:8a2e:0370:7334`). This representation can
#' also be compressed by removing leading zeros and replacing consecutive
#' groups of zeros with double-colon (e.g. `2001:db8:85a3::8a2e:370:7334`).
#' Finally, there is also the dual representation. This expresses the final
#' two groups as an IPv4 address (e.g. `2001:db8:85a3::8a2e:3.112.115.52`).
#'
#' The `ip_address()` constructor accepts a character vector of IP addresses
#' in these two formats. It checks whether each string is a valid IPv4 or IPv6
#' address, and converts it to an `ip_address` object. If the input is invalid,
#' a warning is emitted and `NA` is stored instead.
#'
#' When casting an `ip_address` object back to a character vector using
#' `as.character()`, IPv6 addresses are reduced to their compressed representation.
#' A special case is IPv4-mapped IPv6 addresses, which are returned in their
#' dual representation (e.g. `::ffff:192.0.2.128`).
#'
#' Integers can be added to or subtracted from `ip_address` vectors.
#' This class also supports bitwise operations: `!` (NOT), `&` (AND),
#' `|` (OR) and `^` (XOR).
#'
#' @param x An `ip_address` vector
#' @param ... Arguments to be passed to other methods
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
#' @return An `ip_address` vector
#'
#' @examples
#' # supports IPv4 and IPv6 simultaneously
#' ip_address(c("0.0.0.1", "192.168.0.1", "2001:db8::8a2e:370:7334"))
#'
#' # validates inputs and replaces with NA
#' ip_address(c("1.2.3.4", "255.255.255.256", "1.2.3.4/5"))
#'
#' # addition
#' ip_address("192.168.0.1") + 12L
#'
#' # subtraction
#' ip_address("192.168.0.1") - 12L
#'
#' # bitwise NOT
#' !ip_address("192.168.0.1")
#'
#' # bitwise AND
#' ip_address("192.168.0.1") & ip_address("255.0.0.255")
#'
#' # bitwise OR
#' ip_address("192.168.0.0") | ip_address("255.0.0.255")
#'
#' # bitwise XOR
#' ip_address("192.168.0.0") ^ ip_address("255.0.0.255")
#' @rdname ip_address
#' @export
ip_address <- function(ip = character()) {
  wrap_parse_address(ip)
}

#' Low-level constructor that accepts the underlying data types being stored
#' @noRd
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

#' `as_ip_address()`
#'
#' `as_ip_address()` casts an object to `ip_address`.
#'
#' @rdname ip_address
#' @export
as_ip_address <- function(x) vec_cast(x, ip_address())

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

#' @rdname ip_address
#' @export
as.character.ip_address <- function(x, ...) vec_cast(x, character())



# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_address <- function(x, ...) wrap_compare_address(x)


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_address <- function(x, ...) {
  "ip_addr"
}
