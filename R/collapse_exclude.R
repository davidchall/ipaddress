#' Collapse contiguous and overlapping networks
#'
#' Given a vector of networks, this returns the minimal set of networks required
#' to represent the same range of addresses.
#'
#' @param network An [`ip_network`] vector
#' @return An [`ip_network`] vector (potentially shorter than the input)
#'
#' @examples
#' collapse_networks(ip_network(c("192.168.0.0/24", "192.168.1.0/24")))
#' @seealso [exclude_networks()]
#' @export
collapse_networks <- function(network) {
  if (!is_ip_network(network)) {
    abort("`network` must be an ip_network vector")
  }

  wrap_collapse_networks(network)
}


#' Remove networks from others
#'
#' `exclude_networks()` takes lists of networks to include and exclude. It then
#' calculates the address ranges that are included but not excluded (similar to
#' [setdiff()]), and finally returns the minimal set of networks needed to
#' describe the remaining address ranges.
#'
#' @param include An [`ip_network`] vector
#' @param exclude An [`ip_network`] vector
#' @return An [`ip_network`] vector
#'
#' @examples
#' exclude_networks(ip_network('192.0.2.0/28'), ip_network('192.0.2.1/32'))
#'
#' exclude_networks(ip_network('192.0.2.0/28'), ip_network('192.0.2.15/32'))
#' @seealso [collapse_networks()], [setdiff()]
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
