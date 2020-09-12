#' Represent address as raw bytes
#'
#' Encode or decode an [`ip_address`] as a list of raw bytes.
#'
#' @details
#' The bytes are stored in network order (also known as
#' big-endian order), which is part of the IP standard.
#'
#' IPv4 addresses use 4 bytes, IPv6 addresses use 16 bytes,
#' and missing values are encoded as `NULL`.
#'
#' @param x
#'  * For `ip_to_bytes()`: An [`ip_address`] vector
#'  * For `bytes_to_ip()`: A list of raw vectors or a [`blob::blob`] object
#'
#' @return
#'  * For `ip_to_bytes()`: A list of raw vectors
#'  * For `bytes_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_bytes(x)
#'
#' bytes <- list(
#'   as.raw(c(0xc0, 0xa8, 0x00, 0x01)),
#'   as.raw(c(
#'     0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
#'     0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34
#'   )),
#'   NULL
#' )
#' bytes_to_ip(bytes)
#' @seealso
#'  * [ip_to_integer()] and [integer_to_ip()]
#'  * [ip_to_binary()] and [binary_to_ip()]
#'  * Use [blob::as_blob()] to cast result to a blob object
#' @export
ip_to_bytes <- function(x) {
  if (!is_ip_address(x)) {
    abort("`x` must be an ip_address vector")
  }

  wrap_encode_bytes(x)
}

#' @rdname ip_to_bytes
#' @export
bytes_to_ip <- function(x) {
  is_bytes <- function(y) is_raw(y) || is_null(y)

  if (!is_list(x) || !all(vapply(x, is_bytes, TRUE))) {
    abort("`x` must be a list of raw vectors")
  }

  wrap_decode_bytes(x)
}
