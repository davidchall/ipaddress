
<!-- README.md is generated from README.Rmd. Please edit that file -->

# ipaddress

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![CRAN
status](https://www.r-pkg.org/badges/version/ipaddress)](https://CRAN.R-project.org/package=ipaddress)
[![R build
status](https://github.com/davidchall/ipaddress/workflows/R-CMD-check/badge.svg)](https://github.com/davidchall/ipaddress/actions)
[![codecov.io](https://codecov.io/github/davidchall/ipaddress/coverage.svg?branch=master)](https://codecov.io/github/davidchall/ipaddress?branch=master)
<!-- badges: end -->

The ipaddress package provides classes for storing IP addresses and
networks. Its interface is inspired by Python’s
[`ipaddress`](https://docs.python.org/library/ipaddress.html) and
[`cyberpandas`](https://cyberpandas.readthedocs.io) modules.

Here are some of the features:

  - IP addresses are stored in their native representation (a sequence
    of bits) for **efficient data storage**
  - Calculations are performed in C++ for **improved performance**
  - Classes are **compatible with the tidyverse**
  - Supports both **IPv4 and IPv6** address spaces

## Installation

You can install the released version of ipaddress from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("ipaddress")
```

Or you can install the development version from GitHub:

``` r
# install.packages("remotes")
remotes::install_github("davidchall/ipaddress")
```

## Usage

This package provides the `ip_address` and `ip_network` classes, which
can be used as standalone vectors or as columns within data frames and
tibbles.

``` r
library(tidyverse)
library(ipaddress)

ip_address(c("0.0.0.1", "192.168.0.1", "2001:db8::8a2e:370:7334"))
#> <ip_address[3]>
#> [1] 0.0.0.1                 192.168.0.1             2001:db8::8a2e:370:7334

tibble(
  address = ip_address(c("0.0.0.1", "192.168.0.1", "2001:db8::8a2e:370:7334")),
  network = ip_network(c("92.0.2.0/24", "192.168.100.0/22", "2001:db8::/48"))
)
#> # A tibble: 3 x 2
#>                   address          network
#>                 <ip_addr>        <ip_netw>
#> 1                 0.0.0.1      92.0.2.0/24
#> 2             192.168.0.1 192.168.100.0/22
#> 3 2001:db8::8a2e:370:7334    2001:db8::/48
```

Input character vectors are automatically validated as they are parsed.
Invalid inputs raise a warning and are replaced with `NA`.

``` r
ip_address(c("0.0.0.0", "255.255.255.255", "255.255.255.256"))
#> Warning in address_aton(x): Invalid argument: 255.255.255.256
#> <ip_address[3]>
#> [1] 0.0.0.0         255.255.255.255 <NA>
```
