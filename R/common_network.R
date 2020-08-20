#' Find the common network of two addresses
#'
#' @description
#' Returns the smallest network that contains both addresses.
#'
#' This can construct a network from its first and last addresses. However, if
#' the address range does not match the network boundaries, then the result
#' extends beyond the original address range. Use [summarize_address_range()]
#' to receive a list of networks that exactly match the address range.
#'
#' @param address1 An [`ip_address`] vector
#' @param address2 An [`ip_address`] vector
#' @return An [`ip_network`] vector
#'
#' @examples
#' # address range matches network boundaries
#' common_network(ip_address("192.168.0.0"), ip_address("192.168.0.15"))
#'
#' # address range does not match network boundaries
#' common_network(ip_address("192.167.255.255"), ip_address("192.168.0.16"))
#' @seealso [summarize_address_range()]
#' @export
common_network <- function(address1, address2) {
  if (!is_ip_address(address1)) {
    abort("`address1` must be an ip_address vector")
  }
  if (!is_ip_address(address2)) {
    abort("`address2` must be an ip_address vector")
  }

  # vector recycling
  args <- vec_recycle_common(address1, address2)
  address1 <- args[[1L]]
  address2 <- args[[2L]]

  wrap_smallest_common_network(address1, address2)
}
