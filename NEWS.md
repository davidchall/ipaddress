# ipaddress (development version)

# ipaddress 0.1.0

First CRAN release

* Added `ip_address` and `ip_network` classes
  * Full support for both IPv4 and IPv6 address spaces
  * Efficiently store data in their native representations (i.e. a sequence of bits)
  * Classes based on `vctrs` package for full tidyverse compatibility
* Added functions to determine network membership
  * `is_within()` and `is_within_any()` check if addresses are within networks
  * `is_subnet()` and `is_supernet()` check if networks are within other networks
* Added convenience functions to extract IP metadata
  * `is_ipv4()` and `is_ipv6()` classify the address space
  * `prefix_length()`, `netmask()` and `hostmask()` yield different representations of the network mask
* Calculations performed in C++ (using `Rcpp` and `AsioHeaders` packages) for improved performance
