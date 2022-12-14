#' Sample random addresses
#'
#' `sample_ipv4()` and `sample_ipv6()` sample from the entire address space;
#' `sample_network()` samples from a specific network.
#'
#' @param x An [`ip_network`] scalar
#' @param size Integer specifying the number of addresses to return
#' @param replace Should sampling be with replacement? (default: `FALSE`)
#' @inheritParams rlang::args_dots_empty
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
sample_ipv4 <- function(size, ..., replace = FALSE) {
  sample_network(ip_network("0.0.0.0/0"), size, ..., replace = replace)
}

#' @rdname sample
#' @export
sample_ipv6 <- function(size, ..., replace = FALSE) {
  sample_network(ip_network("::/0"), size, ..., replace = replace)
}

#' @rdname sample
#' @export
sample_network <- function(x, size, ..., replace = FALSE) {
  check_dots_empty()
  check_network(x)
  check_scalar(x)
  check_integer(size)
  check_scalar(size)
  check_all(size > 0, "size", "must be positive non-zero integer")
  check_bool(replace)

  if (is.na(x)) {
    cli::cli_abort("{.arg x} must not be NA")
  }
  if (size >= 2^31) {
    cli::cli_abort(c(
      "{.arg size} must be less than 2^31",
      "x" = "Requested size: {.val {size}}",
      "i" = "Maximum size: {.val {2^31}}"
    ))
  }
  if (!replace && size > num_addresses(x)) {
    cli::cli_abort(c(
      "{.arg size} must not be greater than the network size when {.code replace = FALSE}",
      "x" = "Requested size: {.val {size}}",
      "i" = "Network size: {.val {num_addresses(x)}}"
    ))
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
