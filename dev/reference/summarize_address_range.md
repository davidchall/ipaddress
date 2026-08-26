# List constituent networks of an address range

Given an address range, this returns the list of constituent networks.

If you know the address range matches the boundaries of a single
network, it might be preferable to use
[`common_network()`](https://davidchall.github.io/ipaddress/dev/reference/common_network.md).
This returns an
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vector instead of a list of
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vectors.

## Usage

``` r
summarize_address_range(address1, address2)
```

## Arguments

- address1:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- address2:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## Value

A list of
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vectors

## See also

[`common_network()`](https://davidchall.github.io/ipaddress/dev/reference/common_network.md)

## Examples

``` r
# address range matches network boundaries
summarize_address_range(ip_address("192.168.0.0"), ip_address("192.168.0.15"))
#> <list_of<ip_network>[1]>
#> [[1]]
#> <ip_network[1]>
#> [1] 192.168.0.0/28
#> 

# address range does not match network boundaries
summarize_address_range(ip_address("192.167.255.255"), ip_address("192.168.0.16"))
#> <list_of<ip_network>[1]>
#> [[1]]
#> <ip_network[3]>
#> [1] 192.167.255.255/32 192.168.0.0/28     192.168.0.16/32   
#> 
```
