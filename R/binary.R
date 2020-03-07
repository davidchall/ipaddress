#' Encode or decode address as raw bytes
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
#' packed(x)
#'
#' unpack(packed(x))
#' @name packed
NULL

#' `packed()`
#'
#' `packed()` encodes an `ip_address` vector to a `blob`
#'
#' @rdname packed
#' @export
packed <- function(ip) {
  assertthat::assert_that(is_ip_address(ip))
  blob::as_blob(ip)
}

#' `unpack()`
#'
#' `unpack()` decodes a `blob` to an `ip_address` vector
#'
#' @rdname packed
#' @export
unpack <- function(blob) {
  assertthat::assert_that(blob::is_blob(blob), msg = "argument is not a blob object")
  vec_cast(blob, ip_address())
}
