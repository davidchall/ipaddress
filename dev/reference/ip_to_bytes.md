# Represent address as raw bytes

Encode or decode an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
as a list of raw bytes.

## Usage

``` r
ip_to_bytes(x)

bytes_to_ip(x)
```

## Arguments

- x:

  - `ip_to_bytes()`: An
    [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
    vector

  - `bytes_to_ip()`: A list of raw vectors or a
    [`blob::blob`](https://blob.tidyverse.org/reference/blob.html)
    object

## Value

- `ip_to_bytes()`: A list of raw vectors

- `bytes_to_ip()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## Details

The bytes are stored in network order (also known as big-endian order),
which is part of the IP standard.

IPv4 addresses use 4 bytes, IPv6 addresses use 16 bytes, and missing
values are encoded as `NULL`.

## See also

Use [`blob::as_blob()`](https://blob.tidyverse.org/reference/blob.html)
to cast result to a blob object

Other address representations:
[`ip_to_binary()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md),
[`ip_to_hex()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md),
[`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)

## Examples

``` r
x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
ip_to_bytes(x)
#> [[1]]
#> [1] c0 a8 00 01
#> 
#> [[2]]
#>  [1] 20 01 0d b8 00 00 00 00 00 00 8a 2e 03 70 73 34
#> 
#> [[3]]
#> NULL
#> 

bytes <- list(
  as.raw(c(0xc0, 0xa8, 0x00, 0x01)),
  as.raw(c(
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x8a, 0x2e, 0x03, 0x70, 0x73, 0x34
  )),
  NULL
)
bytes_to_ip(bytes)
#> <ip_address[3]>
#> [1] 192.168.0.1             2001:db8::8a2e:370:7334 <NA>                   
```
