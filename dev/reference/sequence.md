# List addresses within a network

[`seq()`](https://rdrr.io/r/base/seq.html) returns *all* hosts

`hosts()` returns only *usable* hosts

## Usage

``` r
# S3 method for class 'ip_network'
seq(x, ...)

hosts(x)
```

## Arguments

- x:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  scalar

- ...:

  These dots are for future extensions and must be empty.

## Value

An
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
vector

## Details

In IPv4, the unusable hosts are the network address and the broadcast
address (i.e. the first and last addresses in the network). In IPv6, the
only unusable host is the subnet router anycast address (i.e. the first
address in the network).

For networks with a prefix length of 31 (for IPv4) or 127 (for IPv6),
the unusable hosts are included in the results of `hosts()`.

The ipaddress package does not support long vectors (i.e. vectors with
more than 2^31 - 1 elements). As a result, these two functions do not
support networks larger than this size. This corresponds to prefix
lengths less than 2 (for IPv4) or 98 (for IPv6). However, you might find
that machine memory imposes stricter limitations.

## See also

Use
[`network_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
and
[`broadcast_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
to get the first and last address of a network.

Use
[`sample_network()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
to randomly sample addresses from a network.

Use
[`subnets()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
to list the subnetworks within a network.

## Examples

``` r
seq(ip_network("192.168.0.0/30"))
#> <ip_address[4]>
#> [1] 192.168.0.0 192.168.0.1 192.168.0.2 192.168.0.3

seq(ip_network("2001:db8::/126"))
#> <ip_address[4]>
#> [1] 2001:db8::  2001:db8::1 2001:db8::2 2001:db8::3

hosts(ip_network("192.168.0.0/30"))
#> <ip_address[2]>
#> [1] 192.168.0.1 192.168.0.2

hosts(ip_network("2001:db8::/126"))
#> <ip_address[3]>
#> [1] 2001:db8::1 2001:db8::2 2001:db8::3
```
