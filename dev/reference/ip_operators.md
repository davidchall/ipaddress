# Operators for IP addresses

[`ip_address`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
vectors support the following operators:

- bitwise logic operators: `!` (NOT), `&` (AND), `|` (OR), `^` (XOR)

- bitwise shift operators: `%<<%` (left shift), `%>>%` (right shift)

- arithmetic operators: `+` (addition), `-` (subtraction)

## Examples

``` r
# use ip_to_binary() to understand these examples better

# bitwise NOT
!ip_address("192.168.0.1")
#> <ip_address[1]>
#> [1] 63.87.255.254

# bitwise AND
ip_address("192.168.0.1") & ip_address("255.0.0.255")
#> <ip_address[1]>
#> [1] 192.0.0.1

# bitwise OR
ip_address("192.168.0.0") | ip_address("255.0.0.255")
#> <ip_address[1]>
#> [1] 255.168.0.255

# bitwise XOR
ip_address("192.168.0.0") ^ ip_address("255.0.0.255")
#> <ip_address[1]>
#> [1] 63.168.0.255

# bitwise shift left
ip_address("192.168.0.1") %<<% 1
#> <ip_address[1]>
#> [1] 129.80.0.2

# bitwise shift right
ip_address("192.168.0.1") %>>% 1
#> <ip_address[1]>
#> [1] 96.84.0.0

# addition of integers
ip_address("192.168.0.1") + 10
#> <ip_address[1]>
#> [1] 192.168.0.11

# subtraction of integers
ip_address("192.168.0.1") - 10
#> <ip_address[1]>
#> [1] 192.167.255.247
```
