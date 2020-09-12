#' Translate address to/from hostname
#'
#' @description
#' Perform reverse and forward DNS resolution.
#'
#' **Note:** These functions are significantly slower than others in the
#' ipaddress package.
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
#' @param x
#'  * For `ip_to_hostname()`: An [`ip_address`] vector
#'  * For `hostname_to_ip()`: A character vector of hostnames
#' @param multiple A logical scalar indicating if _all_ resolved endpoints are
#'   returned, or just the first endpoint (the default). This determines whether
#'   a vector or list of vectors is returned.
#'
#' @return
#' * For `ip_to_hostname()`: A character vector (`multiple = FALSE`) or
#'   a list of character vectors (`multiple = TRUE`)
#' * For `hostname_to_ip()`: A [`ip_address`] vector (`multiple = FALSE`) or
#'   a list of [`ip_address`] vectors (`multiple = TRUE`)
#'
#' @examples
#' \dontrun{
#' hostname_to_ip("r-project.org")
#'
#' ip_to_hostname(hostname_to_ip("r-project.org"))
#' }
#' @seealso
#' The base function `nsl()` provides forward DNS resolution to IPv4 addresses,
#' but only on Unix-like systems.
#' @export
ip_to_hostname <- function(x, multiple = FALSE) {
  if (!is_ip_address(x)) {
    abort("`x` must be an ip_address vector")
  }
  if (!is_bool(multiple)) {
    abort("`multiple` must be TRUE or FALSE")
  }
  if (is_offline()) {
    abort("DNS resolution requires an internet connection")
  }

  out <- wrap_encode_hostname(x)

  if (multiple) {
    out
  } else {
    pluck_first_of_each(out)
  }
}

#' @rdname ip_to_hostname
#' @export
hostname_to_ip <- function(x, multiple = FALSE) {
  if (!is_character(x)) {
    abort("`x` must be a character vector")
  }
  if (!is_bool(multiple)) {
    abort("`multiple` must be TRUE or FALSE")
  }
  if (is_offline()) {
    abort("DNS resolution requires an internet connection")
  }

  out <- wrap_decode_hostname(x)

  if (multiple) {
    out
  } else {
    pluck_first_of_each(out)
  }
}

is_offline <- function() {
  out <- suppressWarnings(wrap_decode_hostname("www.r-project.org"))
  out <- pluck_first_of_each(out)
  is.na(out)
}

pluck_first_of_each <- function(x) {
  do.call(Map, c(c, x))[[1]]
}
