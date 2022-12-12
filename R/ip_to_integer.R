#' Represent address as integer
#'
#' @description
#' Encode or decode an [`ip_address`] as an integer.
#'
#' @details
#' It is common to represent an IP address as an integer, by reinterpreting
#' the bit sequence as a big-endian unsigned integer. This means IPv4 and IPv6
#' addresses can be represented by 32-bit and 128-bit unsigned integers.
#' In this way, the IPv4 addresses `0.0.0.0` and `255.255.255.255` would be
#' represented as 0 and 4,294,967,295.
#'
#' The numeric data types within base R ([`integer`] and [`double`]) have
#' insufficient precision to cover the IPv6 address space. Instead we return a
#' [`bignum::biginteger`] vector, which supports arbitrary precision integers.
#'
#' @param x
#'  * `ip_to_integer()`: An [`ip_address`] vector
#'  * `integer_to_ip()`: A [`bignum::biginteger`] vector
#' @inheritParams ip_to_hex
#'
#' @return
#'  * `ip_to_integer()`: A [`bignum::biginteger`] vector
#'  * `integer_to_ip()`: An [`ip_address`] vector
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
#' @family address representations
#' @export
ip_to_integer <- function(x) {
  check_installed("bignum")

  bignum::biginteger(ip_to_hex(x))
}

#' @rdname ip_to_integer
#' @export
integer_to_ip <- function(x, is_ipv6 = NULL) {
  check_installed("bignum")

  x <- vec_cast(x, bignum::biginteger())
  hex_to_ip(format(x, notation = "hex"), is_ipv6 = is_ipv6)
}
