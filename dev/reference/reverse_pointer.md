# Reverse DNS pointer

Returns the PTR record used by reverse DNS.

## Usage

``` r
reverse_pointer(x)
```

## Arguments

- x:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## Value

A character vector

## Details

These documents describe reverse DNS lookup in more detail:

- **IPv4:** [RFC-1035 Section
  3.5](https://www.rfc-editor.org/rfc/rfc1035)

- **IPv6:** [RFC-3596 Section
  2.5](https://www.rfc-editor.org/rfc/rfc3596)

## Examples

``` r
reverse_pointer(ip_address("127.0.0.1"))
#> [1] "1.0.0.127.in-addr.arpa"

reverse_pointer(ip_address("2001:db8::1"))
#> [1] "1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.8.b.d.0.1.0.0.2.ip.arpa"
```
