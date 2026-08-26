# Network size

`network_address()` and `broadcast_address()` yield the first and last
addresses of the network; `num_addresses()` gives the total number of
addresses in the network.

## Usage

``` r
network_address(x)

broadcast_address(x)

num_addresses(x)
```

## Arguments

- x:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

## Value

- `network_address()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- `broadcast_address()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- `num_addresses()`: A numeric vector

## Details

The broadcast address is a special address at which any host connected
to the network can receive messages. That is, packets sent to this
address are received by all hosts on the network. In IPv4, the last
address of a network is the broadcast address. Although IPv6 does not
follow this approach to broadcast addresses, the `broadcast_address()`
function still returns the last address of the network.

## See also

Use
[`seq.ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/sequence.md)
to generate all addresses in a network.

## Examples

``` r
x <- ip_network(c("192.168.0.0/22", "2001:db8::/33"))

network_address(x)
#> <ip_address[2]>
#> [1] 192.168.0.0 2001:db8:: 

broadcast_address(x)
#> <ip_address[2]>
#> [1] 192.168.3.255                         
#> [2] 2001:db8:7fff:ffff:ffff:ffff:ffff:ffff

num_addresses(x)
#> [1] 1.024000e+03 3.961408e+28
```
