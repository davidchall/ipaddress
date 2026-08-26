# IPv4 address space allocation

A dataset containing the registry of allocated blocks in IPv4 address
space.

## Usage

``` r
iana_ipv4
```

## Format

A data frame with 121 rows and 3 variables:

- network:

  Address block (an
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector)

- allocation:

  There are three types of allocation:

  - reserved

  - managed by regional Internet registry (RIR)

  - assigned to organization

- label:

  The RIR, organization or purpose for reservation

## Source

<https://www.iana.org/assignments/ipv4-address-space>

## Note

Last updated 2022-12-12

## See also

[`is_reserved()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)

## Examples

``` r
iana_ipv4
#> # A tibble: 121 × 3
#>       network allocation label             
#>    <ip_netwk> <fct>      <chr>             
#>  1  0.0.0.0/8 Reserved   Reserved          
#>  2  1.0.0.0/8 Managed    APNIC             
#>  3  2.0.0.0/8 Managed    RIPE NCC          
#>  4  3.0.0.0/8 Managed    Various registries
#>  5  4.0.0.0/8 Managed    Various registries
#>  6  5.0.0.0/8 Managed    RIPE NCC          
#>  7  6.0.0.0/8 Assigned   US DoD            
#>  8  7.0.0.0/8 Managed    Various registries
#>  9  8.0.0.0/7 Managed    Various registries
#> 10 10.0.0.0/8 Reserved   Reserved          
#> # ℹ 111 more rows
```
