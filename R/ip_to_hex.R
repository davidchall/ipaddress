#' Represent address as hexadecimal
#'
#' Encode or decode an [`ip_address`] as a hexadecimal string.
#'
#' @param x
#'  * For `ip_to_hex()`: An [`ip_address`] vector
#'  * For `hex_to_ip()`: A character vector containing hexadecimal strings
#' @inheritParams ip_to_integer
#'
#' @return
#'  * For `ip_to_hex()`: A character vector
#'  * For `hex_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_hex(x)
#'
#' hex_to_ip(ip_to_hex(x))
#' @family address representations
#' @export
ip_to_hex <- function(x) {
  if (!is_ip_address(x)) {
    abort("`x` must be an ip_address vector")
  }

  wrap_encode_hex(x)
}

#' @rdname ip_to_hex
#' @export
hex_to_ip <- function(x, is_ipv6 = NULL) {
  if (!is_character(x)) {
    abort("`x` must be a character vector")
  }
  if (!(is_null(is_ipv6) || is_logical(is_ipv6))) {
    abort("`is_ipv6` must be a logical vector or NULL")
  }

  if (!all(grepl("^0[xX][0-9a-fA-F]+$", x[!is.na(x)], perl = TRUE))) {
    abort("Found invalid hexadecimal string")
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
