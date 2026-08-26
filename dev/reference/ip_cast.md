# Cast to IP vector

Methods for converting character vectors and
[`ip_interface`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
vectors to
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
and
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vectors.

## Usage

``` r
as_ip_address(x)

as_ip_interface(x)

as_ip_network(x)
```

## Arguments

- x:

  An object to cast

## Value

- `as_ip_address()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- `as_ip_network()`: An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

- `as_ip_interface()`: An
  [`ip_interface`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
  vector

## Examples

``` r
as_ip_address(ip_interface("192.168.0.1/10"))
#> <ip_address[1]>
#> [1] 192.168.0.1

as_ip_network(ip_interface("192.168.0.1/10"))
#> <ip_network[1]>
#> [1] 192.128.0.0/10
```
