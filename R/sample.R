#' Sample random addresses
#'
#' `sample_ipv4()` and `sample_ipv6()` sample from the entire address space;
#' `sample_network()` samples from a specific network.
#'
#' @param x An \code{\link{ip_network}} scalar
#' @param size Integer specifying the number of addresses to return
#' @param replace Should sampling be with replacement?
#' @return An \code{\link{ip_address}} vector
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
  assertthat::assert_that(
    is_ip_network(x),
    assertthat::is.scalar(x),
    assertthat::noNA(x),
    assertthat::is.count(size),
    assertthat::is.flag(replace),
    assertthat::noNA(replace)
  )

  if (!replace && size > num_addresses(x)) {
    stop("cannot take a sample larger than the network size when 'replace = FALSE'")
  }

  # in some cases it's quicker to generate all addresses
  if (size >= num_addresses(x) || num_addresses(x) < 1e4) {
    return(sample(seq(x), size, replace))
  }

  result <- sample_wrapper(x, size)

  if (!replace) {
    unique <- FALSE
    while (!unique) {
      dupes <- duplicated(result)
      n_dupes <- sum(dupes)
      if (n_dupes == 0) {
        unique <- TRUE
      } else {
        result[dupes] <- sample_wrapper(x, sum(dupes))
      }
    }
  }

  result
}
