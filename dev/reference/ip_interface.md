# Vector of IP interfaces

Construct a vector of IP interfaces.

This hybrid class stores both the host address and the network it is on.

## Usage

``` r
ip_interface(...)

# Default S3 method
ip_interface(x = character(), ...)

# S3 method for class 'ip_address'
ip_interface(address, prefix_length, ...)
```

## Arguments

- ...:

  Arguments passed to methods.

- x:

  A character vector of IP interfaces, in CIDR notation (IPv4 or IPv6)

- address:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- prefix_length:

  An integer vector

## Value

An S3 vector of class `ip_interface`

## Details

Constructing an `ip_interface` vector is conceptually like constructing
an
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vector, except the host bits are retained.

The `ip_interface` class inherits from the
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
class. This means it can generally be used in places where an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
vector is expected. A few exceptions to this rule are:

- It does not support addition and subtraction of integers

- It does not support bitwise operations

- It cannot be compared to
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vectors

The `ip_interface` class additionally supports a few functions typically
reserved for
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vectors:
[`prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md),
[`netmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
and
[`hostmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md).

For other purposes, you can extract the address and network components
using
[`as_ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_cast.md)
and
[`as_ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_cast.md).

When comparing and sorting `ip_interface` vectors, the network is
compared before the host address.

## See also

[`vignette("ip-data")`](https://davidchall.github.io/ipaddress/dev/articles/ip-data.md)

## Examples

``` r
# construct from character vector
ip_interface(c("192.168.0.1/10", "2001:db8:c3::abcd/45"))
#> <ip_interface[2]>
#> [1] 192.168.0.1/10       2001:db8:c3::abcd/45

# construct from address + prefix length objects
ip_interface(ip_address(c("192.168.0.1", "2001:db8:c3::abcd")), c(10L, 45L))
#> <ip_interface[2]>
#> [1] 192.168.0.1/10       2001:db8:c3::abcd/45

# extract IP address
x <- ip_interface(c("192.168.0.1/10", "2001:db8:c3::abcd/45"))
as_ip_address(x)
#> <ip_address[2]>
#> [1] 192.168.0.1       2001:db8:c3::abcd

# extract IP network (with host bits masked)
as_ip_network(x)
#> <ip_network[2]>
#> [1] 192.128.0.0/10   2001:db8:c0::/45
```
