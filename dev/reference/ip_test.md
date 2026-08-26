# Test for IP vector

Check if an object is an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md),
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
or
[`ip_interface`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
vector.

## Usage

``` r
is_ip_address(x)

is_ip_interface(x)

is_ip_network(x)
```

## Arguments

- x:

  An object to test

## Value

A logical scalar

## Examples

``` r
is_ip_address(ip_address("192.168.0.1"))
#> [1] TRUE
is_ip_interface(ip_interface("192.168.0.1/10"))
#> [1] TRUE
is_ip_network(ip_network("192.168.0.0/24"))
#> [1] TRUE
```
