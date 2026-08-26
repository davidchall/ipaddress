# Network membership of other networks

`is_supernet()` and `is_subnet()` check if one network is a true
supernet or subnet of another network; `overlaps()` checks for any
overlap between two networks.

## Usage

``` r
is_supernet(network, other)

is_subnet(network, other)

overlaps(network, other)
```

## Arguments

- network:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

- other:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

## Value

A logical vector

## See also

Use
[`is_within()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
to check if an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
is within an
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md).

Use
[`supernet()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
and
[`subnets()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
to traverse the network hierarchy.

## Examples

``` r
net1 <- ip_network("192.168.1.128/30")
net2 <- ip_network("192.168.1.0/24")

is_supernet(net1, net2)
#> [1] FALSE

is_subnet(net1, net2)
#> [1] TRUE

overlaps(net1, net2)
#> [1] TRUE
```
