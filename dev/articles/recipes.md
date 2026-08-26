# Examples and Recipes

This vignette demonstrates some typical example usage and recipes when
learning about ipaddress.

## Addresses from integers

Although IPv4 addresses are usually displayed in a human-readable format
(e.g. `192.168.0.1`), they are often saved to disk as integers to reduce
storage requirements. R is unable to store the entire range of IPv4
addresses in its integer data type, but they can instead be stored in
its numeric data type. More details are found under
[`help("ip_to_integer")`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md).

Given this, it’s quite possible that you’ll receive IPv4 addresses
represented as integers, and we’ll want to convert them to the
[`ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
vector type. Here’s an example of how to do that:

``` r

integer_to_ip(c(0, 3232235521, 4294967295))
#> <ip_address[3]>
#> [1] 0.0.0.0         192.168.0.1     255.255.255.255
```

## Networks from address ranges

There are multiple equivalent ways to represent an IP network:

1.  start address + prefix length (e.g. CIDR notation)
2.  start address + netmask
3.  start address + hostmask
4.  start address + end address

Although the
[`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
function can handle the first 3 options, we use the
[`common_network()`](https://davidchall.github.io/ipaddress/dev/reference/common_network.md)
function for the final option.

``` r

tibble(
  start = ip_address(c("192.168.0.0", "2001:db8::")),
  end = ip_address(c("192.168.0.15", "2001:db8::ffff:ffff:ffff"))
) %>%
  mutate(network = common_network(start, end))
#> # A tibble: 2 × 3
#>         start                      end        network
#>     <ip_addr>                <ip_addr>     <ip_netwk>
#> 1 192.168.0.0             192.168.0.15 192.168.0.0/28
#> 2  2001:db8:: 2001:db8::ffff:ffff:ffff  2001:db8::/80
```

Note that this approach assumes the two addresses do actually correspond
to the first and last addresses of the network, otherwise an expanded
network will be returned (see
[`help("common_network")`](https://davidchall.github.io/ipaddress/dev/reference/common_network.md)
for details).

## Is an address in a network?

A very common task is to check if an address is within a network, so the
ipaddress package provides a couple of different functions to help with
this workflow:
[`is_within()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
and
[`is_within_any()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md).
We also provide
[`is_subnet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
and
[`is_supernet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
to test if a network is within another network.

To see how these functions can be used in practice, let’s consider a
couple of IP networks:

``` r

my_networks <- tibble(
  network = ip_network(c("192.168.0.0/16", "2001:db8::/32")),
  label = c("Private", "Documentation")
)

my_networks
#> # A tibble: 2 × 2
#>          network label        
#>       <ip_netwk> <chr>        
#> 1 192.168.0.0/16 Private      
#> 2  2001:db8::/32 Documentation
```

and a handful of addresses:

``` r

my_addresses <- tibble(
  address = ip_address(c("192.168.100.1", "1.2.3.4", "2001:db8::8a2e:370:7334", "::1"))
)
```

First, we’ll check if each address is in *any* of our networks.

``` r

my_addresses %>%
  mutate(in_network = is_within_any(address, my_networks$network))
#> # A tibble: 4 × 2
#>                   address in_network
#>                 <ip_addr> <lgl>     
#> 1           192.168.100.1 TRUE      
#> 2                 1.2.3.4 FALSE     
#> 3 2001:db8::8a2e:370:7334 TRUE      
#> 4                     ::1 FALSE
```

But what if we need to know *which* of our networks the address was
found in? We can do that using the excellent
[fuzzyjoin](https://cran.r-project.org/package=fuzzyjoin) package
together with the
[`is_within()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
function.

``` r

my_addresses %>%
  fuzzyjoin::fuzzy_left_join(my_networks, c("address" = "network"), is_within)
#> # A tibble: 4 × 3
#>                   address        network label        
#>                 <ip_addr>     <ip_netwk> <chr>        
#> 1           192.168.100.1 192.168.0.0/16 Private      
#> 2                 1.2.3.4             NA NA           
#> 3 2001:db8::8a2e:370:7334  2001:db8::/32 Documentation
#> 4                     ::1             NA NA
```

## Randomly generate public addresses

ipaddress provides functions to sample from a specific network
([`sample_network()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md))
or the entire address space
([`sample_ipv4()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
and
[`sample_ipv6()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)).
However, it can be more difficult to sample from the majority of address
space, while excluding certain networks.

A good example is sampling public IPv4 addresses. The simplest solution
is to use an accept-reject algorithm – sampling the entire IPv4 address
space and rejecting addresses that are reserved.

``` r

sample_public <- function(size) {
  result <- sample_ipv4(size)

  all_public <- FALSE
  while (!all_public) {
    public <- is_global(result)
    n_replace <- sum(!public)

    if (n_replace == 0) {
      all_public <- TRUE
    } else {
      result[!public] <- sample_ipv4(n_replace)
    }
  }

  result
}
```

We now sample 10 addresses and make sure they are all public addresses.

``` r

tibble(address = sample_public(10)) %>%
  mutate(is_public = is_global(address))
#> # A tibble: 10 × 2
#>            address is_public
#>          <ip_addr> <lgl>    
#>  1     7.74.223.20 TRUE     
#>  2   57.173.44.213 TRUE     
#>  3    77.188.8.153 TRUE     
#>  4    162.50.82.40 TRUE     
#>  5   122.251.102.1 TRUE     
#>  6  110.189.50.119 TRUE     
#>  7  180.13.103.127 TRUE     
#>  8 169.164.127.174 TRUE     
#>  9   46.178.99.187 TRUE     
#> 10  55.176.249.197 TRUE
```
