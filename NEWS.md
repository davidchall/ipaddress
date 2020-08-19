# ipaddress (development version)

## New features

* Additional checks for reserved addresses/networks: `is_private()`, `is_reserved()`, `is_site_local()`
* New `is_global()` checks if addresses or networks are *not* reserved
* New `collapse_networks()` collapses contiguous and overlapping networks
* New bitwise shift operators: `%<<%` and `%>>%`
* Reorganized C++ code to expose `IpAddressVector` and `IpNetworkVector` classes to other packages (use `LinkingTo: AsioHeaders, ipaddress, Rcpp`). This does not effect the public R interface.

## Minor improvements and fixes

* `ip_to_integer()` gains a `base` parameter to select between decimal, hexadecimal and binary outputs
* Fixed comparison of `ip_address()` vectors (previously did not account for machine endianness)
* Comparison of `ip_network()` and `ip_interface()` vectors is now consistent with the Python ipaddress module
  * `ip_network()`: network address compared before prefix length
  * `ip_interface()`: network compared before host address


# ipaddress 0.4.0

## New features

* Add support for constructing `ip_network()` vectors without using CIDR notation
  * New `common_network()` function finds the smallest network containing two addresses
  * New `summarize_address_range()` function lists the constituent networks of an address range
  * `prefix_length()` can now infer the prefix length from an `ip_address()` vector of netmasks and/or hostmasks. This makes it possible to construct an `ip_network()` vector like so:
    * `ip_network(ip_address("192.0.2.0"), prefix_length(ip_address("255.255.255.0")))`
    * `ip_network(ip_address("192.0.2.0"), prefix_length(ip_address("0.0.0.255")))`
* New `supernet()` and `subnets()` functions for traversing the network hierarchy
* Added `vignette("ipaddress-examples")` to describe some typical usage patterns

## Minor improvements and fixes

* Check for user interrupts when processing large data sets
* `integer_to_ip()` now accepts integerish doubles
* Addition/subtraction operators now accept integerish doubles
* Addition/subtraction operators now catch missing values in 2nd argument
* `netmask()` and `hostmask()` now raise an error if the `prefix_length` and `is_ipv6` arguments are not both specified
* Fix `is_within_any()` to correctly catch when IPv6 addresses are in zero networks
* Rename `vignette("ipaddress")` as `vignette("ipaddress-classes")`


# ipaddress 0.3.0

##  Breaking changes

* Renamed functions for converting to and from alternative representations of IP addresses:
  * `as_packed()` and `from_packed()` become `ip_to_bytes()` and `bytes_to_ip()`
  * `as_binary()` and `from_binary()` become `ip_to_binary()` and `binary_to_ip()`
  * `as_hostname()` and `from_hostname()` become `ip_to_hostname()` and `hostname_to_ip()`

## New features

* New `ip_to_integer()` and `integer_to_ip()` functions to encode and decode addresses as integers. Note that the integers are contained within a character vector. Please see the function documentation for an explanation.

## Minor improvements

* Support pretty printing in tibbles
  * CIDRs aligned on forward slash separator
  * Prefix length displayed in green to increase prominence
  * Dots and colons displayed in gray to reduce prominence
  * IPv6 addresses can be automatically truncated, to fit more columns into the console width
* Added hex logo
* Compatible with vctrs 0.3.0


# ipaddress 0.2.0

## Classes

* Added `vignette("ipaddress")` to introduce the data classes provided by ipaddress
* New `ip_interface()` class to simultaneously store the address and the network it is on
* `ip_address()` vectors now support bitwise operations (`!`, `&`, `|` and `^`)
* `ip_address()` vectors now support addition and subtraction of integers
* Added an `ip_network()` constructor that accepts `ip_address` and prefix length vectors

## Other representations

* New `as_packed()` and `from_packed()` functions to encode and decode addresses as raw bytes
* New `as_binary()` and `from_binary()` functions to encode and decode addresses as binary strings
* New `as_hostname()` and `from_hostname()` functions translate addresses to and from hostnames

## Address space

* New `max_prefix_length()` function to get the size of the address space (32-bit for IPv4 and 128-bit for IPv6)
* New functions to check if addresses or networks are reserved for special use: `is_multicast()`, `is_unspecified()`, `is_loopback()`, `is_link_local()`
* New functions for IPv6 transition mechanisms:
  * `is_ipv4_mapped()`, `is_6to4()`, `is_teredo()`
  * `extract_ipv4_mapped()`, `extract_6to4()`, `extract_teredo_server()`, `extract_teredo_client()`

## Network membership

* New functions about the size of a network: `num_addresses()`, `network_address()` and `broadcast_address()`
* New `overlaps()` function to check for _any_ overlap between networks
* `netmask()` and `hostmask()` are now generics, so they can now accept:
  * an `ip_network()` vector (existing behavior)
  * an `ip_interface()` vector
  * a vector of prefix lengths

## Generating addresses

* New `seq.ip_network()` and `hosts()` functions to list all addresses within a network
* New functions to randomly sample addresses: `sample_ipv4()`, `sample_ipv6()` and `sample_network()`

## Miscellaneous improvements

* Improved input validation warnings. They now report the row number involved and no longer mention internal function names.
* Many functions now support [tidy vector recyling](https://vctrs.r-lib.org/reference/vec_recycle.html)
* Performance improvements


# ipaddress 0.1.2

* Fixed decoding bug which meant that some IP addresses were interpreted as `NA`
  * In IPv4, this affected `0.0.0.128`
  * In IPv6, this affected any address in the `0:80::/32` network
* `is_subnet()` and `is_supernet()` now check the prefix length, to ensure they are a true subnet or supernet.


# ipaddress 0.1.1

Hotfix for CRAN errors on Solaris.


# ipaddress 0.1.0

First CRAN release

* Added `ip_address()` and `ip_network()` classes
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
