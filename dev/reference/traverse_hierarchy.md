# Traverse the network hierarchy

These functions step up and down the network hierarchy. `supernet()`
returns the supernetwork containing the given network. `subnets()`
returns the list of subnetworks which join to make the given network.

## Usage

``` r
supernet(x, new_prefix = prefix_length(x) - 1L)

subnets(x, new_prefix = prefix_length(x) + 1L)
```

## Arguments

- x:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

- new_prefix:

  An integer vector indicating the desired prefix length. By default,
  this steps a single level through the hierarchy.

## Value

- `supernet()`: An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

- `subnets()`: A list of
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vectors

## Details

The ipaddress package does not support long vectors (i.e. vectors with
more than 2^31 - 1 elements). The limits the number of subnetworks that
`subnets()` can return. However, you might find that machine memory
imposes stricter limitations.

## See also

Use
[`seq.ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/sequence.md)
to list the addresses within a network.

Use
[`is_supernet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
and
[`is_subnet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
to check if one network is contained within another.

## Examples

``` r
supernet(ip_network("192.168.0.0/24"))
#> <ip_network[1]>
#> [1] 192.168.0.0/23

supernet(ip_network("192.168.0.0/24"), new_prefix = 10L)
#> <ip_network[1]>
#> [1] 192.128.0.0/10

subnets(ip_network("192.168.0.0/24"))
#> <list_of<ip_network>[1]>
#> [[1]]
#> <ip_network[2]>
#> [1] 192.168.0.0/25   192.168.0.128/25
#> 

subnets(ip_network("192.168.0.0/24"), new_prefix = 27L)
#> <list_of<ip_network>[1]>
#> [[1]]
#> <ip_network[8]>
#> [1] 192.168.0.0/27   192.168.0.32/27  192.168.0.64/27  192.168.0.96/27 
#> [5] 192.168.0.128/27 192.168.0.160/27 192.168.0.192/27 192.168.0.224/27
#> 
```
