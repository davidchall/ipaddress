#' @importFrom methods setOldClass
methods::setOldClass(c("vctrs_ip_address", "vctrs_vctr"))

#' IP address
#'
#' IPv4 addresses are 32-bit integers that are usually presented as
#' a string in dotted-decimal notation, e.g. "192.168.0.1".
#'
#' @param x Vector of IP addresses
#' @param ... Other parameters passed on
#'
#' @name ip_address
NULL

# Construction ------------------------------------------------------------

#' `ip_address()`
#'
#' `ip_address()` is a high-level constructor that accepts character vectors
#' representing the IP address in dotted-decimal notation.
#'
#' @rdname ip_address
#' @export
ip_address <- function(x = character()) {
  octets <- strsplit(x, ".", fixed = TRUE)
  shift_bits <- function(x, y) bitwOr(bitwShiftL(x, 8L), y)
  out <- vapply(octets, function(x) Reduce(shift_bits, as.integer(x)), 0L)
  new_ip_address(out)
}

# `new_ip_address()` is a low-level constructor that accepts the data type
# stored in the background, [integer].
new_ip_address <- function(x = integer()) {
  vec_assert(x, ptype = integer())
  new_vctr(x, class = "vctrs_ip_address")
}

#' `is_ip_address()`
#'
#' `is_ip_address()` checks if an object is of class `ip_address`.
#'
#' @rdname ip_address
#' @export
is_ip_address <- function(x) {
  inherits(x, "vctrs_ip_address")
}

#' @rdname ip_address
#' @export
format.vctrs_ip_address <- function(x, ...) as.character(x)



# Casting ------------------------------------------------------------

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast vctrs_ip_address
#' @export
#' @export vec_cast.vctrs_ip_address
vec_cast.vctrs_ip_address <- function(x, to, ...) UseMethod("vec_cast.vctrs_ip_address")

#' @method vec_cast.vctrs_ip_address default
#' @export
vec_cast.vctrs_ip_address.default <- function(x, to, ...) vec_default_cast(x, to)

#' @method vec_cast.vctrs_ip_address vctrs_ip_address
#' @export
vec_cast.vctrs_ip_address.vctrs_ip_address <- function(x, to, ...) x

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast.vctrs_ip_address character
#' @export
vec_cast.vctrs_ip_address.character <- function(x, to, ...) ip_address(x)

#' @method vec_cast.character vctrs_ip_address
#' @export
vec_cast.character.vctrs_ip_address <- function(x, to, ...) {
  out <- paste(
    bitwAnd(bitwShiftR(x, 24L), 255L),
    bitwAnd(bitwShiftR(x, 16L), 255L),
    bitwAnd(bitwShiftR(x, 8L), 255L),
    bitwAnd(bitwShiftR(x, 0L), 255L),
    sep = "."
  )
  out[is.na(x)] <- NA
  out
}


# Coercion ------------------------------------------------------------

#' Coercion
#'
#' Double dispatch methods to support [vctrs::vec_ptype2()].
#' @inheritParams vctrs::vec_ptype2
#' @rdname vctrs-compat
#'
#' @method vec_ptype2 vctrs_ip_address
#' @export
#' @export vec_ptype2.vctrs_ip_address
vec_ptype2.vctrs_ip_address <- function(x, y, ...) UseMethod("vec_ptype2.vctrs_ip_address", y)

#' @method vec_ptype2.vctrs_ip_address default
#' @export
vec_ptype2.vctrs_ip_address.default <- function(x, y, ..., x_arg = "x", y_arg = "y") {
  vec_default_ptype2(x, y, x_arg = x_arg, y_arg = y_arg)
}

#' @method vec_ptype2.vctrs_ip_address vctrs_ip_address
#' @export
vec_ptype2.vctrs_ip_address.vctrs_ip_address <- function(x, y, ...) new_ip_address()

#' @method vec_ptype2.vctrs_ip_address character
#' @export
vec_ptype2.vctrs_ip_address.character <- function(x, y, ...) new_ip_address()

#' @method vec_ptype2.character vctrs_ip_address
#' @export
vec_ptype2.character.vctrs_ip_address <- function(x, y, ...) new_ip_address()


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.vctrs_ip_address <- function(x, ...) {
  left_mask <- bitwShiftL(1L, 16L) - 1
  right_mask <- bitwXor(bitwNot(0), left_mask)

  data.frame(
    right = bitwShiftR(bitwAnd(x, right_mask), 16),
    left = bitwAnd(x, left_mask)
  )
}


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.vctrs_ip_address <- function(x, ...) {
  "ip_addr"
}

#' @export
vec_ptype_full.vctrs_ip_address <- function(x, ...) {
  "ip_address"
}
