#' @export
sample_ip <- function(x, size, replace = FALSE) {
  assertthat::assert_that(
    is_ip_network(x),
    assertthat::is.scalar(x),
    assertthat::is.count(size),
    assertthat::is.flag(replace),
    assertthat::noNA(replace)
  )

  if (!replace && size > num_addresses(x)) {
    stop("cannot take a sample larger than the population when 'replace = FALSE'")
  }
  if (!replace && size == num_addresses(x)) {
    return(sample(seq(x)))
  }

  n_bits_to_sample <- max_prefix_length(x) - prefix_length(x)

  sample_ipv4(n_bits_to_sample, size)
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
