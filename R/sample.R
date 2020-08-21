#' Sample random addresses
#'
#' `sample_ipv4()` and `sample_ipv6()` sample from the entire address space;
#' `sample_network()` samples from a specific network.
#'
#' @param x An [`ip_network`] scalar
#' @param size Integer specifying the number of addresses to return
#' @param replace Should sampling be with replacement?
#' @return An [`ip_address`] vector
#'
#' @seealso
#' Use [seq.ip_network()] to generate _all_ addresses in a network.
#'
#' @examples
#' sample_ipv4(5)
#'
#' sample_ipv6(5)
#'
#' sample_network(ip_network("192.168.0.0/16"), 5)
#'
#' sample_network(ip_network("2001:db8::/48"), 5)
#' @name sample
NULL

#' @rdname sample
#' @export
sample_ipv4 <- function(size, replace = FALSE) {
  sample_network(ip_network("0.0.0.0/0"), size, replace)
}

#' @rdname sample
#' @export
sample_ipv6 <- function(size, replace = FALSE) {
  sample_network(ip_network("::/0"), size, replace)
}

#' @rdname sample
#' @export
sample_network <- function(x, size, replace = FALSE) {
  if (!(is_ip_network(x) && length(x) == 1) || is.na(x)) {
    abort("`x` must be an ip_network scalar")
  }
  if (!(is_scalar_integerish(size) && size > 0)) {
    abort("`size` must be a positive integer scalar")
  }
  if (size >= 2^31) {
    abort("`size` must be less than 2^31")
  }
  if (!is_bool(replace)) {
    abort("`replace` must be TRUE or FALSE")
  }
  if (!replace && size > num_addresses(x)) {
    abort("cannot take a sample larger than the network size when `replace = FALSE`")
  }

  # in some cases it's quicker to generate all addresses
  if (size >= num_addresses(x) || num_addresses(x) < 1e4) {
    return(sample(seq(x), size, replace))
  }

  result <- wrap_sample_network(x, size)

  if (!replace) {
    unique <- FALSE
    while (!unique) {
      dupes <- duplicated(result)
      n_dupes <- sum(dupes)
      if (n_dupes == 0) {
        unique <- TRUE
      } else {
        result[dupes] <- wrap_sample_network(x, sum(dupes))
      }
    }
  }

  result
}
