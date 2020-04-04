#' Represent address as integer
#'
#' @description
#' Encode or decode an [`ip_address`] as an integer.
#'
#' **Note:** The result is a character vector (see below for why). This can be
#' converted using [as.numeric()] for IPv4 addresses.
#'
#' @details
#' It is common to represent an IP address as an integer, by reinterpreting
#' the bit sequence as a big-endian unsigned integer. This means IPv4 and IPv6
#' addresses can be represented by 32-bit and 128-bit unsigned integers.
#' In this way, the IPv4 addresses `0.0.0.0` and `255.255.255.255` would be
#' represented as 0 and 4,294,967,295.
#'
#' @section Why is a character vector returned?:
#' Base R provides two data types that can store integers: [`integer`] and
#' [`double`] (also known as [`numeric`]). The former is a fixed-point data
#' format (32-bit) and the latter is a floating-point data format (64-bit).
#' Both types are signed, and R does not offer unsigned variants.
#'
#' For the purpose of storing IP addresses as integers, we need to be able to
#' store a large range of positive integers without losing integer precision.
#' Under these circumstances, the [`integer`] type can store integers up to
#' 2^31 - 1 and the [`double`] type can store integers up to 2^53. However,
#' for IPv4 and IPv6 addresses we need to store integers up to 2^32 - 1 and
#' 2^128 - 1, respectively. This means an IPv4 address can be stored in a
#' [`double`], but an IPv6 address cannot be stored in either R data type.
#'
#' Although the integer representation of an IPv6 address cannot be stored in
#' a numeric R data type, it can be stored as a character string instead.
#' This allows the integer to be written to disk or used by other software that
#' _does_ support 128-bit unsigned integers. To treat IPv4 and IPv6 equally,
#' `ip_to_integer()` will always return a [`character`] vector. With IPv4
#' addresses, this output can be converted to a [`double`] vector using
#' [as.double()] or [as.numeric()]. With IPv6 addresses, this conversion loses
#' the distinction between individual addresses because integer precision is lost.
#'
#' @param x
#'  * For `ip_to_integer()`: An [`ip_address`] vector
#'  * For `integer_to_ip()`: A character vector
#'
#' @return
#'  * For `ip_to_integer()`: A character vector
#'  * For `integer_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_integer(x)
#'
#' integer_to_ip(ip_to_integer(x))
#' @seealso
#'  * [ip_to_bytes()] and [bytes_to_ip()]
#'  * [ip_to_bits()] and [bits_to_ip()]
#' @name ip_to_integer
NULL

#' @rdname ip_to_integer
#' @export
ip_to_integer <- function(x) {
  if (!is_ip_address(x)) {
    abort("'x' must be an ip_address vector")
  }

  wrap_encode_integer(x)
}

#' @rdname ip_to_integer
#' @export
integer_to_ip <- function(x) {
  if (!is_character(x)) {
    abort("'x' must be a character vector")
  }

  wrap_decode_integer(x, TRUE)
}


#' Represent address as raw bytes
#'
#' Encode or decode an [`ip_address`] vector to a vector of raw bytes.
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
#'  * [ip_to_bits()] and [bits_to_ip()]
#' @name ip_to_bytes
NULL

#' @rdname ip_to_bytes
#' @export
ip_to_bytes <- function(x) {
  if (!is_ip_address(x)) {
    abort("'x' must be an ip_address vector")
  }

  blob::as_blob(x)
}

#' @rdname ip_to_bytes
#' @export
bytes_to_ip <- function(x) {
  if (!blob::is_blob(x)) {
    abort("'x' must be a blob object")
  }

  vec_cast(x, ip_address())
}


#' Represent address as sequence of bits
#'
#' Encode or decode an [`ip_address`] vector to a character vector of bits.
#'
#' @details
#' The bits are stored in network order (also known as big-endian order), which
#' is part of the IP standard.
#'
#' IPv4 addresses use 32 bits, IPv6 addresses use 128 bits, and missing values
#' are encoded as `NA`.
#'
#' @param x
#'  * For `ip_to_bits()`: An [`ip_address`] vector
#'  * For `bits_to_ip()`: A character vector containing only `0` and `1` characters
#'
#' @return
#'  * For `ip_to_bits()`: A character vector
#'  * For `bits_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_bits(x)
#'
#' bits_to_ip(ip_to_bits(x))
#' @seealso
#'  * [ip_to_integer()] and [integer_to_ip()]
#'  * [ip_to_bytes()] and [bytes_to_ip()]
#' @name ip_to_bits
NULL

#' @rdname ip_to_bits
#' @export
ip_to_bits <- function(x) {
  if (!is_ip_address(x)) {
    abort("'x' must be an ip_address vector")
  }

  wrap_encode_binary(x)
}

#' @rdname ip_to_bits
#' @export
bits_to_ip <- function(x) {
  if (!is_character(x)) {
    abort("'x' must be a character vector")
  }

  wrap_decode_binary(x)
}
