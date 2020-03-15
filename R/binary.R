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
#' and missing values are stored as `NULL`.
#'
#' @param ip An \code{\link{ip_address}} vector
#' @param blob A \code{\link[blob]{blob}} vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' as_packed(x)
#'
#' from_packed(as_packed(x))
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
from_packed <- function(blob) {
  assertthat::assert_that(blob::is_blob(blob), msg = "argument is not a blob object")
  vec_cast(blob, ip_address())
}
