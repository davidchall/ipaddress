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
    assertthat::is.scalar(x),
    assertthat::noNA(x),
    assertthat::is.count(size),
    assertthat::is.flag(replace),
    assertthat::noNA(replace)
  )

  if (!replace && size > num_addresses(x)) {
    stop("cannot take a sample larger than the network size when 'replace = FALSE'")
  }

  # if generating all addresses, use C++ for performance
  if (size >= num_addresses(x)) {
    return(sample(seq(x), size, replace))
  }

  # for small networks it's quicker to generate all addresses
  if (num_addresses(x) < 1e6) {
    return(sample(seq(x), size, replace))
  }

  n_bits_to_sample <- max_prefix_length(x) - prefix_length(x)
  sample_func <- ifelse(is_ipv6(x), sample_ipv6_character, sample_ipv4_character)

  result <- do.call(sample_func, list(size, n_bits_to_sample))

  if (!replace) {
    unique <- FALSE
    while (!unique) {
      dupes <- duplicated(result)
      n_dupes <- sum(dupes)
      if (n_dupes == 0) {
        unique <- TRUE
      } else {
        result[dupes] <- do.call(sample_func, list(sum(dupes), n_bits_to_sample))
      }
    }
  }

  rep(network_address(x), size) | ip_address(result)
}

sample_ipv4_character <- function(size, n_bits_to_sample) {
  sample_octet <- function(i) {
    n_bits_octet <- pmin(pmax(n_bits_to_sample - 8L * i, 0L), 8L)
    range_octet <- 0L:(2L^n_bits_octet - 1L)
    sample(range_octet, size, replace = TRUE)
  }

  Reduce(function(x, y) paste(x, y, sep = "."), Map(sample_octet, 3:0))
}

sample_ipv6_character <- function(size, n_bits_to_sample) {
  sample_nibble <- function(i) {
    n_bits_nibble <- pmin(pmax(n_bits_to_sample - 4L * i, 0L), 4L)
    max_decimal <- 2 ^ n_bits_nibble - 1
    range_nibble <- c(0:pmin(max_decimal, 9), letters[0:(pmax(max_decimal - 9, 0))])
    sample(range_nibble, size, replace = TRUE)
  }

  sample_hextet <- function(i) {
    i_nibbles <- seq.int(4 * i + 3, by = -1, length.out = 4)
    Reduce(paste0, Map(sample_nibble, i_nibbles))
  }

  Reduce(function(x, y) paste(x, y, sep = ":"), Map(sample_hextet, 7:0))
}
