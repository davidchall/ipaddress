# IPv6 transition mechanisms

There are multiple mechanisms designed to help with the transition from
IPv4 to IPv6. These functions make it possible to extract the embedded
IPv4 address from an IPv6 address.

## Usage

``` r
is_ipv4_mapped(x)

is_6to4(x)

is_teredo(x)

extract_ipv4_mapped(x)

extract_6to4(x)

extract_teredo_server(x)

extract_teredo_client(x)
```

## Arguments

- x:

  An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## Value

- `is_xxx()`: A logical vector

- `extract_xxx()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

## Details

The IPv6 transition mechanisms are described in the IETF memos:

- IPv4-mapped: [RFC 4291](https://www.rfc-editor.org/rfc/rfc4291)

- 6to4: [RFC 3056](https://www.rfc-editor.org/rfc/rfc3056)

- Teredo: [RFC 4380](https://www.rfc-editor.org/rfc/rfc4380)

## Examples

``` r
# these examples show the reserved networks
is_ipv4_mapped(ip_network("::ffff:0.0.0.0/96"))
#> [1] TRUE

is_6to4(ip_network("2002::/16"))
#> [1] TRUE

is_teredo(ip_network("2001::/32"))
#> [1] TRUE

# these examples show embedded IPv4 addresses
extract_ipv4_mapped(ip_address("::ffff:192.168.0.1"))
#> <ip_address[1]>
#> [1] 192.168.0.1

extract_6to4(ip_address("2002:c000:0204::"))
#> <ip_address[1]>
#> [1] 192.0.2.4

extract_teredo_server(ip_address("2001:0000:4136:e378:8000:63bf:3fff:fdd2"))
#> <ip_address[1]>
#> [1] 65.54.227.120

extract_teredo_client(ip_address("2001:0000:4136:e378:8000:63bf:3fff:fdd2"))
#> <ip_address[1]>
#> [1] 192.0.2.45
```
