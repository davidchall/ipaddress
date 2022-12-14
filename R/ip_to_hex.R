#' Represent address as hexadecimal
#'
#' Encode or decode an [`ip_address`] as a hexadecimal string.
#'
#' @param x
#'  * `ip_to_hex()`: An [`ip_address`] vector
#'  * `hex_to_ip()`: A character vector containing hexadecimal strings
#' @param is_ipv6 A logical vector indicating whether to construct an IPv4 or
#'   IPv6 address. If `NULL` (the default), then IPv4 is preferred but an IPv6
#'   address is constructed when `x` is too large for the IPv4 address space.
#'
#' @return
#'  * `ip_to_hex()`: A character vector
#'  * `hex_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_hex(x)
#'
#' hex_to_ip(ip_to_hex(x))
#' @family address representations
#' @export
ip_to_hex <- function(x) {
  check_address(x)
  wrap_encode_hex(x)
}

#' @rdname ip_to_hex
#' @export
hex_to_ip <- function(x, is_ipv6 = NULL) {
  check_character(x)
  check_all(
    grepl("^0[xX][0-9a-fA-F]+$", x %|% "0xff", perl = TRUE),
    "x", "must be a hexadecimal string"
  )

  if (!(is_null(is_ipv6) || is_logical(is_ipv6))) {
    cli::cli_abort("{.arg is_ipv6} must be a logical vector or NULL")
  }

  if (is_null(is_ipv6)) {
    is_ipv6 <- nchar(x) > 10L
  } else {
    args <- vec_recycle_common(x, is_ipv6)
    x <- args[[1L]]
    is_ipv6 <- args[[2L]]
  }

  x_oob <- nchar(x) > ifelse(is_ipv6, 34L, 10L)
  if (any(x_oob, na.rm = TRUE)) {
    warn("Found out-of-bounds input value(s)")
    x[x_oob] <- NA_character_
  }

  wrap_decode_hex(x, is_ipv6)
}
