#' Represent address as binary
#'
#' Encode or decode an [`ip_address`] as a binary bit string.
#'
#' @details
#' The bits are stored in network order (also known as big-endian order), which
#' is part of the IP standard.
#'
#' IPv4 addresses use 32 bits, IPv6 addresses use 128 bits, and missing values
#' are encoded as `NA`.
#'
#' @param x
#'  * For `ip_to_binary()`: An [`ip_address`] vector
#'  * For `binary_to_ip()`: A character vector containing only `0` and `1` characters
#'
#' @return
#'  * For `ip_to_binary()`: A character vector
#'  * For `binary_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_binary(x)
#'
#' binary_to_ip(ip_to_binary(x))
#' @seealso
#'  * [ip_to_integer()] and [integer_to_ip()]
#'  * [ip_to_bytes()] and [bytes_to_ip()]
#' @export
ip_to_binary <- function(x) {
  if (!is_ip_address(x)) {
    abort("`x` must be an ip_address vector")
  }

  wrap_encode_binary(x)
}

#' @rdname ip_to_binary
#' @export
binary_to_ip <- function(x) {
  if (!is_character(x)) {
    abort("`x` must be a character vector")
  }

  wrap_decode_binary(x)
}
