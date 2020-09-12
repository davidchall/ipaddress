#' Represent address as raw bytes
#'
#' Encode or decode an [`ip_address`] as a vector of raw bytes.
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
#'  * For `bytes_to_ip()`: A [`blob::blob`] vector
#'
#' @return
#'  * For `ip_to_bytes()`: A [`blob::blob`] vector
#'  * For `bytes_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_bytes(x)
#'
#' bytes_to_ip(ip_to_bytes(x))
#' @seealso
#'  * [ip_to_integer()] and [integer_to_ip()]
#'  * [ip_to_binary()] and [binary_to_ip()]
#' @export
ip_to_bytes <- function(x) {
  if (!is_ip_address(x)) {
    abort("`x` must be an ip_address vector")
  }

  blob::new_blob(wrap_encode_bytes(x))
}

#' @rdname ip_to_bytes
#' @export
bytes_to_ip <- function(x) {
  if (!blob::is_blob(x)) {
    abort("`x` must be a blob object")
  }

  wrap_decode_bytes(x)
}
