#' Operators for IP addresses
#'
#' @description
#' [`ip_address`] vectors support the following operators:
#'
#' * bitwise logic operators: `!` (NOT), `&` (AND), `|` (OR), `^` (XOR)
#' * bitwise shift operators: `%<<%` (left shift), `%>>%` (right shift)
#' * arithmetic operators: `+` (addition), `-` (subtraction)
#'
#' @examples
#' # use ip_to_binary() to understand these examples better
#'
#' # bitwise NOT
#' !ip_address("192.168.0.1")
#'
#' # bitwise AND
#' ip_address("192.168.0.1") & ip_address("255.0.0.255")
#'
#' # bitwise OR
#' ip_address("192.168.0.0") | ip_address("255.0.0.255")
#'
#' # bitwise XOR
#' ip_address("192.168.0.0") ^ ip_address("255.0.0.255")
#'
#' # bitwise shift left
#' ip_address("192.168.0.1") %<<% 1
#'
#' # bitwise shift right
#' ip_address("192.168.0.1") %>>% 1
#'
#' # addition of integers
#' ip_address("192.168.0.1") + 10
#'
#' # subtraction of integers
#' ip_address("192.168.0.1") - 10
#' @name ip_operators
NULL


# bitwise shift operators -------------------------------------------

#' @usage NULL
#' @rdname ip_operators
#' @export
`%<<%` <- function(x, n) {
  if (!is_ip_address(x) || is_ip_interface(x) || !is_integerish(n)) {
    stop_incompatible_op("%<<%", x, n)
  }
  if (!all(n >= 0, na.rm = TRUE)) {
    abort("`n` must be a positive integer vector")
  }

  # vector recycling
  args <- vec_recycle_common(x, n)
  x <- args[[1L]]
  n <- args[[2L]]

  wrap_bitwise_shift_left(x, n)
}

#' @usage NULL
#' @rdname ip_operators
#' @export
`%>>%` <- function(x, n) {
  if (!is_ip_address(x) || is_ip_interface(x) || !is_integerish(n)) {
    stop_incompatible_op("%>>%", x, n)
  }
  if (!all(n >= 0, na.rm = TRUE)) {
    abort("`n` must be a positive integer vector")
  }

  # vector recycling
  args <- vec_recycle_common(x, n)
  x <- args[[1L]]
  n <- args[[2L]]

  wrap_bitwise_shift_right(x, n)
}


# vctrs arithmetic operators --------------------------------------

#' @method vec_arith ip_address
#' @export
#' @export vec_arith.ip_address
#' @rdname ipaddress-vctrs
vec_arith.ip_address <- function(op, x, y, ...) {
  UseMethod("vec_arith.ip_address", y)
}

#' @method vec_arith.ip_address default
#' @export
vec_arith.ip_address.default <- function(op, x, y, ...) {
  stop_incompatible_op(op, x, y)
}

#' @method vec_arith.ip_address ip_address
#' @export
vec_arith.ip_address.ip_address <- function(op, x, y, ...) {
  args <- vec_recycle_common(x, y)
  x <- args[[1L]]
  y <- args[[2L]]

  switch(
    op,
    "&" = wrap_bitwise_and(x, y),
    "|" = wrap_bitwise_or(x, y),
    "^" = wrap_bitwise_xor(x, y),
    stop_incompatible_op(op, x, y)
  )
}

#' @method vec_arith.ip_address integer
#' @export
vec_arith.ip_address.integer <- function(op, x, y, ...) {
  args <- vec_recycle_common(x, y)
  x <- args[[1L]]
  y <- args[[2L]]

  switch(
    op,
    "+" = wrap_add_integer(x, y),
    "-" = wrap_add_integer(x, -y),
    stop_incompatible_op(op, x, y)
  )
}

#' @method vec_arith.ip_address double
#' @export
vec_arith.ip_address.double <- function(op, x, y, ...) {
  if (!is_integerish(y)) {
    stop_incompatible_op(op, x, y)
  }

  args <- vec_recycle_common(x, y)
  x <- args[[1L]]
  y <- args[[2L]]

  switch(
    op,
    "+" = wrap_add_integer(x, y),
    "-" = wrap_add_integer(x, -y),
    stop_incompatible_op(op, x, y)
  )
}

#' @method vec_arith.ip_address MISSING
#' @export
vec_arith.ip_address.MISSING <- function(op, x, y, ...) {
  switch(
    op,
    "!" = wrap_bitwise_not(x),
    stop_incompatible_op(op, x, y)
  )
}


# Disable operators for ip_interface class ------------------------------------

#' @method vec_arith ip_interface
#' @export
#' @export vec_arith.ip_interface
#' @rdname ipaddress-vctrs
vec_arith.ip_interface <- function(op, x, y, ...) {
  stop_incompatible_op(op, x, y)
}

#' @method vec_arith.ip_address ip_interface
#' @export
vec_arith.ip_address.ip_interface <- function(op, x, y, ...) {
  stop_incompatible_op(op, x, y)
}
