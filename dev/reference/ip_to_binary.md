# Represent address as binary

Encode or decode an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
as a binary bit string.

## Usage

``` r
ip_to_binary(x)

binary_to_ip(x)
```

## Arguments

- x:

  - `ip_to_binary()`: An
    [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
    vector

  - `binary_to_ip()`: A character vector containing only `0` and `1`
    characters

## Value

- `ip_to_binary()`: A character vector

- `binary_to_ip()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## Details

The bits are stored in network order (also known as big-endian order),
which is part of the IP standard.

IPv4 addresses use 32 bits, IPv6 addresses use 128 bits, and missing
values are encoded as `NA`.

## See also

Other address representations:
[`ip_to_bytes()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md),
[`ip_to_hex()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md),
[`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)

## Examples

``` r
x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
ip_to_binary(x)
#> [1] "11000000101010000000000000000001"                                                                                                
#> [2] "00100000000000010000110110111000000000000000000000000000000000000000000000000000100010100010111000000011011100000111001100110100"
#> [3] NA                                                                                                                                

binary_to_ip(ip_to_binary(x))
#> <ip_address[3]>
#> [1] 192.168.0.1             2001:db8::8a2e:370:7334 <NA>                   
```
