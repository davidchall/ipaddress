# Remove networks from others

`exclude_networks()` takes lists of networks to include and exclude. It
then calculates the address ranges that are included but not excluded
(similar to [`base::setdiff()`](https://rdrr.io/r/base/sets.html)), and
finally returns the minimal set of networks needed to describe the
remaining address ranges.

## Usage

``` r
exclude_networks(include, exclude)
```

## Arguments

- include:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

- exclude:

  An
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vector

## Value

An
[`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
vector

## See also

[`collapse_networks()`](https://davidchall.github.io/ipaddress/dev/reference/collapse_networks.md),
[`base::setdiff()`](https://rdrr.io/r/base/sets.html)

## Examples

``` r
exclude_networks(ip_network("192.0.2.0/28"), ip_network("192.0.2.1/32"))
#> <ip_network[4]>
#> [1] 192.0.2.0/32 192.0.2.2/31 192.0.2.4/30 192.0.2.8/29

exclude_networks(ip_network("192.0.2.0/28"), ip_network("192.0.2.15/32"))
#> <ip_network[4]>
#> [1] 192.0.2.0/29  192.0.2.8/30  192.0.2.12/31 192.0.2.14/32
```
