#' Traverse the network hierarchy
#'
#' These functions step up and down the network hierarchy. `supernet()` returns
#' the supernetwork containing the given network. `subnets()` returns the list
#' of subnetworks which join to make the given network.
#'
#' @param x An [`ip_network`] vector
#' @param new_prefix An integer vector indicating the desired prefix length.
#'   By default, this steps a single level through the hierarchy.
#' @return
#'  * `supernet()`: An [`ip_network`] vector
#'  * `subnets()`: A list of [`ip_network`] vectors
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
  check_network(x)
  check_integer(new_prefix)
  check_all(prefix_length(x) > 0, "x", "must have a supernetwork")
  check_all(new_prefix >= 0, "new_prefix", "must be positive")
  check_all(new_prefix < prefix_length(x), "new_prefix", "must be less than {.code prefix_length(x)}")

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
  check_network(x)
  check_integer(new_prefix)
  check_all(new_prefix >= 0, "new_prefix", "must be positive")
  check_all(prefix_length(x) < max_prefix_length(x), "x", "must have a subnetwork")
  check_all(new_prefix > prefix_length(x), "new_prefix", "must be greater than {.code prefix_length(x)}")
  check_all(new_prefix <= max_prefix_length(x), "new_prefix", "must be less than {.code max_prefix_length(x)}")

  if (any(new_prefix - prefix_length(x) > 30L, na.rm = TRUE)) {
    abort("Too many subnets")
  }

  # vector recycling
  args <- vec_recycle_common(x, new_prefix)
  x <- args[[1L]]
  new_prefix <- args[[2L]]

  as_list_of(wrap_subnets(x, new_prefix), .ptype = ip_network())
}
