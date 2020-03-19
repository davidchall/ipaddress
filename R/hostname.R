#' @export
as_hostname <- function(x) {
  assertthat::assert_that(is_ip_address(x))

  res <- translate_to_hostnames(x)
  if (all(lengths(res)) == 1L) {
    res <- unlist(res)
  }

  res
}
