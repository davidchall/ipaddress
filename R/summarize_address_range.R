#' List constituent networks of an address range
#'
#' @description
#' Given an address range, this returns the list of constituent networks.
#'
#' If you know the address range matches the boundaries of a single network, it
#' might be preferable to use [common_network()]. This returns an [`ip_network`]
#' vector instead of a list of [`ip_network`] vectors.
#'
#' @param address1 An [`ip_address`] vector
#' @param address2 An [`ip_address`] vector
#' @return A list of [`ip_network`] vectors
#'
#' @examples
#' # address range matches network boundaries
#' summarize_address_range(ip_address("192.168.0.0"), ip_address("192.168.0.15"))
#'
#' # address range does not match network boundaries
#' summarize_address_range(ip_address("192.167.255.255"), ip_address("192.168.0.16"))
#' @seealso [common_network()]
#' @export
summarize_address_range <- function(address1, address2) {
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

  wrap_summarize_address_range(address1, address2)
}
