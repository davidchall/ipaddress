#' @importFrom methods setOldClass
methods::setOldClass(c("ip_network", "vctrs_vctr"))

#' Class for storing IP networks
#'
#' @param x An object
#' @param ... Additional arguments to be passed to or from methods
#'
#' @name ip_network
NULL


# Construction ------------------------------------------------------------

#' `ip_network()`
#'
#' `ip_network()` constructs a vector of IP networks.
#'
#' @param ip Character vector of IP networks, in CIDR notation (IPv4 or IPv6).
#'
#' @examples
#' # supports IPv4 and IPv6 simultaneously
#' ip_network(c("92.0.2.0/24", "192.168.100.0/22", "2001:db8::/48"))
#'
#' # validates inputs and replaces with NA
#' ip_network(c("192.168.0.0/24", "192.168.0.0/33", "1.2.3.4"))
#'
#' @rdname ip_network
#' @export
ip_network <- function(ip = character()) {
  y <- parse_network_wrapper(ip)
  new_ip_network(
    y$address1, y$address2, y$address3, y$address4,
    y$prefix,
    y$is_ipv6
  )
}

# low-level constructor that accepts the underlying data types being stored
new_ip_network <- function(address1 = integer(), address2 = integer(), address3 = integer(), address4 = integer(), prefix = integer(), is_ipv6 = logical()) {
  vec_assert(address1, ptype = integer())
  vec_assert(address2, ptype = integer())
  vec_assert(address3, ptype = integer())
  vec_assert(address4, ptype = integer())
  vec_assert(prefix, ptype = integer())
  vec_assert(is_ipv6, ptype = logical())

  new_rcrd(list(
    address1 = address1, address2 = address2, address3 = address3, address4 = address4,
    prefix = prefix,
    is_ipv6 = is_ipv6
  ), class = "ip_network")
}

#' `is_ip_network()`
#'
#' `is_ip_network()` checks if an object is of class `ip_network`.
#'
#' @rdname ip_network
#' @export
is_ip_network <- function(x) inherits(x, "ip_network")

assertthat::on_failure(is_ip_network) <- function(call, env) {
  paste0(deparse(call$x), " is not an ip_network vector")
}

#' @rdname ip_network
#' @export
format.ip_network <- function(x, ...) as.character(x)


# Casting ------------------------------------------------------------

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast ip_network
#' @export
#' @export vec_cast.ip_network
vec_cast.ip_network <- function(x, to, ...) UseMethod("vec_cast.ip_network")

#' @method vec_cast.ip_network default
#' @export
vec_cast.ip_network.default <- function(x, to, ...) vec_default_cast(x, to)

#' @method vec_cast.ip_network ip_network
#' @export
vec_cast.ip_network.ip_network <- function(x, to, ...) x

#' @rdname vctrs-compat
#' @keywords internal
#' @method vec_cast.ip_network character
#' @export
vec_cast.ip_network.character <- function(x, to, ...) ip_network(x)

#' @method vec_cast.character ip_network
#' @export
vec_cast.character.ip_network <- function(x, to, ...) print_network_wrapper(x)

#' @rdname ip_network
#' @export
as.character.ip_network <- function(x, ...) vec_cast(x, character())


# Coercion ------------------------------------------------------------

#' Coercion
#'
#' Double dispatch methods to support [vctrs::vec_ptype2()].
#' @inheritParams vctrs::vec_ptype2
#' @rdname vctrs-compat
#'
#' @method vec_ptype2 ip_network
#' @export
#' @export vec_ptype2.ip_network
vec_ptype2.ip_network <- function(x, y, ...) UseMethod("vec_ptype2.ip_network", y)

#' @method vec_ptype2.ip_network default
#' @export
vec_ptype2.ip_network.default <- function(x, y, ..., x_arg = "x", y_arg = "y") {
  vec_default_ptype2(x, y, x_arg = x_arg, y_arg = y_arg)
}

#' @method vec_ptype2.ip_network ip_network
#' @export
vec_ptype2.ip_network.ip_network <- function(x, y, ...) new_ip_network()

#' @method vec_ptype2.ip_network character
#' @export
vec_ptype2.ip_network.character <- function(x, y, ...) new_ip_network()

#' @method vec_ptype2.character ip_network
#' @export
vec_ptype2.character.ip_network <- function(x, y, ...) new_ip_network()


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_network <- function(x, ...) compare_network_wrapper(x)


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_network <- function(x, ...) {
  "ip_netw"
}
