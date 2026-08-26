# Vector of IP networks

Construct a vector of IP networks.

## Usage

``` r
ip_network(...)

# Default S3 method
ip_network(x = character(), ..., strict = TRUE)

# S3 method for class 'ip_address'
ip_network(address, prefix_length, ..., strict = TRUE)
```

## Arguments

- ...:

  Arguments passed to methods.

- x:

  A character vector of IP networks, in CIDR notation (IPv4 or IPv6)

- strict:

  If `TRUE` (the default) and the input has host bits set, then a
  warning is emitted and `NA` is returned. If `FALSE`, the host bits are
  set to zero and a valid IP network is returned. If you need to retain
  the host bits, consider using
  [`ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
  instead.

- address:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- prefix_length:

  An integer vector

## Value

An S3 vector of class `ip_network`

## Details

An IP network corresponds to a contiguous range of IP addresses (also
known as an IP block). CIDR notation represents an IP network as the
routing prefix address (which denotes the start of the range) and the
prefix length (which indicates the size of the range) separated by a
forward slash. For example, `192.168.0.0/24` represents addresses from
`192.168.0.0` to `192.168.0.255`.

The prefix length indicates the number of bits reserved by the routing
prefix. This means that larger prefix lengths indicate smaller networks.
The maximum prefix length is 32 for IPv4 and 128 for IPv6. These would
correspond to an IP network of a single IP address.

The `ip_network()` constructor accepts a character vector of IP networks
in CIDR notation. It checks whether each string is a valid IPv4 or IPv6
network, and converts it to an `ip_network` object. If the input is
invalid, a warning is emitted and `NA` is stored instead.

An alternative constructor accepts an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
vector and an integer vector containing the network address and prefix
length, respectively.

When casting an `ip_network` object back to a character vector using
[`as.character()`](https://rdrr.io/r/base/character.html), IPv6
addresses are reduced to their compressed representation.

When comparing and sorting `ip_network` vectors, the network address is
compared before the prefix length.

## See also

[`prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md),
[`network_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md),
[`netmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md),
[`hostmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)

[`vignette("ip-data")`](https://davidchall.github.io/ipaddress/dev/articles/ip-data.md)

## Examples

``` r
# construct from character vector
ip_network(c("192.168.0.0/24", "2001:db8::/48"))
#> <ip_network[2]>
#> [1] 192.168.0.0/24 2001:db8::/48 

# validates inputs and replaces with NA
ip_network(c("192.168.0.0/33", "192.168.0.0"))
#> Warning: Problem on row 1: 192.168.0.0/33
#> Warning: Problem on row 2: 192.168.0.0
#> <ip_network[2]>
#> [1] <NA> <NA>

# IP networks should not have any host bits set
ip_network("192.168.0.1/22")
#> Warning: Problem on row 1: 192.168.0.1/22 (host bits set)
#> <ip_network[1]>
#> [1] <NA>

# but we can mask the host bits if desired
ip_network("192.168.0.1/22", strict = FALSE)
#> <ip_network[1]>
#> [1] 192.168.0.0/22

# construct from address + prefix length
ip_network(ip_address("192.168.0.0"), 24L)
#> <ip_network[1]>
#> [1] 192.168.0.0/24

# construct from address + netmask
ip_network(ip_address("192.168.0.0"), prefix_length(ip_address("255.255.255.0")))
#> <ip_network[1]>
#> [1] 192.168.0.0/24

# construct from address + hostmask
ip_network(ip_address("192.168.0.0"), prefix_length(ip_address("0.0.0.255")))
#> <ip_network[1]>
#> [1] 192.168.0.0/24
```
