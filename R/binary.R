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
#' @param blob A \code{\link[blob]{blob}} vector
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
from_packed <- function(blob) {
  assertthat::assert_that(blob::is_blob(blob), msg = "argument is not a blob object")
  vec_cast(blob, ip_address())
}


#' Encode or decode address as binary
#'
#' @details
#' The bits are stored in network order (also known as
#' big-endian order), which is part of the IP standard.
#'
#' IPv4 addresses use 32 bits, IPv6 addresses use 128 bits,
#' and missing values are encoded as `NA`.
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

#' `as_binary()`
#'
#' `as_binary()` encodes an `ip_address` vector to a character vector of bits
#'
#' @rdname binary
#' @export
as_binary <- function(ip) {
  raw_to_binary <- function(raw) {
    if (is.null(raw)) return(NA_character_)

    # ipaddress returns big-endian order (bytes and bits), but
    # rawToBits returns little-endian order (bits)
    bits <- rawToBits(raw)
    bits <- unlist(lapply(split(bits, ceiling(seq_along(bits) / 8L)), rev), use.names = FALSE)

    paste(as.integer(bits), collapse = "")
  }

  vapply(as_packed(ip), raw_to_binary, "")
}

#' `from_binary()`
#'
#' `from_binary()` decodes a character vector of bits to an `ip_address` vector
#'
#' @rdname binary
#' @export
from_binary <- function(bits) {
  assertthat::assert_that(all(nchar(bits) %in% c(32L, 128L, NA)))

  binary_to_raw <- function(binary) {
    if (is.na(binary)) return(NULL)

    bits <- as.integer(unlist(strsplit(binary, "")))

    # ipaddress expects big-endian order (bytes and bits), but
    # packBits expects little-endian order (bits)
    bits <- unlist(lapply(split(bits, ceiling(seq_along(bits) / 8L)), rev), use.names = FALSE)
    packBits(bits)
  }

  from_packed(blob::as_blob(lapply(bits, binary_to_raw)))
}
