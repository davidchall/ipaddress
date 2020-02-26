#' @importFrom methods setOldClass
methods::setOldClass(c("ip_network", "vctrs_vctr"))

#' Class for storing IP networks
#'
#' @details
#' An IP network corresponds to a range of contiguous IP addresses
#' (also known as an IP block). CIDR notation represents an
#' IP network as the routing prefix address (which denotes the start
#' of the range) and the prefix length (which indicates the size of
#' the range) separated by a forward slash. For example, "192.168.100.0/22"
#' represents addresses from "192.168.100.0" to "192.168.103.255".
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
#' When casting an `ip_network` object back to a character vector using
#' `as.character()`, IPv6 addresses are reduced to their compressed representation.
#'
#' @seealso \code{\link{prefix_length}}, \code{\link{netmask}},
#'   \code{\link{hostmask}}
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
#' @param strict If `strict = TRUE` (the default) and the input has host bits set,
#'   then a warning is emitted and `NA` is returned. If `FALSE`, the
#'   host bits are set to zero and a valid IP network is returned.
#' @return An `ip_network` vector
#'
#' @examples
#' # supports IPv4 and IPv6 simultaneously
#' ip_network(c("92.0.2.0/24", "192.168.100.0/22", "2001:db8::/48"))
#'
#' # validates inputs and replaces with NA
#' ip_network(c("192.168.0.0/24", "192.168.0.0/33", "1.2.3.4"))
#'
#' # IP networks should not have any host bits set
#' ip_network("192.168.0.1/22")
#'
#' ip_network("192.168.0.1/22", strict = FALSE)
#'
#' @rdname ip_network
#' @export
ip_network <- function(ip = character(), strict = TRUE) {
  assertthat::is.flag(strict)
  y <- parse_network_wrapper(ip, strict)

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

#' @rdname ip_network
#' @export
as.character.ip_network <- function(x, ...) vec_cast(x, character())


# Comparison ------------------------------------------------------------

#' @export
vec_proxy_compare.ip_network <- function(x, ...) compare_network_wrapper(x)


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_network <- function(x, ...) {
  "ip_netw"
}
