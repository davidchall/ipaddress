#' Collapse contiguous and overlapping networks
#'
#' Given a vector of networks, this returns the minimal set of networks required
#' to represent the same range of addresses.
#'
#' @param network An [`ip_network`] vector
#' @return An [`ip_network`] vector (potentially shorter than the input)
#' @examples
#' collapse_networks(ip_network(c("192.168.0.0/24", "192.168.1.0/24")))
#' @export
collapse_networks <- function(network) {
  if (!is_ip_network(network)) {
    abort("`network` must be an ip_network vector")
  }

  wrap_collapse_networks(network)
}


#' Remove networks from others
#'
#' Returns the minimal set of networks
#'
#' @param include An [`ip_network`] vector
#' @param exclude An [`ip_network`] vector
#' @return An [`ip_network`] vector
#' @export
exclude_networks <- function(include, exclude) {
  if (!is_ip_network(include)) {
    abort("`include` must be an ip_network vector")
  }
  if (!is_ip_network(exclude)) {
    abort("`exclude` must be an ip_network vector")
  }

  wrap_exclude_networks(include, exclude)
}
