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
#' @param strict If `strict = TRUE` (the default) and the input has host bits set,
#'   then a warning is emitted and `NA` is returned. If `FALSE`, the
#'   host bits are set to zero and a valid IP network is returned.
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
#' ip_network(c("192.168.0.0/24", "192.168.0.0/33", "1.2.3.4"))
#'
#' # IP networks should not have any host bits set
#' ip_network("192.168.0.1/22")
#'
#' ip_network("192.168.0.1/22", strict = FALSE)
#'
#' @rdname ip_network
#' @export
ip_network <- function(...) {
  UseMethod("ip_network")
}

#' @rdname ip_network
#' @export
ip_network.default <- function(ip = character(), strict = TRUE, ...) {
  assertthat::assert_that(
    assertthat::is.flag(strict),
    assertthat::noNA(strict)
  )

  y <- parse_network_wrapper(ip, strict)

  new_ip_network(
    y$address1, y$address2, y$address3, y$address4,
    y$prefix,
    y$is_ipv6
  )
}

#' @rdname ip_network
#' @export
ip_network.ip_address <- function(address, prefix_length, strict = TRUE, ...) {
  assertthat::assert_that(
    assertthat::is.flag(strict),
    assertthat::noNA(strict),
    is.integer(prefix_length),
    length(address) == length(prefix_length)
  )

  y <- construct_network_wrapper(address, prefix_length, strict)

  new_ip_network(
    y$address1, y$address2, y$address3, y$address4,
    y$prefix,
    y$is_ipv6
  )
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
vec_proxy_compare.ip_network <- function(x, ...) {
  compare_address_wrapper(network_address(x))
}


# Other ------------------------------------------------------------

#' @export
vec_ptype_abbr.ip_network <- function(x, ...) {
  "ip_netw"
}


#' Basic information about a network
#'
#' @param x An \code{\link{ip_network}} vector
#' @return
#' * `prefix_length()` returns an integer vector
#' * `num_addresses()` returns a numeric vector
#' * `network_address()` and `broadcast_address()` return an \code{\link{ip_address}} vector
#'
#' @examples
#' x <- ip_network(c("192.168.0.0/22", "2001:db00::0/26"))
#'
#' prefix_length(x)
#'
#' num_addresses(x)
#'
#' network_address(x)
#'
#' broadcast_address(x)
#'
#' @seealso
#' The prefix length can equivalently be represented by the [netmask()] or [hostmask()].
#'
#' @name network_info
NULL

#' `prefix_length()`
#'
#' `prefix_length()` gives the prefix length
#'
#' @rdname network_info
#' @export
prefix_length <- function(x) {
  assertthat::assert_that(is_ip_network(x))
  field(x, "prefix")
}

#' `num_addresses()`
#'
#' `num_addresses()` gives the total number of addresses
#'
#' @rdname network_info
#' @export
num_addresses <- function(x) {
  assertthat::assert_that(is_ip_network(x))

  2L ^ (ifelse(field(x, "is_ipv6"), 128L, 32L) - field(x, "prefix"))
}

#' `network_address()`
#'
#' `network_address()` gives the first address
#'
#' @rdname network_info
#' @export
network_address <- function(x) {
  assertthat::assert_that(is_ip_network(x))

  new_ip_address(
    field(x, "address1"),
    field(x, "address2"),
    field(x, "address3"),
    field(x, "address4"),
    field(x, "is_ipv6")
  )
}

#' `broadcast_address()`
#'
#' `broadcast_address()` gives the last address
#'
#' @details
#' The broadcast address is a special address at which any host connected
#' to the network can receive messages. That is, packets sent to this address
#' are received by all hosts on the network.
#' In IPv4, the last address of a network is the broadcast address.
#' Although IPv6 does not follow this approach to broadcast addresses, the
#' `broadcast_address()` function still returns the last address of the network.
#'
#' @rdname network_info
#' @export
broadcast_address <- function(x) {
  assertthat::assert_that(is_ip_network(x))

  y <- broadcast_address_wrapper(x)

  new_ip_address(
    y$address1, y$address2, y$address3, y$address4,
    y$is_ipv6
  )
}
