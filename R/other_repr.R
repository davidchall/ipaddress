#' Represent address as integer
#'
#' @description
#' Encode or decode an [`ip_address`] as an integer.
#'
#' **Note:** The result is a character vector (see below for why). This can be
#' converted using [as.numeric()] for IPv4 addresses.
#'
#' @details
#' It is common to represent an IP address as an integer, by reinterpreting
#' the bit sequence as a big-endian unsigned integer. This means IPv4 and IPv6
#' addresses can be represented by 32-bit and 128-bit unsigned integers.
#' In this way, the IPv4 addresses `0.0.0.0` and `255.255.255.255` would be
#' represented as 0 and 4,294,967,295.
#'
#' @section Why is a character vector returned?:
#' Base R provides two data types that can store integers: [`integer`] and
#' [`double`] (also known as [`numeric`]). The former is a fixed-point data
#' format (32-bit) and the latter is a floating-point data format (64-bit).
#' Both types are signed, and R does not offer unsigned variants.
#'
#' For the purpose of storing IP addresses as integers, we need to be able to
#' store a large range of positive integers without losing integer precision.
#' Under these circumstances, the [`integer`] type can store integers up to
#' 2^31 - 1 and the [`double`] type can store integers up to 2^53. However,
#' for IPv4 and IPv6 addresses we need to store integers up to 2^32 - 1 and
#' 2^128 - 1, respectively. This means an IPv4 address can be stored in a
#' [`double`], but an IPv6 address cannot be stored in either R data type.
#'
#' Although the integer representation of an IPv6 address cannot be stored in
#' a numeric R data type, it can be stored as a character string instead.
#' This allows the integer to be written to disk or used by other software that
#' _does_ support 128-bit unsigned integers. To treat IPv4 and IPv6 equally,
#' `ip_to_integer()` will always return a [`character`] vector. With IPv4
#' addresses, this output can be converted to a [`double`] vector using
#' [as.double()] or [as.numeric()]. With IPv6 addresses, this conversion loses
#' the distinction between individual addresses because integer precision is lost.
#'
#' @param x
#'  * For `ip_to_integer()`: An [`ip_address`] vector
#'  * For `integer_to_ip()`: A character vector
#' @param base A string choosing the numeric base of the output. Choices are
#'   decimal (`"dec"`; the default), hexadecimal (`"hex"`), and binary (`"bin"`).
#' @param is_ipv6 A logical vector indicating whether to construct an IPv4 or
#'   IPv6 address. If `NULL` (the default), then integers less than 2^32 will
#'   construct an IPv4 address and anything larger will construct an IPv6 address.
#'
#' @return
#'  * For `ip_to_integer()`: A character vector
#'  * For `integer_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_integer(x)
#'
#' integer_to_ip(ip_to_integer(x))
#'
#' # with IPv4 only, we can use numeric data type
#' as.numeric(ip_to_integer(ip_address("192.168.0.1")))
#'
#' integer_to_ip(3232235521)
#'
#' # hex representation
#' ip_to_integer(x, base = "hex")
#' @seealso
#'  * [ip_to_bytes()] and [bytes_to_ip()]
#'  * [ip_to_binary()] and [binary_to_ip()]
#' @export
ip_to_integer <- function(x, base = c("dec", "hex", "bin")) {
  if (!is_ip_address(x)) {
    abort("'x' must be an ip_address vector")
  }

  switch(
    arg_match(base),
    dec = wrap_encode_integer(x, FALSE),
    hex = wrap_encode_integer(x, TRUE),
    bin = wrap_encode_binary(x)
  )
}

#' @rdname ip_to_integer
#' @export
integer_to_ip <- function(x, is_ipv6 = NULL) {
  if (is_integerish(x)) {
    x <- as.character(x)
  }
  if (!is_character(x)) {
    abort("'x' must be a character vector")
  }
  if (!(is_null(is_ipv6) || is_logical(is_ipv6))) {
    abort("'is_ipv6' must be a logical vector or NULL")
  }

  # vector recycling
  if (!is_null(is_ipv6)) {
    args <- vec_recycle_common(x, is_ipv6)
    x <- args[[1L]]
    is_ipv6 <- args[[2L]]
  }

  wrap_decode_integer(x, is_ipv6)
}


#' Represent address as raw bytes
#'
#' Encode or decode an [`ip_address`] as a vector of raw bytes.
#'
#' @details
#' The bytes are stored in network order (also known as
#' big-endian order), which is part of the IP standard.
#'
#' IPv4 addresses use 4 bytes, IPv6 addresses use 16 bytes,
#' and missing values are encoded as `NULL`.
#'
#' @param x
#'  * For `ip_to_bytes()`: An [`ip_address`] vector
#'  * For `bytes_to_ip()`: A [`blob::blob`] vector
#'
#' @return
#'  * For `ip_to_bytes()`: A [`blob::blob`] vector
#'  * For `bytes_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_bytes(x)
#'
#' bytes_to_ip(ip_to_bytes(x))
#' @seealso
#'  * [ip_to_integer()] and [integer_to_ip()]
#'  * [ip_to_binary()] and [binary_to_ip()]
#' @export
ip_to_bytes <- function(x) {
  if (!is_ip_address(x)) {
    abort("'x' must be an ip_address vector")
  }

  blob::new_blob(wrap_encode_bytes(x))
}

#' @rdname ip_to_bytes
#' @export
bytes_to_ip <- function(x) {
  if (!blob::is_blob(x)) {
    abort("'x' must be a blob object")
  }

  wrap_decode_bytes(x)
}


#' Represent address as binary
#'
#' Encode or decode an [`ip_address`] as a binary bit string.
#'
#' @details
#' The bits are stored in network order (also known as big-endian order), which
#' is part of the IP standard.
#'
#' IPv4 addresses use 32 bits, IPv6 addresses use 128 bits, and missing values
#' are encoded as `NA`.
#'
#' @param x
#'  * For `ip_to_binary()`: An [`ip_address`] vector
#'  * For `binary_to_ip()`: A character vector containing only `0` and `1` characters
#'
#' @return
#'  * For `ip_to_binary()`: A character vector
#'  * For `binary_to_ip()`: An [`ip_address`] vector
#'
#' @examples
#' x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
#' ip_to_binary(x)
#'
#' binary_to_ip(ip_to_binary(x))
#' @seealso
#'  * [ip_to_integer()] and [integer_to_ip()]
#'  * [ip_to_bytes()] and [bytes_to_ip()]
#' @export
ip_to_binary <- function(x) {
  if (!is_ip_address(x)) {
    abort("'x' must be an ip_address vector")
  }

  wrap_encode_binary(x)
}

#' @rdname ip_to_binary
#' @export
binary_to_ip <- function(x) {
  if (!is_character(x)) {
    abort("'x' must be a character vector")
  }

  wrap_decode_binary(x)
}


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
    abort("'x' must be an ip_address vector")
  }
  if (!is_bool(multiple)) {
    abort("'multiple' must be TRUE or FALSE")
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
    abort("'x' must be a character vector")
  }
  if (!is_bool(multiple)) {
    abort("'multiple' must be TRUE or FALSE")
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
