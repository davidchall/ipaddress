# Version of the address space

Version of the address space

## Usage

``` r
is_ipv4(x)

is_ipv6(x)
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

## See also

[`max_prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/max_prefix_length.md)

## Examples

``` r
ip <- ip_address(c("192.168.0.1", "2001:db8::7334"))

is_ipv4(ip)
#> [1]  TRUE FALSE

is_ipv6(ip)
#> [1] FALSE  TRUE
```
