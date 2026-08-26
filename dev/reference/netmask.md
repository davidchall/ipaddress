# Network mask

`prefix_length()`, `netmask()` and `hostmask()` extract different (but
equivalent) representations of the network mask. They accept an
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
or
[`ip_interface`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
vector.

The functions can also convert between these alternative
representations. For example, `prefix_length()` can infer the prefix
length from an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
vector of netmasks and/or hostmasks, while `netmask()` and `hostmask()`
can accept a vector of prefix lengths.

## Usage

``` r
prefix_length(x)

netmask(x, ...)

# S3 method for class 'numeric'
netmask(x, is_ipv6 = NULL, ...)

hostmask(x, ...)

# S3 method for class 'numeric'
hostmask(x, is_ipv6 = NULL, ...)
```

## Arguments

- x:

  - An
    [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
    vector.

  - An
    [`ip_interface`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
    vector.

  - `prefix_length()`: An
    [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
    vector of netmasks and/or hostmasks. Ambiguous cases (all zeros, all
    ones) are treated as netmasks.

  - `netmask()` and `hostmask()`: An integer vector of prefix lengths.

- ...:

  Arguments passed to methods.

- is_ipv6:

  A logical vector indicating whether to construct an IPv4 or IPv6
  address. If `NULL` (the default), then IPv4 is preferred but an IPv6
  address is constructed when `x` is too large for the IPv4 address
  space.

## Value

- `prefix_length()`: An integer vector

- `netmask()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- `hostmask()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## See also

[`max_prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/max_prefix_length.md)

## Examples

``` r
x <- ip_network(c("192.168.0.0/22", "2001:db00::0/26"))

prefix_length(x)
#> [1] 22 26

netmask(x)
#> <ip_address[2]>
#> [1] 255.255.252.0 ffff:ffc0::  

hostmask(x)
#> <ip_address[2]>
#> [1] 0.0.3.255                          0:3f:ffff:ffff:ffff:ffff:ffff:ffff

# construct netmask/hostmask from prefix length
netmask(c(22L, 26L), c(FALSE, TRUE))
#> <ip_address[2]>
#> [1] 255.255.252.0 ffff:ffc0::  

hostmask(c(22L, 26L), c(FALSE, TRUE))
#> <ip_address[2]>
#> [1] 0.0.3.255                          0:3f:ffff:ffff:ffff:ffff:ffff:ffff

# extract prefix length from netmask/hostmask
prefix_length(ip_address(c("255.255.255.0", "0.255.255.255")))
#> [1] 24  8

# invalid netmask/hostmask raise a warning and return NA
prefix_length(ip_address("255.255.255.1"))
#> Warning: Problem on row 1: 255.255.255.1 (invalid netmask/hostmask)
#> [1] NA
```
