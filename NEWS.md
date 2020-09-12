# ipaddress 0.5.1

* Addition/subtraction of large integers is now much faster (#64)
* `ip_to_bytes()` now returns a list of raw vectors instead of a `blob` object (#65)
  * Result can still be converted using `blob::as_blob()`
  * Removes excessive blob package dependency
* Refactored C++ code to reduce dependence on Asio library (#64)
  * Package developers can now use `LinkingTo: ipaddress` without `LinkingTo: AsioHeaders`


# ipaddress 0.5.0

This release achieves feature parity with the Python [ipaddress](https://docs.python.org/3/library/ipaddress.html) module (#46).

## New features

* Additional checks for reserved addresses/networks: `is_private()`, `is_reserved()`, `is_site_local()` (#49)
* New `is_global()` checks if addresses or networks are *not* reserved (#49)
* New `collapse_networks()` collapses contiguous and overlapping networks (#54)
* New `exclude_networks()` removes networks from others (#59)
* New `reverse_pointer()` returns the record used by reverse DNS (#57)
* New datasets: `iana_ipv4` and `iana_ipv6` contain registries of allocated blocks (#55)
* New bitwise shift operators: `%<<%` and `%>>%` (#52)
* Reorganized C++ code to expose `IpAddressVector` and `IpNetworkVector` classes to other packages (use `LinkingTo: AsioHeaders, ipaddress, Rcpp`). This does not affect the public R interface. (#51)

## Minor improvements and fixes

* `format.ip_address()`, `format.ip_network()` and `format.ip_interface()` gain an `exploded` parameter to display leading zeros for IPv6 addresses (#56)
* `ip_to_integer()` gains a `base` parameter to select between decimal, hexadecimal and binary outputs (#47)
* Integer-like doubles are now accepted everywhere in place of an integer
* Update `vignette("ipaddress-examples")` to use the [fuzzyjoin](https://cran.r-project.org/package=fuzzyjoin) package (#61)
* Update `vignette("ipaddress-examples")` with how to randomly generate public IP addresses (#62)
* Fixed comparison of `ip_address()` vectors to account for machine endianness (#53)
* Comparison of `ip_network()` and `ip_interface()` vectors is now consistent with the Python ipaddress module
  * `ip_network()`: network address compared before prefix length
  * `ip_interface()`: network compared before host address


# ipaddress 0.4.0

## New features

* Add support for constructing `ip_network()` vectors without using CIDR notation
  * New `common_network()` function finds the smallest network containing two addresses (#39)
  * New `summarize_address_range()` function lists the constituent networks of an address range (#41)
  * `prefix_length()` can now infer the prefix length from an `ip_address()` vector of netmasks and/or hostmasks. This makes it possible to construct an `ip_network()` vector like so: (#36)
    * `ip_network(ip_address("192.0.2.0"), prefix_length(ip_address("255.255.255.0")))`
    * `ip_network(ip_address("192.0.2.0"), prefix_length(ip_address("0.0.0.255")))`
* New `supernet()` and `subnets()` functions for traversing the network hierarchy (#42)
* Added `vignette("ipaddress-examples")` to describe some typical usage patterns (#43)

## Minor improvements and fixes

* Check for user interrupts when processing large data sets
* `integer_to_ip()` now accepts integerish doubles
* Addition/subtraction operators now accept integerish doubles
* Addition/subtraction operators now catch missing values in 2nd argument
* `netmask()` and `hostmask()` now raise an error if the `prefix_length` and `is_ipv6` arguments are not both specified (#38)
* Fix `is_within_any()` to correctly catch when IPv6 addresses are in zero networks
* Rename `vignette("ipaddress")` as `vignette("ipaddress-classes")`


# ipaddress 0.3.0

##  Breaking changes

* Renamed functions for converting to and from alternative representations of IP addresses: (#30)
  * `as_packed()` and `from_packed()` become `ip_to_bytes()` and `bytes_to_ip()`
  * `as_binary()` and `from_binary()` become `ip_to_binary()` and `binary_to_ip()`
  * `as_hostname()` and `from_hostname()` become `ip_to_hostname()` and `hostname_to_ip()`

## New features

* New `ip_to_integer()` and `integer_to_ip()` functions to encode and decode addresses as integers. Note that the integers are contained within a character vector. Please see the function documentation for an explanation. (#30)

## Minor improvements

* Support pretty printing in tibbles (#27)
  * CIDRs aligned on forward slash separator
  * Prefix length displayed in green to increase prominence
  * Dots and colons displayed in gray to reduce prominence
  * IPv6 addresses can be automatically truncated, to fit more columns into the console width
* Added hex logo
* Compatible with vctrs 0.3.0 (#31, #34)


# ipaddress 0.2.0

## Classes

* Added `vignette("ipaddress")` to introduce the data classes provided by ipaddress (#24)
* New `ip_interface()` class to simultaneously store the address and the network it is on (#15)
* `ip_address()` vectors now support bitwise operations (`!`, `&`, `|` and `^`)
* `ip_address()` vectors now support addition and subtraction of integers (#14)
* Added an `ip_network()` constructor that accepts `ip_address` and prefix length vectors (#9)

## Other representations

* New `as_packed()` and `from_packed()` functions to encode and decode addresses as raw bytes (#13)
* New `as_binary()` and `from_binary()` functions to encode and decode addresses as binary strings (#18)
* New `as_hostname()` and `from_hostname()` functions translate addresses to and from hostnames (#22)

## Address space

* New `max_prefix_length()` function to get the size of the address space (32-bit for IPv4 and 128-bit for IPv6)
* New functions to check if addresses or networks are reserved for special use: `is_multicast()`, `is_unspecified()`, `is_loopback()`, `is_link_local()`
* New functions for IPv6 transition mechanisms: (#16)
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
* New functions to randomly sample addresses: `sample_ipv4()`, `sample_ipv6()` and `sample_network()` (#11, #19)

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
