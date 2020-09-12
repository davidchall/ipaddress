#' Vector of IP networks
#'
#' @description
#' `ip_network()` constructs a vector of IP networks.
#'
#' `is_ip_network()` checks if an object is of class `ip_network`.
#'
#' `as_ip_network()` casts an object to `ip_network`.
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
#' An alternative constructor accepts an [`ip_address`] vector and an
#' integer vector containing the network address and prefix length, respectively.
#'
#' When casting an `ip_network` object back to a character vector using
#' `as.character()`, IPv6 addresses are reduced to their compressed representation.
#'
#' When comparing and sorting `ip_network` vectors, the network address is
#' compared before the prefix length.
#'
#' @param ... Included for S3 generic consistency
#' @param x
#' * For `ip_network()`: A character vector of IP networks, in CIDR notation
#'   (IPv4 or IPv6)
#' * For `is_ip_network()`: An object to test
#' * For `as_ip_network()`: An object to cast
#' * For `as.character()`: An `ip_network` vector
#' @param address An [`ip_address`] vector
#' @param prefix_length An integer vector
#' @param strict If `TRUE` (the default) and the input has host bits set,
#'   then a warning is emitted and `NA` is returned. If `FALSE`, the
#'   host bits are set to zero and a valid IP network is returned. If you need
#'   to retain the host bits, consider using [ip_interface()] instead.
#' @return An S3 vector of class `ip_network`
#'
#' @examples
#' # construct from character vector
#' ip_network(c("192.168.0.0/24", "2001:db8::/48"))
#'
#' # validates inputs and replaces with NA
#' ip_network(c("192.168.0.0/33", "192.168.0.0"))
#'
#' # IP networks should not have any host bits set
#' ip_network("192.168.0.1/22")
#'
#' # but we can mask the host bits if desired
#' ip_network("192.168.0.1/22", strict = FALSE)
#'
#' # construct from address + prefix length
#' ip_network(ip_address("192.168.0.0"), 24L)
#'
#' # construct from address + netmask
#' ip_network(ip_address("192.168.0.0"), prefix_length(ip_address("255.255.255.0")))
#'
#' # construct from address + hostmask
#' ip_network(ip_address("192.168.0.0"), prefix_length(ip_address("0.0.0.255")))
#' @seealso
#' [prefix_length()], [network_address()], [netmask()], [hostmask()]
#'
#' `vignette("ipaddress-classes")`
#' @name ip_network
NULL


# Construction ------------------------------------------------------------

#' @rdname ip_network
#' @export
ip_network <- function(...) {
  UseMethod("ip_network")
}

#' @rdname ip_network
#' @export
ip_network.default <- function(x = character(), strict = TRUE, ...) {
  if (!is_bool(strict)) {
    abort("`strict` be must TRUE or FALSE")
  }

  wrap_parse_network(x, strict, FALSE)
}

#' @rdname ip_network
#' @export
ip_network.ip_address <- function(address, prefix_length, strict = TRUE, ...) {
  if (!is_integerish(prefix_length)) {
    abort("`prefix_length` must be an integer vector")
  }
  if (!is_bool(strict)) {
    abort("`strict` be must TRUE or FALSE")
  }

  # vector recycling
  args <- vec_recycle_common(address, prefix_length)
  address <- args[[1L]]
  prefix_length <- args[[2L]]

  wrap_construct_network_from_address(address, prefix_length, strict, FALSE)
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

#' @rdname ip_network
#' @export
is_ip_network <- function(x) inherits(x, "ip_network")


# Casting ------------------------------------------------------------

#' @rdname ip_network
#' @export
as_ip_network <- function(x) UseMethod("as_ip_network")

#' @rdname ip_network
#' @export
as_ip_network.character <- function(x) ip_network(x)

#' @rdname ip_network
#' @export
as_ip_network.ip_interface <- function(x) {
  ip_network(x, field(x, "prefix"), strict = FALSE)
}

#' @rdname ip_network
#' @export
as.character.ip_network <- function(x, ...) wrap_print_network(x)

#' @inheritParams format.ip_address
#' @rdname ip_network
#' @export
format.ip_network <- function(x, exploded = FALSE, ...) {
  wrap_print_network(x, exploded)
}


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_network <- function(x, ...) {
  compare_df <- wrap_compare_address(network_address(x))
  compare_df$prefix <- field(x, "prefix")
  compare_df
}


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_network <- function(x, ...) {
  "ip_netwk"
}
