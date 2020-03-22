#' Translate address to/from hostname
#'
#' @description
#' `as_hostname()` performs reverse DNS resolution (translating IP addresses
#' to hostnames)
#'
#' `from_hostname()` performs forward DNS resolution (translating hostnames to
#' IP addresses)
#'
#' @details
#' These functions require an internet connection. Before processing the input
#' vector, we first check that a known hostname can be resolved. If this fails,
#' an error is raised.
#'
#' If DNS lookup cannot resolve an input, then `NA` is returned for that input.
#' If an error occurs during DNS lookup, then a warning is emitted and `NA` is
#' returned for that input.
#'
#' DNS resolution performs a many-to-many mapping between IP addresses and
#' hostnames. For this reason, these two functions can potentially return
#' multiple values for each element of the input vector. The `multiple` argument
#' control whether _all_ values are returned (a vector for each input), or
#' just the first value (a scalar for each input).
#'
#' @param ip An \code{\link{ip_address}} vector
#' @param host A character vector of hostnames
#' @param multiple A logical scalar indicating if _all_ resolved endpoints are
#'   returned, or just the first endpoint (the default). This determines whether
#'   a vector or list of vectors is returned.
#'
#' @return
#' * `as_hostname()` returns a character vector or a list of character vectors
#'   (depending upon the `multiple` argument)
#' * `from_hostname()` returns a \code{\link{ip_address}} vector or a list of
#'   \code{\link{ip_address}} vectors (depending upon the `multiple` argument)
#'
#' @examples
#' from_hostname("r-project.org")
#'
#' as_hostname(from_hostname("r-project.org"))
#' @seealso
#' The base function [nsl()] provides forward DNS resolution to IPv4 addresses,
#' but only on Unix-like systems.
#' @name hostname
NULL

#' @rdname hostname
#' @export
as_hostname <- function(ip, multiple = FALSE) {
  if (!is_ip_address(ip)) {
    abort("'ip' must be an ip_address vector")
  }
  if (!is_bool(multiple)) {
    abort("'multiple' must be TRUE or FALSE")
  }
  if (is_offline()) {
    abort("DNS resolution requires an internet connection")
  }

  res <- wrap_encode_hostname(ip)

  if (multiple) {
    res
  } else {
    pluck_first_of_each(res)
  }
}

#' @rdname hostname
#' @export
from_hostname <- function(host, multiple = FALSE) {
  if (!is_character(host)) {
    abort("'host' must be a character vector")
  }
  if (!is_bool(multiple)) {
    abort("'multiple' must be TRUE or FALSE")
  }
  if (is_offline()) {
    abort("DNS resolution requires an internet connection")
  }

  res <- wrap_decode_hostname(host)

  if (multiple) {
    res
  } else {
    pluck_first_of_each(res)
  }
}

is_offline <- function() {
  res <- suppressWarnings(wrap_decode_hostname("www.r-project.org"))
  res <- pluck_first_of_each(res)
  is.na(res)
}

pluck_first_of_each <- function(x) {
  do.call(Map, c(c, x))[[1]]
}
