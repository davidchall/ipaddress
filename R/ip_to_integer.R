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
#' @param x
#'  * For `ip_to_integer()`: An [`ip_address`] vector
#'  * For `integer_to_ip()`: A [`bignum::biginteger`] vector
#' @param base A string choosing the numeric base of the output. Choices are
#'   decimal (`"dec"`; the default), hexadecimal (`"hex"`), and binary (`"bin"`).
#' @param is_ipv6 A logical vector indicating whether to construct an IPv4 or
#'   IPv6 address. If `NULL` (the default), then integers less than 2^32 will
#'   construct an IPv4 address and anything larger will construct an IPv6 address.
#'
#' @return
#'  * For `ip_to_integer()`: A [`bignum::biginteger`] vector
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

  switch(arg_match(base),
    dec = {
      if (!is_installed("bignum")) {
        abort("`bignum` must be installed to use `base = \"dec\"`.")
      }
      bignum::biginteger(wrap_encode_integer(x))
    },
    hex = wrap_encode_integer(x),
    bin = wrap_encode_binary(x)
  )
}

#' @rdname ip_to_integer
#' @export
integer_to_ip <- function(x, is_ipv6 = NULL) {
  if (!is_installed("bignum")) {
    abort("`bignum` must be installed to use `integer_to_ip()`.")
  }

  x <- vec_cast(x, bignum::biginteger())
  if (!(is_null(is_ipv6) || is_logical(is_ipv6))) {
    abort("`is_ipv6` must be a logical vector or NULL")
  }

  if (is_null(is_ipv6)) {
    is_ipv6 <- x >= bignum::biginteger(2)^32L
  } else {
    args <- vec_recycle_common(x, is_ipv6)
    x <- args[[1L]]
    is_ipv6 <- args[[2L]]
  }

  if (any(x < 0, na.rm = TRUE)) {
    warn("Found negative integers.")
  }

  max_value <- bignum::biginteger(2)^ifelse(is_ipv6, 128L, 32L)
  if (any(x >= max_value, na.rm = TRUE)) {
    warn("Found integers beyond the address space.")
    x[x >= max_value] <- bignum::NA_biginteger_
  }

  wrap_decode_integer(format(x, notation = "hex"), is_ipv6)
}
