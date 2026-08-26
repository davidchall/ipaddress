# Collapse contiguous and overlapping networks

Given a vector of networks, this returns the minimal set of networks
required to represent the same range of addresses.

## Usage

``` r
collapse_networks(network)
```

## Arguments

- network:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

## Value

An
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vector (potentially shorter than the input)

## See also

[`exclude_networks()`](https://davidchall.github.io/ipaddress/dev/reference/exclude_networks.md)

## Examples

``` r
collapse_networks(ip_network(c("192.168.0.0/24", "192.168.1.0/24")))
#> <ip_network[1]>
#> [1] 192.168.0.0/23
```
