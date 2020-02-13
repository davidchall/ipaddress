#' @importFrom methods setOldClass
methods::setOldClass(c("vctrs_ip_network", "vctrs_vctr"))

#' IP network
#'
#' @param x Vector of IP networks
#' @param ... Other parameters passed on
#'
#' @name ip_network
NULL

# Construction ------------------------------------------------------------

#' `ip_network()`
#'
#' `ip_network()` is a high-level constructor that accepts character vectors
#' representing the IP network in CIDR notation.
#'
#' @rdname ip_network
#' @export
ip_network <- function(x = character()) {
  parts <- ipv4_network_aton(x)
  new_ip_network(parts$address, parts$prefix)
}

# `new_ip_network()` is a low-level constructor that accepts the data types
# stored in the background, [integer, integer].
new_ip_network <- function(address = integer(), prefix = integer()) {
  vec_assert(address, ptype = integer())
  vec_assert(prefix, ptype = integer())

  new_rcrd(list(address = address, prefix = prefix), class = "vctrs_ip_network")
}

#' `is_ip_network()`
#'
#' `is_ip_network()` checks if an object is of class `ip_network`.
#'
#' @rdname ip_network
#' @export
is_ip_network <- function(x) {
  inherits(x, "vctrs_ip_network")
}

#' @rdname ip_network
#' @export
format.vctrs_ip_network <- function(x, ...) as.character(x)



# Casting ------------------------------------------------------------

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast vctrs_ip_network
#' @export
#' @export vec_cast.vctrs_ip_network
vec_cast.vctrs_ip_network <- function(x, to, ...) UseMethod("vec_cast.vctrs_ip_network")

#' @method vec_cast.vctrs_ip_network default
#' @export
vec_cast.vctrs_ip_network.default <- function(x, to, ...) vec_default_cast(x, to)

#' @method vec_cast.vctrs_ip_network vctrs_ip_network
#' @export
vec_cast.vctrs_ip_network.vctrs_ip_network <- function(x, to, ...) x

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast.vctrs_ip_network character
#' @export
vec_cast.vctrs_ip_network.character <- function(x, to, ...) ip_network(x)

#' @method vec_cast.character vctrs_ip_network
#' @export
vec_cast.character.vctrs_ip_network <- function(x, to, ...) {
  ipv4_network_ntoa(field(x, "address"), field(x, "prefix"))
}


# Coercion ------------------------------------------------------------

#' Coercion
#'
#' Double dispatch methods to support [vctrs::vec_ptype2()].
#' @inheritParams vctrs::vec_ptype2
#' @rdname vctrs-compat
#'
#' @method vec_ptype2 vctrs_ip_network
#' @export
#' @export vec_ptype2.vctrs_ip_network
vec_ptype2.vctrs_ip_network <- function(x, y, ...) UseMethod("vec_ptype2.vctrs_ip_network", y)

#' @method vec_ptype2.vctrs_ip_network default
#' @export
vec_ptype2.vctrs_ip_network.default <- function(x, y, ..., x_arg = "x", y_arg = "y") {
  vec_default_ptype2(x, y, x_arg = x_arg, y_arg = y_arg)
}

#' @method vec_ptype2.vctrs_ip_network vctrs_ip_network
#' @export
vec_ptype2.vctrs_ip_network.vctrs_ip_network <- function(x, y, ...) new_ip_network()

#' @method vec_ptype2.vctrs_ip_network character
#' @export
vec_ptype2.vctrs_ip_network.character <- function(x, y, ...) new_ip_network()

#' @method vec_ptype2.character vctrs_ip_network
#' @export
vec_ptype2.character.vctrs_ip_network <- function(x, y, ...) new_ip_network()


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.vctrs_ip_network <- function(x, ...) {
  left_mask <- bitwShiftL(1L, 16L) - 1L
  right_mask <- bitwXor(bitwNot(0L), left_mask)

  data.frame(
    right = bitwShiftR(bitwAnd(field(x, "address"), right_mask), 16L),
    left = bitwAnd(field(x, "address"), left_mask)
  )
}


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.vctrs_ip_network <- function(x, ...) {
  "ip_netw"
}

#' @export
vec_ptype_full.vctrs_ip_network <- function(x, ...) {
  "ip_network"
}
