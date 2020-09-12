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
#' @param base A string choosing the numeric base of the output. Choices are
#'   decimal (`"dec"`; the default), hexadecimal (`"hex"`), and binary (`"bin"`).
#' @param is_ipv6 A logical vector indicating whether to construct an IPv4 or
#'   IPv6 address. If `NULL` (the default), then integers less than 2^32 will
#'   construct an IPv4 address and anything larger will construct an IPv6 address.
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
#'
#' # with IPv4 only, we can use numeric data type
#' as.numeric(ip_to_integer(ip_address("192.168.0.1")))
#'
#' integer_to_ip(3232235521)
#'
#' # hex representation
#' ip_to_integer(x, base = "hex")
#' @seealso
#'  * [ip_to_bytes()] and [bytes_to_ip()]
#'  * [ip_to_binary()] and [binary_to_ip()]
#' @export
ip_to_integer <- function(x, base = c("dec", "hex", "bin")) {
  if (!is_ip_address(x)) {
    abort("`x` must be an ip_address vector")
  }

  switch(
    arg_match(base),
    dec = wrap_encode_integer(x, FALSE),
    hex = wrap_encode_integer(x, TRUE),
    bin = wrap_encode_binary(x)
  )
}

#' @rdname ip_to_integer
#' @export
integer_to_ip <- function(x, is_ipv6 = NULL) {
  if (is_integerish(x)) {
    x <- as.character(x)
  }
  if (!is_character(x)) {
    abort("`x` must be a character vector")
  }
  if (!(is_null(is_ipv6) || is_logical(is_ipv6))) {
    abort("`is_ipv6` must be a logical vector or NULL")
  }

  # vector recycling
  if (!is_null(is_ipv6)) {
    args <- vec_recycle_common(x, is_ipv6)
    x <- args[[1L]]
    is_ipv6 <- args[[2L]]
  }

  wrap_decode_integer(x, is_ipv6)
}
