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
