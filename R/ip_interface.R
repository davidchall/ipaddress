#' Vector of IP interfaces
#'
#' @description
#' Construct a vector of IP interfaces.
#'
#' This hybrid class stores both the host address and the network it is on.
#'
#' @details
#' Constructing an `ip_interface` vector is conceptually like constructing an
#' [`ip_network`] vector, except the host bits are retained.
#'
#' The `ip_interface` class inherits from the [`ip_address`] class.
#' This means it can generally be used in places where an [`ip_address`]
#' vector is expected. A few exceptions to this rule are:
#' * It does not support addition and subtraction of integers
#' * It does not support bitwise operations
#' * It cannot be compared to [`ip_address`] vectors
#'
#' The `ip_interface` class additionally supports a few functions typically
#' reserved for [`ip_network`] vectors: [prefix_length()], [netmask()] and
#' [hostmask()].
#'
#' For other purposes, you can extract the address and network components using
#' [as_ip_address()] and [as_ip_network()].
#'
#' When comparing and sorting `ip_interface` vectors, the network is compared
#' before the host address.
#'
#' @inheritParams rlang::args_dots_used
#' @param x A character vector of IP interfaces, in CIDR notation (IPv4 or IPv6)
#' @param address An [`ip_address`] vector
#' @param prefix_length An integer vector
#' @return An S3 vector of class `ip_interface`
#'
#' @examples
#' # construct from character vector
#' ip_interface(c("192.168.0.1/10", "2001:db8:c3::abcd/45"))
#'
#' # construct from address + prefix length objects
#' ip_interface(ip_address(c("192.168.0.1", "2001:db8:c3::abcd")), c(10L, 45L))
#'
#' # extract IP address
#' x <- ip_interface(c("192.168.0.1/10", "2001:db8:c3::abcd/45"))
#' as_ip_address(x)
#'
#' # extract IP network (with host bits masked)
#' as_ip_network(x)
#' @seealso
#' `vignette("ipaddress-classes")`
#' @name ip_interface
NULL


# Construction ------------------------------------------------------------

#' @rdname ip_interface
#' @export
ip_interface <- function(...) {
  check_dots_used()
  UseMethod("ip_interface")
}

#' @rdname ip_interface
#' @export
ip_interface.default <- function(x = character(), ...) {
  new_ip_interface_reclass(wrap_parse_network(x, FALSE, TRUE))
}

#' @rdname ip_interface
#' @export
ip_interface.ip_address <- function(address, prefix_length, ...) {
  if (!is_integerish(prefix_length)) {
    abort("`prefix_length` must be an integer vector")
  }

  # vector recycling
  args <- vec_recycle_common(address, prefix_length)
  address <- args[[1L]]
  prefix_length <- args[[2L]]

  new_ip_interface_reclass(wrap_construct_network_from_address(address, prefix_length, FALSE, TRUE))
}

#' Low-level constructor that accepts the encoded data from C++.
#' This has already been validated to conform to vctrs_rcrd requirements,
#' so we just need to convert the class from ip_network to ip_interface.
#' @noRd
new_ip_interface_reclass <- function(x) {
  class(x) <- c("ip_interface", "ip_address", "vctrs_rcrd", "vctrs_vctr")
  x
}

#' Low-level constructor that accepts the underlying data types being stored
#' @noRd
new_ip_interface <- function(address1 = integer(), address2 = integer(), address3 = integer(), address4 = integer(), prefix = integer(), is_ipv6 = logical()) {
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
  ), class = c("ip_interface", "ip_address"))
}

#' @examples
#' is_ip_interface(ip_interface("192.168.0.1/10"))
#' @rdname ip_test
#' @export
is_ip_interface <- function(x) inherits(x, "ip_interface")


# Casting ------------------------------------------------------------

#' @rdname ip_cast
#' @export
as_ip_interface <- function(x) UseMethod("as_ip_interface")

#' @export
as_ip_interface.character <- function(x) ip_interface(x)

#' @export
as.character.ip_interface <- function(x, ...) wrap_print_network(x)

#' @rdname ip_format
#' @export
format.ip_interface <- function(x, ..., exploded = FALSE) {
  wrap_print_network(x, exploded)
}


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_interface <- function(x, ...) {
  compare_network <- vec_proxy_compare(as_ip_network(x))
  compare_address <- vec_proxy_compare(as_ip_address(x))

  cbind(compare_network, compare_address)
}


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_interface <- function(x, ...) {
  "ip_intf"
}
