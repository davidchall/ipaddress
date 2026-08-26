# Reserved addresses

Most of these functions check if an address or network is reserved for
special use. The exception is `is_global()`, which checks if it is *not*
reserved.

A network is considered reserved if both the
[`network_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
and
[`broadcast_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
are reserved.

## Usage

``` r
is_private(x)

is_global(x)

is_multicast(x)

is_unspecified(x)

is_reserved(x)

is_loopback(x)

is_link_local(x)

is_site_local(x)
```

## Arguments

- x:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  or
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

## Value

A logical vector

## Details

Here are hyperlinks to the IANA registries of allocated address space:

- **IPv4:**
  [allocations](https://www.iana.org/assignments/ipv4-address-space/ipv4-address-space.xhtml),
  [special
  purpose](https://www.iana.org/assignments/iana-ipv4-special-registry/iana-ipv4-special-registry.xhtml)

- **IPv6:**
  [allocations](https://www.iana.org/assignments/ipv6-address-space/ipv6-address-space.xhtml),
  [special
  purpose](https://www.iana.org/assignments/iana-ipv6-special-registry/iana-ipv6-special-registry.xhtml)

## See also

Addresses reserved by IPv6 transition mechanisms can be identified by
functions described in
[ipv6-transition](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md).

## Examples

``` r
is_private(ip_network(c("192.168.0.0/16", "2001:db8::/32")))
#> [1] TRUE TRUE

is_global(ip_network(c("1.0.0.0/8", "2002::/32")))
#> [1] TRUE TRUE

is_multicast(ip_network(c("224.0.0.0/4", "ff00::/8")))
#> [1] TRUE TRUE

is_unspecified(ip_network(c("0.0.0.0/32", "::/128")))
#> [1] TRUE TRUE

is_reserved(ip_network(c("240.0.0.0/4", "f000::/5")))
#> [1] TRUE TRUE

is_loopback(ip_network(c("127.0.0.0/8", "::1/128")))
#> [1] TRUE TRUE

is_link_local(ip_network(c("169.254.0.0/16", "fe80::/10")))
#> [1] TRUE TRUE

is_site_local(ip_network("fec0::/10"))
#> [1] TRUE
```
