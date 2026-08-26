# Country-level IP networks

Retrieve lists of IP networks registered to specific countries.

## Usage

``` r
country_networks(country, ..., collapse = TRUE)
```

## Source

<https://www.iwik.org/ipcountry/> (updated daily)

## Arguments

- country:

  Character vector of two-letter country codes (ISO 3166-1 alpha-2)

- ...:

  These dots are for future extensions and must be empty.

- collapse:

  If `TRUE` (the default), contiguous networks are collapsed. See
  [`collapse_networks()`](https://davidchall.github.io/ipaddress/dev/reference/collapse_networks.md).

## Value

A data frame with 2 variables:

- `country`: A character vector

- `network`: A list of
  [`ip_network`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vectors

Each row represents a single country associated with a vector of IP
networks.

## Details

This function requires an internet connection to download network lists.

## Examples

``` r
if (FALSE) { # \dontrun{
country_networks(c("GB", "US"))

country_networks(c("GB", "US"), collapse = FALSE)

# retrieve networks for a single country
country_networks("TO")$networks[[1]]

# expand networks for multiple countries
tidyr::unchop(country_networks(c("GB", "US")), networks)
} # }
```
