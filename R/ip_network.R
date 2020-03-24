#' @importFrom methods setOldClass
methods::setOldClass(c("ip_network", "vctrs_vctr"))

#' Vector of IP networks
#'
#' @details
#' An IP network corresponds to a contiguous range of IP addresses
#' (also known as an IP block). CIDR notation represents an
#' IP network as the routing prefix address (which denotes the start
#' of the range) and the prefix length (which indicates the size of
#' the range) separated by a forward slash. For example, `192.168.0.0/24`
#' represents addresses from `192.168.0.0` to `192.168.0.255`.
#'
#' The prefix length indicates the number of bits reserved by the
#' routing prefix. This means that larger prefix lengths indicate
#' smaller networks. The maximum prefix length is 32 for IPv4 and
#' 128 for IPv6. These would correspond to an IP network of a single
#' IP address.
#'
#' The `ip_network()` constructor accepts a character vector of IP networks
#' in CIDR notation. It checks whether each string is a valid IPv4 or IPv6
#' network, and converts it to an `ip_network` object. If the input is invalid,
#' a warning is emitted and `NA` is stored instead.
#'
#' An alternative constructor accepts an \code{\link{ip_address}} vector and an
#' integer vector containing the network address and prefix length, respectively.
#'
#' When casting an `ip_network` object back to a character vector using
#' `as.character()`, IPv6 addresses are reduced to their compressed representation.
#'
#' @seealso [prefix_length()], [network_address()], [netmask()], [hostmask()]
#'
#' @param x An `ip_network` vector
#' @param ... Arguments to be passed to other methods
#'
#' @name ip_network
NULL


# Construction ------------------------------------------------------------

#' `ip_network()`
#'
#' `ip_network()` constructs a vector of IP networks.
#'
#' @param ip Character vector of IP networks, in CIDR notation (IPv4 or IPv6).
#' @param address An \code{\link{ip_address}} vector
#' @param prefix_length An integer vector
#' @param strict If `TRUE` (the default) and the input has host bits set,
#'   then a warning is emitted and `NA` is returned. If `FALSE`, the
#'   host bits are set to zero and a valid IP network is returned. If you need
#'   to retain the host bits, consider using `ip_interface()` instead.
#' @return An `ip_network` vector
#'
#' @examples
#' # construct from character vector
#' ip_network(c("192.168.0.0/24", "2001:db8::/48"))
#'
#' # construct from address + prefix length objects
#' ip_network(ip_address(c("192.168.0.0", "2001:db8::")), c(24L, 48L))
#'
#' # validates inputs and replaces with NA
#' ip_network(c("192.168.0.0/33", "192.168.0.0"))
#'
#' # IP networks should not have any host bits set
#' ip_network("192.168.0.1/22")
#'
#' # but we can mask the host bits if desired
#' ip_network("192.168.0.1/22", strict = FALSE)
#' @rdname ip_network
#' @export
ip_network <- function(...) {
  UseMethod("ip_network")
}

#' @rdname ip_network
#' @export
ip_network.default <- function(ip = character(), strict = TRUE, ...) {
  if (!is_bool(strict)) {
    abort("'strict' be must TRUE or FALSE")
  }

  wrap_parse_network(ip, strict)
}

#' @rdname ip_network
#' @export
ip_network.ip_address <- function(address, prefix_length, strict = TRUE, ...) {
  if (!is_integer(prefix_length)) {
    abort("'prefix_length' must be an integer vector")
  }
  if (!is_bool(strict)) {
    abort("'strict' be must TRUE or FALSE")
  }

  # vector recycling
  args <- vec_recycle_common(address, prefix_length)
  address <- args[[1L]]
  prefix_length <- args[[2L]]

  wrap_construct_network_from_address(address, prefix_length, strict)
}

#' Low-level constructor that accepts the underlying data types being stored
#' @noRd
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

#' `as_ip_network()`
#'
#' `as_ip_network()` casts an object to `ip_network`.
#'
#' @rdname ip_network
#' @export
as_ip_network <- function(x) vec_cast(x, ip_network())

#' `is_ip_network()`
#'
#' `is_ip_network()` checks if an object is of class `ip_network`.
#'
#' @rdname ip_network
#' @export
is_ip_network <- function(x) inherits(x, "ip_network")

#' @rdname ip_network
#' @export
format.ip_network <- function(x, ...) as.character(x)

#' @rdname ip_network
#' @export
as.character.ip_network <- function(x, ...) vec_cast(x, character())


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_network <- function(x, ...) {
  wrap_compare_address(network_address(x))
}


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_network <- function(x, ...) {
  "ip_netwk"
}
