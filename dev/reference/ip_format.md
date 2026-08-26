# Format IP vector

Format vector of IP data using compressed or exploded representation.

## Usage

``` r
# S3 method for class 'ip_address'
format(x, ..., exploded = FALSE)

# S3 method for class 'ip_interface'
format(x, ..., exploded = FALSE)

# S3 method for class 'ip_network'
format(x, ..., exploded = FALSE)
```

## Arguments

- x:

  An object to format

- ...:

  These dots are for future extensions and must be empty.

- exploded:

  Logical scalar. Should IPv6 addresses display leading zeros? (default:
  `FALSE`)

## Value

A character vector

## Examples

``` r
format(ip_address("2001:db8::8a2e:370:7334"))
#> [1] "2001:db8::8a2e:370:7334"

format(ip_address("2001:db8::8a2e:370:7334"), exploded = TRUE)
#> [1] "2001:0db8:0000:0000:0000:8a2e:0370:7334"
```
