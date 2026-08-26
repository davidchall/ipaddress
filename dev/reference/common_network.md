# Find the common network of two addresses

Returns the smallest network that contains both addresses.

This can construct a network from its first and last addresses. However,
if the address range does not match the network boundaries, then the
result extends beyond the original address range. Use
[`summarize_address_range()`](https://davidchall.github.io/ipaddress/dev/reference/summarize_address_range.md)
to receive a list of networks that exactly match the address range.

## Usage

``` r
common_network(address1, address2)
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

An
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vector

## See also

[`summarize_address_range()`](https://davidchall.github.io/ipaddress/dev/reference/summarize_address_range.md)

## Examples

``` r
# address range matches network boundaries
common_network(ip_address("192.168.0.0"), ip_address("192.168.0.15"))
#> <ip_network[1]>
#> [1] 192.168.0.0/28

# address range does not match network boundaries
common_network(ip_address("192.167.255.255"), ip_address("192.168.0.16"))
#> <ip_network[1]>
#> [1] 192.160.0.0/12
```
