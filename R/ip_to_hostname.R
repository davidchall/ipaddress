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
#' hostnames. For this reason, there are two versions of each function. The
#' regular version returns just the first value and the `_all()` suffix version
#' returns all values.
#'
#' @param x
#'  * For `ip_to_hostname()`: An [`ip_address`] vector
#'  * For `hostname_to_ip()`: A character vector of hostnames
#'
#' @return
#' * For `ip_to_hostname()`: A character vector
#' * For `ip_to_hostname_all()`: A list of character vectors
#' * For `hostname_to_ip()`: An [`ip_address`] vector
#' * For `hostname_to_ip_all()`: A list of [`ip_address`] vectors
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
ip_to_hostname <- function(x) {
  pluck_first_of_each(ip_to_hostname_all(x))
}

#' @rdname ip_to_hostname
#' @export
ip_to_hostname_all <- function(x) {
  if (!is_ip_address(x)) {
    abort("`x` must be an ip_address vector")
  }
  if (is_offline()) {
    abort("DNS resolution requires an internet connection")
  }

  as_list_of(wrap_encode_hostname(x), .ptype = character())
}

#' @rdname ip_to_hostname
#' @export
hostname_to_ip <- function(x) {
  pluck_first_of_each(hostname_to_ip_all(x))
}

#' @rdname ip_to_hostname
#' @export
hostname_to_ip_all <- function(x) {
  if (!is_character(x)) {
    abort("`x` must be a character vector")
  }
  if (is_offline()) {
    abort("DNS resolution requires an internet connection")
  }

  as_list_of(wrap_decode_hostname(x), .ptype = ip_address())
}

is_offline <- function() {
  out <- suppressWarnings(wrap_decode_hostname("www.r-project.org"))
  out <- pluck_first_of_each(out)
  is.na(out)
}

pluck_first_of_each <- function(x) {
  do.call(Map, c(c, x))[[1]]
}
