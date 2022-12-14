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
#'  * `ip_to_binary()`: An [`ip_address`] vector
#'  * `binary_to_ip()`: A character vector containing only `0` and `1` characters
#'
#' @return
#'  * `ip_to_binary()`: A character vector
#'  * `binary_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_binary(x)
#'
#' binary_to_ip(ip_to_binary(x))
#' @family address representations
#' @export
ip_to_binary <- function(x) {
  check_address(x)
  wrap_encode_binary(x)
}

#' @rdname ip_to_binary
#' @export
binary_to_ip <- function(x) {
  check_character(x)
  wrap_decode_binary(x)
}
