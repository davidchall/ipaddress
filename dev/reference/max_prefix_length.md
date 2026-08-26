# Size of the address space

The total number of bits available in the address space. IPv4 uses
32-bit addresses and IPv6 uses 128-bit addresses.

## Usage

``` r
max_prefix_length(x)
```

## Arguments

- x:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  or
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

## Value

An integer vector

## See also

[`is_ipv4()`](https://davidchall.github.io/ipaddress/dev/reference/is_ipv6.md),
[`is_ipv6()`](https://davidchall.github.io/ipaddress/dev/reference/is_ipv6.md),
[`prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)

## Examples

``` r
x <- ip_address(c("192.168.0.1", "2001:db8::7334"))

max_prefix_length(x)
#> [1]  32 128
```
