# Vector of IP addresses

Construct a vector of IP addresses.

## Usage

``` r
ip_address(x = character())
```

## Arguments

- x:

  A character vector of IP addresses, in dot-decimal notation (IPv4) or
  hexadecimal notation (IPv6)

## Value

An S3 vector of class `ip_address`

## Details

An address in IPv4 space uses 32-bits. It is usually represented as 4
groups of 8 bits, each shown as decimal digits (e.g. `192.168.0.1`).
This is known as dot-decimal notation.

An address in IPv6 space uses 128-bits. It is usually represented as 8
groups of 16 bits, each shown as hexadecimal digits (e.g.
`2001:0db8:85a3:0000:0000:8a2e:0370:7334`). This representation can also
be compressed by removing leading zeros and replacing consecutive groups
of zeros with double-colon (e.g. `2001:db8:85a3::8a2e:370:7334`).
Finally, there is also the dual representation. This expresses the final
two groups as an IPv4 address (e.g. `2001:db8:85a3::8a2e:3.112.115.52`).

The `ip_address()` constructor accepts a character vector of IP
addresses in these two formats. It checks whether each string is a valid
IPv4 or IPv6 address, and converts it to an `ip_address` object. If the
input is invalid, a warning is emitted and `NA` is stored instead.

When casting an `ip_address` object back to a character vector using
[`as.character()`](https://rdrr.io/r/base/character.html), IPv6
addresses are reduced to their compressed representation. A special case
is IPv4-mapped IPv6 addresses (see
[`is_ipv4_mapped()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)),
which are returned in the dual representation (e.g.
`::ffff:192.168.0.1`).

`ip_address` vectors support a number of
[operators](https://davidchall.github.io/ipaddress/dev/reference/ip_operators.md).

## See also

[`ip_operators`](https://davidchall.github.io/ipaddress/dev/reference/ip_operators.md),
[`vignette("ip-data")`](https://davidchall.github.io/ipaddress/dev/articles/ip-data.md)

## Examples

``` r
# supports IPv4 and IPv6 simultaneously
ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334"))
#> <ip_address[2]>
#> [1] 192.168.0.1             2001:db8::8a2e:370:7334

# validates inputs and replaces with NA
ip_address(c("255.255.255.256", "192.168.0.1/32"))
#> Warning: Problem on row 1: 255.255.255.256
#> Warning: Problem on row 2: 192.168.0.1/32
#> <ip_address[2]>
#> [1] <NA> <NA>
```
