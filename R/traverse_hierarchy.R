#' Traverse the network hierarchy
#'
#' These functions step up and down the network hierarchy. `supernet()` returns
#' the supernetwork containing the given network. `subnets()` returns the list
#' of subnetworks which join to make the given network.
#'
#' @param x
#'  * For `supernet()`: An [`ip_network`] vector
#'  * For `subnets()`: An [`ip_network`] scalar
#' @param new_prefix An integer vector indicating the desired prefix length.
#'   By default, this steps a single level through the hierarchy.
#' @return An [`ip_network`] vector
#'
#' @details
#' The ipaddress package does not support \link[base:LongVectors]{long vectors}
#' (i.e. vectors with more than 2^31 - 1 elements). The limits the number of
#' subnetworks that `subnets()` can return. However, you might find that machine
#' memory imposes stricter limitations.
#'
#' @examples
#' supernet(ip_network("192.168.0.0/24"))
#'
#' supernet(ip_network("192.168.0.0/24"), new_prefix = 10L)
#'
#' subnets(ip_network("192.168.0.0/24"))
#'
#' subnets(ip_network("192.168.0.0/24"), new_prefix = 27L)
#' @seealso
#' Use [seq.ip_network()] to list the addresses within a network.
#'
#' Use [is_supernet()] and [is_subnet()] to check if one network is contained
#' within another.
#' @name traverse_hierarchy
NULL

#' @rdname traverse_hierarchy
#' @export
supernet <- function(x, new_prefix = prefix_length(x) - 1L) {
  if (!is_ip_network(x)) {
    abort("`x` must be an ip_network vector")
  }
  if (!is_integerish(new_prefix)) {
    abort("`new_prefix` must be an integer vector")
  }
  if (any(new_prefix < 0, na.rm = TRUE)) {
    abort("`new_prefix` cannot be negative")
  }
  if (any(new_prefix > max_prefix_length(x), na.rm = TRUE)) {
    abort("`new_prefix` cannot be greater than maximum (32 for IPv4, 128 for IPv6)")
  }
  if (any(new_prefix >= prefix_length(x), na.rm = TRUE)) {
    abort("`new_prefix` must be shorter than current prefix length")
  }

  # vector recycling
  args <- vec_recycle_common(x, new_prefix)
  x <- args[[1L]]
  new_prefix <- args[[2L]]

  supernet_addr <- network_address(x) & netmask(new_prefix, is_ipv6(x))

  new_ip_network(
    field(supernet_addr, "address1"),
    field(supernet_addr, "address2"),
    field(supernet_addr, "address3"),
    field(supernet_addr, "address4"),
    new_prefix,
    field(supernet_addr, "is_ipv6")
  )
}

#' @rdname traverse_hierarchy
#' @export
subnets <- function(x, new_prefix = prefix_length(x) + 1L) {
  if (!(is_ip_network(x) && length(x) == 1)) {
    abort("`x` must be an ip_network scalar")
  }
  if (!is_scalar_integerish(new_prefix)) {
    abort("`new_prefix` must be an integer scalar")
  }
  if (any(new_prefix < 0, na.rm = TRUE)) {
    abort("`new_prefix` cannot be negative")
  }
  if (any(new_prefix > max_prefix_length(x), na.rm = TRUE)) {
    abort("`new_prefix` cannot be greater than maximum (32 for IPv4, 128 for IPv6)")
  }
  if (any(new_prefix <= prefix_length(x), na.rm = TRUE)) {
    abort("`new_prefix` must be longer than current prefix length")
  }
  if (any(new_prefix - prefix_length(x) > 30L, na.rm = TRUE)) {
    abort("Too many subnets")
  }

  wrap_subnets(x, new_prefix)
}
