# IPv6 address space allocation

A dataset containing the registry of allocated blocks in IPv6 address
space.

## Usage

``` r
iana_ipv6
```

## Format

A data frame with 47 rows and 3 variables:

- network:

  Address block (an
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector)

- allocation:

  There are two types of allocation:

  - reserved

  - managed by regional Internet registry (RIR)

- label:

  The RIR or purpose for reservation

## Source

<https://www.iana.org/assignments/ipv6-address-space>

<https://www.iana.org/assignments/ipv6-unicast-address-assignments>

## Note

Last updated 2020-08-18

## See also

[`is_reserved()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)

## Examples

``` r
iana_ipv6
#> # A tibble: 47 × 3
#>           network allocation label   
#>        <ip_netwk> <fct>      <chr>   
#>  1          ::/3  Reserved   IETF    
#>  2      2001::/23 Managed    IANA    
#>  3  2001:200::/23 Managed    APNIC   
#>  4  2001:400::/23 Managed    ARIN    
#>  5  2001:600::/23 Managed    RIPE NCC
#>  6  2001:800::/22 Managed    RIPE NCC
#>  7  2001:c00::/22 Managed    APNIC   
#>  8 2001:1200::/23 Managed    LACNIC  
#>  9 2001:1400::/22 Managed    RIPE NCC
#> 10 2001:1800::/23 Managed    ARIN    
#> # ℹ 37 more rows
```
