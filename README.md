
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

The goal of ipaddress is to provide classes for working with IP
addresses, which play nicely with the tidyverse. I plan to emulate some
of the features from Python’s
[`ipaddress`](https://docs.python.org/library/ipaddress.html) and
[`cyberpandas`](https://cyberpandas.readthedocs.io) modules.

Right now, my focus is on providing a working interface with unit tests.
Once this is working, I’ll move onto performance optimizations.

## Installation

You can install the released version of ipaddress from
[CRAN](https://CRAN.R-project.org) with:

``` r
install.packages("ipaddress")
```

## Example

Here’s how IP addresses can be stored within a tibble:

``` r
library(tibble)
library(ipaddress)

ip_str <- c("0.0.0.0", "0.0.0.1", "192.168.0.1", "255.255.255.255")

tibble(ip = ip_address(ip_str))
#> # A tibble: 4 x 1
#>                ip
#>         <ip_addr>
#> 1         0.0.0.0
#> 2         0.0.0.1
#> 3     192.168.0.1
#> 4 255.255.255.255
```
