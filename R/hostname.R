#' Represent address as hostname
#'
#' @param ip An \code{\link{ip_address}} vector
#' @param host A character vector of hostnames
#' @param multiple A logical scalar indicating if _all_ resolved endpoints are
#'   returned, or just the first endpoint (the default). This determines whether
#'   a vector or list of vectors is returned.
#' @return
#' * `as_hostname()` returns a character vector or a list of character vectors
#'   (depending upon the `multiple` argument)
#' * `from_hostname()` returns a \code{\link{ip_address}} vector or a list of
#'   \code{\link{ip_address}} vectors (depending upon the `multiple` argument)
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
  assertthat::assert_that(
    is_ip_address(ip),
    assertthat::is.flag(multiple),
    assertthat::noNA(multiple)
  )

  res <- translate_to_hostnames(ip)

  if (multiple) {
    res
  } else {
    pluck_first_of_each(res)
  }
}

#' @rdname hostname
#' @export
from_hostname <- function(host, multiple = FALSE) {
  assertthat::assert_that(
    is.character(host),
    assertthat::is.flag(multiple),
    assertthat::noNA(multiple)
  )

  res <- translate_from_hostname(host)

  if (multiple) {
    res
  } else {
    pluck_first_of_each(res)
  }
}

pluck_first_of_each <- function(x) {
  do.call(Map, c(c, x))[[1]]
}
