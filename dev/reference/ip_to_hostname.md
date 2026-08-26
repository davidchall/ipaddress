# Translate address to/from hostname

Perform reverse and forward DNS resolution.

**Note:** These functions are significantly slower than others in the
ipaddress package.

## Usage

``` r
ip_to_hostname(x)

ip_to_hostname_all(x)

hostname_to_ip(x)

hostname_to_ip_all(x)
```

## Arguments

- x:

  - `ip_to_hostname()`: An
    [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
    vector

  - `hostname_to_ip()`: A character vector of hostnames

## Value

- `ip_to_hostname()`: A character vector

- `ip_to_hostname_all()`: A list of character vectors

- `hostname_to_ip()`: An
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vector

- `hostname_to_ip_all()`: A list of
  [`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vectors

## Details

These functions require an internet connection. Before processing the
input vector, we first check that a known hostname can be resolved. If
this fails, an error is raised.

If DNS lookup cannot resolve an input, then `NA` is returned for that
input. If an error occurs during DNS lookup, then a warning is emitted
and `NA` is returned for that input.

DNS resolution performs a many-to-many mapping between IP addresses and
hostnames. For this reason, there are two versions of each function. The
regular version returns just the first value and the `_all()` suffix
version returns all values.

## See also

The base function [`nsl()`](https://rdrr.io/r/utils/nsl.html) provides
forward DNS resolution to IPv4 addresses, but only on Unix-like systems.

## Examples

``` r
if (FALSE) { # \dontrun{
hostname_to_ip("r-project.org")

ip_to_hostname(hostname_to_ip("r-project.org"))
} # }
```
