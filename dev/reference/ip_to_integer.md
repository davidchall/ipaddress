# Represent address as integer

Encode or decode an
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
as an integer.

## Usage

``` r
ip_to_integer(x)

integer_to_ip(x, is_ipv6 = NULL)
```

## Arguments

- x:

  - `ip_to_integer()`: An
    [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
    vector

  - `integer_to_ip()`: A
    [`bignum::biginteger`](https://davidchall.github.io/bignum/reference/biginteger.html)
    vector

- is_ipv6:

  A logical vector indicating whether to construct an IPv4 or IPv6
  address. If `NULL` (the default), then IPv4 is preferred but an IPv6
  address is constructed when `x` is too large for the IPv4 address
  space.

## Value

- `ip_to_integer()`: A
  [`bignum::biginteger`](https://davidchall.github.io/bignum/reference/biginteger.html)
  vector

- `integer_to_ip()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## Details

It is common to represent an IP address as an integer, by reinterpreting
the bit sequence as a big-endian unsigned integer. This means IPv4 and
IPv6 addresses can be represented by 32-bit and 128-bit unsigned
integers. In this way, the IPv4 addresses `0.0.0.0` and
`255.255.255.255` would be represented as 0 and 4,294,967,295.

The numeric data types within base R
([`integer`](https://rdrr.io/r/base/integer.html) and
[`double`](https://rdrr.io/r/base/double.html)) have insufficient
precision to cover the IPv6 address space. Instead we return a
[`bignum::biginteger`](https://davidchall.github.io/bignum/reference/biginteger.html)
vector, which supports arbitrary precision integers.

## See also

Other address representations:
[`ip_to_binary()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md),
[`ip_to_bytes()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md),
[`ip_to_hex()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md)

## Examples

``` r
x <- ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334", NA))
ip_to_integer(x)
#> <biginteger[3]>
#> [1] 3.232236e+09 4.254077e+37 <NA>        

integer_to_ip(ip_to_integer(x))
#> <ip_address[3]>
#> [1] 192.168.0.1             2001:db8::8a2e:370:7334 <NA>                   

# with IPv4 only, we can use numeric data type
as.numeric(ip_to_integer(ip_address("192.168.0.1")))
#> [1] 3232235521

integer_to_ip(3232235521)
#> <ip_address[1]>
#> [1] 192.168.0.1
```
