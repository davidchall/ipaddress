#' Reverse DNS pointer
#'
#' Returns the PTR record used by reverse DNS.
#'
#' @details
#' These documents describe reverse DNS lookup in more detail:
#'
#' * **IPv4:** [RFC-1035 Section 3.5](https://www.rfc-editor.org/rfc/rfc1035)
#' * **IPv6:** [RFC-3596 Section 2.5](https://www.rfc-editor.org/rfc/rfc3596)
#'
#' @param x An [`ip_address`] vector
#' @return A character vector
#'
#' @examples
#' reverse_pointer(ip_address("127.0.0.1"))
#'
#' reverse_pointer(ip_address("2001:db8::1"))
#' @export
reverse_pointer <- function(x) {
  check_address(x)
  wrap_reverse_pointer(x)
}
