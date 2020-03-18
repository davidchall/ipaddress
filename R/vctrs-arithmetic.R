#' Arithmetic operations
#'
#' Double dispatch methods to support [vctrs::vec_arith()].
#'
#' @inherit vctrs::vec_arith return params
#' @keywords internal
#' @method vec_arith ip_address
#' @export
#' @export vec_arith.ip_address
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
    "&" = bitwise_and_wrapper(x, y),
    "|" = bitwise_or_wrapper(x, y),
    "^" = bitwise_xor_wrapper(x, y),
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
    "+" = addition_wrapper(x, y),
    "-" = addition_wrapper(x, -y),
    stop_incompatible_op(op, x, y)
  )
}

#' @method vec_arith.ip_address MISSING
#' @export
vec_arith.ip_address.MISSING <- function(op, x, y, ...) {
  switch(
    op,
    "!" = bitwise_not_wrapper(x),
    stop_incompatible_op(op, x, y)
  )
}


# Disable operators for ip_interface class ------------------------------------

#' Arithmetic operations
#'
#' Double dispatch methods to support [vctrs::vec_arith()].
#'
#' @inherit vctrs::vec_arith return params
#' @keywords internal
#' @method vec_arith ip_interface
#' @export
#' @export vec_arith.ip_interface
vec_arith.ip_interface <- function(op, x, y, ...) {
  stop_incompatible_op(op, x, y)
}

#' @method vec_arith.ip_address ip_interface
#' @export
vec_arith.ip_address.ip_interface <- function(op, x, y, ...) {
  stop_incompatible_op(op, x, y)
}
