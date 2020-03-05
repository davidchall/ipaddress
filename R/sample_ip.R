#' Randomly sample addresses from a network
#'
#' @param space The address space to sample ("IPv4" or "IPv6")
#' @param x An \code{\link{ip_network}} scalar
#' @param size Integer specifying the number of addresses to return
#' @param replace Should sampling be with replacement?
#' @param ... Arguments to be passed to other methods
#' @return An \code{\link{ip_address}} vector
#'
#' @seealso
#' Use [seq.ip_network()] to generate _all_ addresses in a network.
#'
#' @examples
#' set.seed(2020)
#' sample_ip("IPv4", 5)
#'
#' sample_ip("IPv6", 5)
#'
#' sample_ip(ip_network("192.168.0.0/16"), 5)
#'
#' sample_ip(ip_network("2001:db8::/48"), 5)
#' @name sample_ip
#' @export
sample_ip <- function(...) {
  UseMethod("sample_ip")
}

#' @rdname sample_ip
#' @export
sample_ip.default <- function(space = c("IPv4", "IPv6"), size, replace = FALSE, ...) {
  if (space == "IPv4") {
    sample_ip(ip_network("0.0.0.0/0"), size, replace)
  } else if (space == "IPv6") {
    sample_ip(ip_network("::/0"), size, replace)
  } else {
    stop("`space` must be either 'IPv4' or 'IPv6")
  }
}

#' @rdname sample_ip
#' @export
sample_ip.ip_network <- function(x, size, replace = FALSE, ...) {
  assertthat::assert_that(
    assertthat::is.scalar(x),
    assertthat::is.count(size),
    assertthat::is.flag(replace),
    assertthat::noNA(replace)
  )

  if (!replace && size > num_addresses(x)) {
    stop("cannot take a sample larger than the network size when 'replace = FALSE'")
  }

  # if generating all addresses, we can use C++ for performance boost
  if (!replace && size == num_addresses(x)) {
    return(sample(seq(x), size, replace))
  }

  # for small networks it's quicker to generate all addresses
  if (num_addresses(x) < 1000L) {
    return(sample(seq(x), size, replace))
  }

  n_bits_to_sample <- max_prefix_length(x) - prefix_length(x)
  sample_func <- ifelse(is_ipv6(x), sample_ipv6, sample_ipv4)

  if (replace) {
    result <- do.call(sample_func, list(n_bits_to_sample, size))
  } else {
    result <- do.call(sample_func, list(n_bits_to_sample, size))

    unique <- FALSE
    while (!unique) {
      dupes <- duplicated(result)
      n_dupes <- sum(dupes)
      if (n_dupes == 0) {
        unique <- TRUE
      } else {
        result[dupes] <- do.call(sample_func, list(n_bits_to_sample, sum(dupes)))
      }
    }
  }

  result
}

sample_ipv4 <- function(n_bits_to_sample, size) {
  sample_octet <- function(i) {
    n_bits_octet <- pmin(pmax(n_bits_to_sample - 8L * i, 0L), 8L)
    range_octet <- 0L:(2L^n_bits_octet - 1L)
    sample(range_octet, size, replace = TRUE)
  }

  ip <- Reduce(function(x, y) paste(x, y, sep = "."), Map(sample_octet, 3:0))

  ip_address(ip)
}

sample_ipv6 <- function(n_bits_to_sample, size) {
  sample_nibble <- function(i) {
    n_bits_nibble <- pmin(pmax(n_bits_to_sample - 4L * i, 0L), 4L)
    max_decimal <- 2^n_bits_nibble - 1
    range_nibble <- c(0:pmin(max_decimal, 9), letters[0:(pmax(max_decimal - 9, 0))])
    sample(range_nibble, size, replace = TRUE)
  }

  sample_hextet <- function(i) {
    i_nibbles <- seq.int(4*i+3, by = -1, length.out = 4)
    Reduce(paste0, Map(sample_nibble, i_nibbles))
  }

  ip <- Reduce(function(x, y) paste(x, y, sep = ":"), Map(sample_hextet, 7:0))

  ip_address(ip)
}
