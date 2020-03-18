#' Represent address as raw bytes
#'
#' `as_packed()` and `from_packed()` encode and decode an \code{\link{ip_address}}
#' vector to a \code{\link[blob]{blob}} vector.
#'
#' @details
#' The bytes are stored in network order (also known as
#' big-endian order), which is part of the IP standard.
#'
#' IPv4 addresses use 4 bytes, IPv6 addresses use 16 bytes,
#' and missing values are encoded as `NULL`.
#'
#' @param ip An \code{\link{ip_address}} vector
#' @param bytes A \code{\link[blob]{blob}} vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' as_packed(x)
#'
#' from_packed(as_packed(x))
#' @seealso Use `as_binary()` and `from_binary()` to encode/decode binary.
#' @name packed
NULL

#' @rdname packed
#' @export
as_packed <- function(ip) {
  assertthat::assert_that(is_ip_address(ip))
  blob::as_blob(ip)
}

#' @rdname packed
#' @export
from_packed <- function(bytes) {
  assertthat::assert_that(blob::is_blob(bytes), msg = "argument is not a blob object")
  vec_cast(bytes, ip_address())
}


#' Represent address as binary
#'
#' `as_binary()` and `from_binary()` encode and decode an \code{\link{ip_address}}
#' vector to a character vector of bits.
#'
#' @details
#' The bits are stored in network order (also known as big-endian order), which
#' is part of the IP standard.
#'
#' IPv4 addresses use 32 bits, IPv6 addresses use 128 bits, and missing values
#' are encoded as `NA`.
#'
#' @param ip An \code{\link{ip_address}} vector
#' @param bits A character vector containing only `0` and `1` characters
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' as_binary(x)
#'
#' from_binary(as_binary(x))
#' @seealso Use `as_packed()` and `from_packed()` to encode/decode raw bytes.
#' @name binary
NULL

#' @rdname binary
#' @export
as_binary <- function(ip) {
  to_binary_address_wrapper(ip)
}

#' @rdname binary
#' @export
from_binary <- function(bits) {
  from_binary_address_wrapper(bits)
}
