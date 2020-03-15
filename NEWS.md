# ipaddress (development version)

## New features

### Classes

* New `ip_interface()` class to simultaneously store the address and the network it is on
* `ip_address()` vectors now support bitwise operations (`!`, `&`, `|` and `^`)
* `ip_address()` vectors now support addition and subtraction of integers
* Added an `ip_network()` constructor that accepts `ip_address` and prefix length vectors

### Other representations

* New `packed()` and `unpack()` functions to encode and decode addresses as raw bytes

### Address spaces

* New `max_prefix_length()` function to get the size of the address space (32-bit for IPv4 and 128-bit for IPv6)
* New functions to check if addresses or networks are reserved for special use: `is_multicast()`, `is_unspecified()`, `is_loopback()`, `is_link_local()`
* New functions for IPv6 transition mechanisms: `is_ipv4_mapped()`, `is_6to4()`, `is_teredo()`, `extract_ipv4_mapped()`, `extract_6to4()`, `extract_teredo_server()`, `extract_teredo_client()`

### Network membership

* New functions about the size of a network: `num_addresses()`, `network_address()` and `broadcast_address()`
* New `overlaps()` function to check for _any_ overlap between networks
* `netmask()` and `hostmask()` are now generics, so they can now accept either an `ip_network` vector or a vector of prefix lengths. Previously they only accepted an `ip_network` vector.

### Generating addresses

* New `seq.ip_network()` and `hosts()` functions to list all addresses within a network
* New functions to randomly sample addresses: `sample_ipv4()`, `sample_ipv6()` and `sample_network()`

## Minor improvements

* Improved input validation warnings. They now report the row number involved and no longer mention internal function names.
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
