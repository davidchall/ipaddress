# Network membership of addresses

These functions check whether an address falls within a network.

`is_within()` performs a one-to-one matching between addresses and
networks.

`is_within_any()` checks if each address falls within *any* of the
networks.

## Usage

``` r
is_within(address, network)

is_within_any(address, network)
```

## Arguments

- address:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- network:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

## Value

A logical vector

## See also

Use
[`is_subnet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
to check if an
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
is within another
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md).

## Examples

``` r
is_within(ip_address("192.168.2.6"), ip_network("192.168.2.0/28"))
#> [1] TRUE

is_within(ip_address("192.168.3.6"), ip_network("192.168.2.0/28"))
#> [1] FALSE

is_within_any(ip_address("192.168.3.6"), ip_network(c("192.168.2.0/28", "192.168.3.0/28")))
#> [1] TRUE
```
