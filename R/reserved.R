#' Reserved addresses
#'
#' @description
#' Most of these functions check if an address or network is reserved for
#' special use. The exception is `is_global()`, which checks if it is *not*
#' reserved.
#'
#' A network is considered reserved if both the `network_address()`
#' and `broadcast_address()` are reserved.
#'
#' @details
#' Here are hyperlinks to the IANA registries of allocated address space:
#'
#'  * **IPv4:**
#'    [allocations](https://www.iana.org/assignments/ipv4-address-space/ipv4-address-space.xhtml),
#'    [special purpose](https://www.iana.org/assignments/iana-ipv4-special-registry/iana-ipv4-special-registry.xhtml)
#'  * **IPv6:**
#'    [allocations](https://www.iana.org/assignments/ipv6-address-space/ipv6-address-space.xhtml),
#'    [special purpose](https://www.iana.org/assignments/iana-ipv6-special-registry/iana-ipv6-special-registry.xhtml)
#'
#' @param x An [`ip_address`] or [`ip_network`] vector
#' @return A logical vector
#'
#' @examples
#' is_private(ip_network(c("192.168.0.0/16", "2001:db8::/32")))
#'
#' is_global(ip_network(c("1.0.0.0/8", "2002::/32")))
#'
#' is_multicast(ip_network(c("224.0.0.0/4", "ff00::/8")))
#'
#' is_unspecified(ip_network(c("0.0.0.0/32", "::/128")))
#'
#' is_reserved(ip_network(c("240.0.0.0/4", "f000::/5")))
#'
#' is_loopback(ip_network(c("127.0.0.0/8", "::1/128")))
#'
#' is_link_local(ip_network(c("169.254.0.0/16", "fe80::/10")))
#'
#' is_site_local(ip_network("fec0::/10"))
#' @seealso
#' Addresses reserved by IPv6 transition mechanisms can be identified
#' by functions described in [ipv6-transition].
#' @name is_reserved
NULL

#' @rdname is_reserved
#' @export
is_private <- function(x) {
  private <- ip_network(c(
    "0.0.0.0/8", "10.0.0.0/8", "127.0.0.0/8", "169.254.0.0/16", "172.16.0.0/12",
    "192.0.0.0/29", "192.0.0.170/31", "192.0.2.0/24", "192.168.0.0/16",
    "198.18.0.0/15", "198.51.100.0/24", "203.0.113.0/24", "240.0.0.0/4",
    "::/127", "::ffff:0:0/96", "100::/64", "2001::/23", "2001:db8::/32",
    "fc00::/7", "fe80::/10"
  ))

  if (is_ip_address(x)) {
    is_within_any(x, private)
  } else if (is_ip_network(x)) {
    first <- network_address(x)
    last <- broadcast_address(x)
    is_within_any(first, private) & is_within_any(last, private)
  } else {
    abort("`x` must be an ip_address or ip_network vector")
  }
}

#' @rdname is_reserved
#' @export
is_global <- function(x) {
  shared <- ip_network("100.64.0.0/10")

  if (is_ip_address(x)) {
    !is_within_any(x, shared) & !is_private(x)
  } else if (is_ip_network(x)) {
    first <- network_address(x)
    last <- broadcast_address(x)
    !is_within_any(first, shared) & !is_within_any(last, shared) & !is_private(first) & !is_private(last)
  } else {
    abort("`x` must be an ip_address or ip_network vector")
  }
}

#' @rdname is_reserved
#' @export
is_multicast <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  wrap_is_multicast(x)
}

#' @rdname is_reserved
#' @export
is_unspecified <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  wrap_is_unspecified(x)
}

#' @rdname is_reserved
#' @export
is_reserved <- function(x) {
  reserved <- ip_network(c(
    "240.0.0.0/4", "::/3", "4000::/2", "8000::/2", "c000::/3", "e000::/4",
    "f000::/5", "f800::/6", "fe00::/9"
  ))

  if (is_ip_address(x)) {
    is_within_any(x, reserved)
  } else if (is_ip_network(x)) {
    first <- network_address(x)
    last <- broadcast_address(x)
    is_within_any(first, reserved) & is_within_any(last, reserved)
  } else {
    abort("`x` must be an ip_address or ip_network vector")
  }
}

#' @rdname is_reserved
#' @export
is_loopback <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  wrap_is_loopback(x)
}

#' @rdname is_reserved
#' @export
is_link_local <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  wrap_is_link_local(x)
}

#' @rdname is_reserved
#' @export
is_site_local <- function(x) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    abort("`x` must be an ip_address or ip_network vector")
  }

  wrap_is_site_local(x)
}
