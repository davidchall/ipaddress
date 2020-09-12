#' Vector of IP addresses
#'
#' @description
#' `ip_address()` constructs a vector of IP addresses.
#'
#' `is_ip_address()` checks if an object is of class `ip_address`.
#'
#' `as_ip_address()` casts an object to `ip_address`.
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
#' A special case is IPv4-mapped IPv6 addresses (see [is_ipv4_mapped()]), which
#' are returned in the dual representation (e.g. `::ffff:192.168.0.1`).
#'
#' `ip_address` vectors support a number of [operators][ip_operators].
#'
#' @param x
#' * For `ip_address()`: A character vector of IP addresses, in dot-decimal
#'   notation (IPv4) or hexadecimal notation (IPv6)
#' * For `is_ip_address()`: An object to test
#' * For `as_ip_address()`: An object to cast
#' * For `as.character()`: An `ip_address` vector
#' @param ... Included for S3 generic consistency
#' @return An S3 vector of class `ip_address`
#'
#' @examples
#' # supports IPv4 and IPv6 simultaneously
#' ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334"))
#'
#' # validates inputs and replaces with NA
#' ip_address(c("255.255.255.256", "192.168.0.1/32"))
#' @seealso
#' [`ip_operators`], `vignette("ipaddress-classes")`
#' @name ip_address
NULL


# Construction ------------------------------------------------------------

#' @rdname ip_address
#' @export
ip_address <- function(x = character()) {
  wrap_parse_address(x)
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

#' @rdname ip_address
#' @export
is_ip_address <- function(x) inherits(x, "ip_address")


# Casting ------------------------------------------------------------

#' @rdname ip_address
#' @export
as_ip_address <- function(x) UseMethod("as_ip_address")

#' @rdname ip_address
#' @export
as_ip_address.character <- function(x) ip_address(x)

#' @rdname ip_address
#' @export
as_ip_address.ip_interface <- function(x) {
  new_ip_address(
    field(x, "address1"),
    field(x, "address2"),
    field(x, "address3"),
    field(x, "address4"),
    field(x, "is_ipv6")
  )
}

#' @rdname ip_address
#' @export
as.character.ip_address <- function(x, ...) wrap_print_address(x)

#' @param exploded Logical scalar. Should IPv6 addresses display leading zeros?
#'   (default: `FALSE`)
#' @rdname ip_address
#' @export
format.ip_address <- function(x, exploded = FALSE, ...) {
  wrap_print_address(x, exploded)
}


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_address <- function(x, ...) wrap_compare_address(x)


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_address <- function(x, ...) {
  "ip_addr"
}
