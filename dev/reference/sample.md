# Sample random addresses

`sample_ipv4()` and `sample_ipv6()` sample from the entire address
space; `sample_network()` samples from a specific network.

## Usage

``` r
sample_ipv4(size, ..., replace = FALSE)

sample_ipv6(size, ..., replace = FALSE)

sample_network(x, size, ..., replace = FALSE)
```

## Arguments

- size:

  Integer specifying the number of addresses to return

- ...:

  These dots are for future extensions and must be empty.

- replace:

  Should sampling be with replacement? (default: `FALSE`)

- x:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  scalar

## Value

An
[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
vector

## See also

Use
[`seq.ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/sequence.md)
to generate *all* addresses in a network.

## Examples

``` r
sample_ipv4(5)
#> <ip_address[5]>
#> [1] 50.223.119.20  103.44.127.213 16.8.74.153    99.82.187.40   249.102.197.1 

sample_ipv6(5)
#> <ip_address[5]>
#> [1] 3dff:eb87:572:31d3:c776:c3ae:6e07:bd4a 
#> [2] 8c26:6699:605f:f246:3450:c57f:b439:dad 
#> [3] d584:3642:8f07:8a91:b62c:fda4:f24d:87bc
#> [4] 7d8:ab4a:db77:8b55:1088:f8a9:2ea2:b232 
#> [5] 78b7:f7a:6263:4798:5a7e:6318:377a:b0fb 

sample_network(ip_network("192.168.0.0/16"), 5)
#> <ip_address[5]>
#> [1] 192.168.171.206 192.168.129.208 192.168.169.103 192.168.131.55 
#> [5] 192.168.213.107

sample_network(ip_network("2001:db8::/48"), 5)
#> <ip_address[5]>
#> [1] 2001:db8:0:55b3:912:932a:3fdb:80b5  2001:db8:0:9138:97ff:afa9:6791:5bdf
#> [3] 2001:db8:0:40ba:3c9c:3edb:c540:c602 2001:db8:0:7637:e82c:bed:1eeb:95e3 
#> [5] 2001:db8:0:ea74:d1e8:e88d:31de:a2ff
```
