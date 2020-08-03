#' Find the common network of two addresses
#'
#' @description
#' Returns the smallest network that contains both addresses.
#'
#' This is a simple way to construct a network from its first and last addresses.
#' However, if the addresses do not correspond to network boundaries, then the
#' returned network will extend beyond their address range.
#'
#' @param address1 An [`ip_address`] vector
#' @param address2 An [`ip_address`] vector
#' @return An [`ip_network`] vector
#'
#' @examples
#' first <- ip_address(c("192.168.0.0", "224.0.0.0"))
#' last <- ip_address(c("192.168.0.15", "239.255.255.255"))
#'
#' common_network(first, last)
#' @export
common_network <- function(address1, address2) {
  if (!is_ip_address(address1)) {
    abort("'address1' must be an ip_address vector")
  }
  if (!is_ip_address(address2)) {
    abort("'address2' must be an ip_address vector")
  }

  # vector recycling
  args <- vec_recycle_common(address1, address2)
  address1 <- args[[1L]]
  address2 <- args[[2L]]

  wrap_smallest_common_network(address1, address2)
}
