# Represent address as hexadecimal

Encode or decode an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
as a hexadecimal string.

## Usage

``` r
ip_to_hex(x)

hex_to_ip(x, is_ipv6 = NULL)
```

## Arguments

- x:

  - `ip_to_hex()`: An
    [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
    vector

  - `hex_to_ip()`: A character vector containing hexadecimal strings

- is_ipv6:

  A logical vector indicating whether to construct an IPv4 or IPv6
  address. If `NULL` (the default), then IPv4 is preferred but an IPv6
  address is constructed when `x` is too large for the IPv4 address
  space.

## Value

- `ip_to_hex()`: A character vector

- `hex_to_ip()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## See also

Other address representations:
[`ip_to_binary()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md),
[`ip_to_bytes()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md),
[`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)

## Examples

``` r
x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
ip_to_hex(x)
#> [1] "0xC0A80001"                         "0x20010DB80000000000008A2E03707334"
#> [3] NA                                  

hex_to_ip(ip_to_hex(x))
#> <ip_address[3]>
#> [1] 192.168.0.1             2001:db8::8a2e:370:7334 <NA>                   
```
