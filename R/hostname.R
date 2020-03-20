#' Represent address as hostname
#'
#' @param ip An \code{\link{ip_address}} vector
#' @param host A character vector of hostnames
#' @return
#' * `as_hostname()` returns a list of character vectors
#' * `from_hostname()` returns a list of \code{\link{ip_address}} vectors
#'
#' @seealso [nsl()]
#' @name hostname
NULL

#' @rdname hostname
#' @export
as_hostname <- function(ip, simplify = TRUE) {
  assertthat::assert_that(is_ip_address(ip))

  res <- translate_to_hostnames(ip)

  if (simplify && all(lengths(res)) == 1L) {
    res <- unlist(res)
  }

  res
}

#' @rdname hostname
#' @export
from_hostname <- function(host, simplify = TRUE) {
  assertthat::assert_that(is.character(host))

  res <- translate_from_hostname(host)

  if (simplify && all(lengths(res)) == 1L) {
    res <- do.call(Map, c(c, res))[[1]]
  }

  res
}
