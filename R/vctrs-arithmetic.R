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
  switch(
    op,
    "&" = new_ip_address_encode(bitwise_and_wrapper(x, y)),
    "|" = new_ip_address_encode(bitwise_or_wrapper(x, y)),
    "^" = new_ip_address_encode(bitwise_xor_wrapper(x, y)),
    stop_incompatible_op(op, x, y)
  )
}

#' @method vec_arith.ip_address MISSING
#' @export
vec_arith.ip_address.MISSING <- function(op, x, y, ...) {
  switch(
    op,
    "!" = new_ip_address_encode(bitwise_not_wrapper(x)),
    stop_incompatible_op(op, x, y)
  )
}
