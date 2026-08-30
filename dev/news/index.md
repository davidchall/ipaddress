# Changelog

## ipaddress 1.0.4

Fix for CRAN checks.

## ipaddress 1.0.3

CRAN release: 2025-08-22

Fix for testthat deprecation warnings.

## ipaddress 1.0.2

CRAN release: 2023-12-01

Fix for CRAN checks.

## ipaddress 1.0.1

CRAN release: 2023-04-04

Fix for CRAN checks.

## ipaddress 1.0.0

CRAN release: 2023-01-12

To mark the release of ipaddress 1.0.0, some **breaking changes** were
made to improve the interface for data analysis.

### Breaking changes

- Removed the `multiple` argument from
  [`ip_to_hostname()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
  and
  [`hostname_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
  ([\#83](https://github.com/davidchall/ipaddress/issues/83)).
  - [`ip_to_hostname()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
    and
    [`hostname_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
    now always return one result per input (stored in a vector).
  - New
    [`ip_to_hostname_all()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
    and
    [`hostname_to_ip_all()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
    return all results per input (stored in a list of vectors).
- [`subnets()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
  now takes vector input and outputs a list of vectors
  ([\#83](https://github.com/davidchall/ipaddress/issues/83)).
- Some arguments must now be explicitly passed using the argument name:
  - The `strict` argument of
    [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md).
  - The `exploded` argument of
    [`format.ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md),
    [`format.ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md)
    and
    [`format.ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md).
  - The `replace` argument of
    [`sample_ipv4()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md),
    [`sample_ipv6()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
    and
    [`sample_network()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md).

### New features

- New
  [`country_networks()`](https://davidchall.github.io/ipaddress/dev/reference/country_networks.md)
  downloads IP networks registered to specific countries
  ([\#87](https://github.com/davidchall/ipaddress/issues/87)).
- Error formatting has been improved using {cli}
  ([\#86](https://github.com/davidchall/ipaddress/issues/86)).

### Minor improvements and fixes

- The `is_ipv6` argument of
  [`netmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  and
  [`hostmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  defaults to `NULL`. This option prefers an IPv4 mask, but creates an
  IPv6 mask as a fallback.
- Renamed `vignette("ipaddress-classes")` to
  [`vignette("ip-data")`](https://davidchall.github.io/ipaddress/dev/articles/ip-data.md).
- Renamed `vignette("ipaddress-examples")` to
  [`vignette("recipes")`](https://davidchall.github.io/ipaddress/dev/articles/recipes.md).
- Updated the `iana_ipv4` dataset.
- Tests now use {testthat} 3e.

## ipaddress 0.5.6

CRAN release: 2022-12-11

Fix for CRAN checks.

## ipaddress 0.5.5

CRAN release: 2022-08-12

Fix for CRAN checks.

## ipaddress 0.5.4

CRAN release: 2022-01-11

Fix for CRAN checks.

## ipaddress 0.5.3

CRAN release: 2021-07-27

Fix for CRAN checks.

## ipaddress 0.5.2

CRAN release: 2021-06-17

- The `base` argument of
  [`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  is removed.
  - `base = "dec"` is still handled by
    [`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md).
  - `base = "bin"` is still handled by the existing
    [`ip_to_binary()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md)
    function.
  - `base = "hex"` is now handled by the new
    [`ip_to_hex()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md)
    function.
- [`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  and
  [`integer_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  now use
  [`bignum::biginteger()`](https://davidchall.github.io/bignum/reference/biginteger.html)
  vectors to store IP addresses as integers. Previously, these integers
  were stored in a character vector (because they were beyond the range
  of base R numeric types).
  - The BH package is no longer a dependency (C++ Boost headers were a
    heavy dependency).
  - The bignum package is now an optional dependency.
- New
  [`ip_to_hex()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md)
  and
  [`hex_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md)
  functions to encode and decode addresses as hexadecimal strings.

## ipaddress 0.5.1

CRAN release: 2020-09-12

- Addition/subtraction of large integers is now much faster
  ([\#64](https://github.com/davidchall/ipaddress/issues/64)).
- [`ip_to_bytes()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md)
  now returns a list of raw vectors instead of a `blob` object
  ([\#65](https://github.com/davidchall/ipaddress/issues/65)).
  - Result can still be converted using
    [`blob::as_blob()`](https://blob.tidyverse.org/reference/blob.html).
  - Removes excessive blob package dependency.
- Refactored C++ code to reduce dependence on Asio library
  ([\#64](https://github.com/davidchall/ipaddress/issues/64)).
  - Package developers can now use `LinkingTo: ipaddress` without
    `LinkingTo: AsioHeaders`.

## ipaddress 0.5.0

CRAN release: 2020-08-26

This release achieves feature parity with the Python
[ipaddress](https://docs.python.org/3/library/ipaddress.html) module
([\#46](https://github.com/davidchall/ipaddress/issues/46)).

### New features

- Additional checks for reserved addresses/networks:
  [`is_private()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md),
  [`is_reserved()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md),
  [`is_site_local()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  ([\#49](https://github.com/davidchall/ipaddress/issues/49)).
- New
  [`is_global()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  checks if addresses or networks are *not* reserved
  ([\#49](https://github.com/davidchall/ipaddress/issues/49)).
- New
  [`collapse_networks()`](https://davidchall.github.io/ipaddress/dev/reference/collapse_networks.md)
  collapses contiguous and overlapping networks
  ([\#54](https://github.com/davidchall/ipaddress/issues/54)).
- New
  [`exclude_networks()`](https://davidchall.github.io/ipaddress/dev/reference/exclude_networks.md)
  removes networks from others
  ([\#59](https://github.com/davidchall/ipaddress/issues/59)).
- New
  [`reverse_pointer()`](https://davidchall.github.io/ipaddress/dev/reference/reverse_pointer.md)
  returns the record used by reverse DNS
  ([\#57](https://github.com/davidchall/ipaddress/issues/57)).
- New datasets: `iana_ipv4` and `iana_ipv6` contain registries of
  allocated blocks
  ([\#55](https://github.com/davidchall/ipaddress/issues/55)).
- New bitwise shift operators: `%<<%` and `%>>%`
  ([\#52](https://github.com/davidchall/ipaddress/issues/52)).
- Reorganized C++ code to expose `IpAddressVector` and `IpNetworkVector`
  classes to other packages (use
  `LinkingTo: AsioHeaders, ipaddress, Rcpp`). This does not affect the
  public R interface
  ([\#51](https://github.com/davidchall/ipaddress/issues/51)).

### Minor improvements and fixes

- [`format.ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md),
  [`format.ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md)
  and
  [`format.ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md)
  gain an `exploded` parameter to display leading zeros for IPv6
  addresses ([\#56](https://github.com/davidchall/ipaddress/issues/56)).
- [`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  gains a `base` parameter to select between decimal, hexadecimal and
  binary outputs
  ([\#47](https://github.com/davidchall/ipaddress/issues/47)).
- Integer-like doubles are now accepted everywhere in place of an
  integer.
- Update `vignette("ipaddress-examples")` to use the
  [fuzzyjoin](https://cran.r-project.org/package=fuzzyjoin) package
  ([\#61](https://github.com/davidchall/ipaddress/issues/61)).
- Update `vignette("ipaddress-examples")` with how to randomly generate
  public IP addresses
  ([\#62](https://github.com/davidchall/ipaddress/issues/62)).
- Fixed comparison of
  [`ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vectors to account for machine endianness
  ([\#53](https://github.com/davidchall/ipaddress/issues/53)).
- Comparison of
  [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  and
  [`ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
  vectors is now consistent with the Python ipaddress module.
  - [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md):
    network address compared before prefix length.
  - [`ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md):
    network compared before host address.

## ipaddress 0.4.0

CRAN release: 2020-08-06

### New features

- Add support for constructing
  [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  vectors without using CIDR notation.
  - New
    [`common_network()`](https://davidchall.github.io/ipaddress/dev/reference/common_network.md)
    function finds the smallest network containing two addresses
    ([\#39](https://github.com/davidchall/ipaddress/issues/39)).
  - New
    [`summarize_address_range()`](https://davidchall.github.io/ipaddress/dev/reference/summarize_address_range.md)
    function lists the constituent networks of an address range
    ([\#41](https://github.com/davidchall/ipaddress/issues/41)).
  - [`prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
    can now infer the prefix length from an
    [`ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
    vector of netmasks and/or hostmasks. This makes it possible to
    construct an
    [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
    vector like so:
    ([\#36](https://github.com/davidchall/ipaddress/issues/36))
    - `ip_network(ip_address("192.0.2.0"), prefix_length(ip_address("255.255.255.0")))`.
    - `ip_network(ip_address("192.0.2.0"), prefix_length(ip_address("0.0.0.255")))`.
- New
  [`supernet()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
  and
  [`subnets()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
  functions for traversing the network hierarchy
  ([\#42](https://github.com/davidchall/ipaddress/issues/42)).
- Added `vignette("ipaddress-examples")` to describe some typical usage
  patterns ([\#43](https://github.com/davidchall/ipaddress/issues/43)).

### Minor improvements and fixes

- Check for user interrupts when processing large data sets.
- [`integer_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  now accepts integerish doubles.
- Addition/subtraction operators now accept integerish doubles.
- Addition/subtraction operators now catch missing values in 2nd
  argument.
- [`netmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  and
  [`hostmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  now raise an error if the `prefix_length` and `is_ipv6` arguments are
  not both specified
  ([\#38](https://github.com/davidchall/ipaddress/issues/38)).
- Fix
  [`is_within_any()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
  to correctly catch when IPv6 addresses are in zero networks.
- Rename `vignette("ipaddress")` as `vignette("ipaddress-classes")`.

## ipaddress 0.3.0

CRAN release: 2020-05-12

### Breaking changes

- Renamed functions for converting to and from alternative
  representations of IP addresses:
  ([\#30](https://github.com/davidchall/ipaddress/issues/30))
  - `as_packed()` and `from_packed()` become
    [`ip_to_bytes()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md)
    and
    [`bytes_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md).
  - `as_binary()` and `from_binary()` become
    [`ip_to_binary()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md)
    and
    [`binary_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md).
  - `as_hostname()` and `from_hostname()` become
    [`ip_to_hostname()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
    and
    [`hostname_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md).

### New features

- New
  [`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  and
  [`integer_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  functions to encode and decode addresses as integers. Note that the
  integers are contained within a character vector. Please see the
  function documentation for an explanation
  ([\#30](https://github.com/davidchall/ipaddress/issues/30)).

### Minor improvements

- Support pretty printing in tibbles
  ([\#27](https://github.com/davidchall/ipaddress/issues/27)).
  - CIDRs aligned on forward slash separator.
  - Prefix length displayed in green to increase prominence.
  - Dots and colons displayed in gray to reduce prominence.
  - IPv6 addresses can be automatically truncated, to fit more columns
    into the console width.
- Added hex logo.
- Compatible with vctrs 0.3.0
  ([\#31](https://github.com/davidchall/ipaddress/issues/31),
  [\#34](https://github.com/davidchall/ipaddress/issues/34)).

## ipaddress 0.2.0

CRAN release: 2020-03-25

### Classes

- Added `vignette("ipaddress")` to introduce the data classes provided
  by ipaddress
  ([\#24](https://github.com/davidchall/ipaddress/issues/24)).
- New
  [`ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
  class to simultaneously store the address and the network it is on
  ([\#15](https://github.com/davidchall/ipaddress/issues/15)).
- [`ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vectors now support bitwise operations (`!`, `&`, `|` and `^`).
- [`ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  vectors now support addition and subtraction of integers
  ([\#14](https://github.com/davidchall/ipaddress/issues/14)).
- Added an
  [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  constructor that accepts `ip_address` and prefix length vectors
  ([\#9](https://github.com/davidchall/ipaddress/issues/9)).

### Other representations

- New `as_packed()` and `from_packed()` functions to encode and decode
  addresses as raw bytes
  ([\#13](https://github.com/davidchall/ipaddress/issues/13)).
- New `as_binary()` and `from_binary()` functions to encode and decode
  addresses as binary strings
  ([\#18](https://github.com/davidchall/ipaddress/issues/18)).
- New `as_hostname()` and `from_hostname()` functions translate
  addresses to and from hostnames
  ([\#22](https://github.com/davidchall/ipaddress/issues/22)).

### Address space

- New
  [`max_prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/max_prefix_length.md)
  function to get the size of the address space (32-bit for IPv4 and
  128-bit for IPv6).
- New functions to check if addresses or networks are reserved for
  special use:
  [`is_multicast()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md),
  [`is_unspecified()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md),
  [`is_loopback()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md),
  [`is_link_local()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md).
- New functions for IPv6 transition mechanisms:
  ([\#16](https://github.com/davidchall/ipaddress/issues/16))
  - [`is_ipv4_mapped()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md),
    [`is_6to4()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md),
    [`is_teredo()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md).
  - [`extract_ipv4_mapped()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md),
    [`extract_6to4()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md),
    [`extract_teredo_server()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md),
    [`extract_teredo_client()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md).

### Network membership

- New functions about the size of a network:
  [`num_addresses()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md),
  [`network_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
  and
  [`broadcast_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md).
- New
  [`overlaps()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
  function to check for *any* overlap between networks.
- [`netmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  and
  [`hostmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  are now generics, so they can now accept:
  - an
    [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
    vector (existing behavior).
  - an
    [`ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
    vector.
  - a vector of prefix lengths.

### Generating addresses

- New
  [`seq.ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/sequence.md)
  and
  [`hosts()`](https://davidchall.github.io/ipaddress/dev/reference/sequence.md)
  functions to list all addresses within a network.
- New functions to randomly sample addresses:
  [`sample_ipv4()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md),
  [`sample_ipv6()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
  and
  [`sample_network()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
  ([\#11](https://github.com/davidchall/ipaddress/issues/11),
  [\#19](https://github.com/davidchall/ipaddress/issues/19)).

### Miscellaneous improvements

- Improved input validation warnings. They now report the row number
  involved and no longer mention internal function names.
- Many functions now support [tidy vector
  recyling](https://vctrs.r-lib.org/reference/vec_recycle.html).
- Performance improvements.

## ipaddress 0.1.2

CRAN release: 2020-03-10

- Fixed decoding bug which meant that some IP addresses were interpreted
  as `NA`.
  - In IPv4, this affected `0.0.0.128`.
  - In IPv6, this affected any address in the `0:80::/32` network.
- [`is_subnet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
  and
  [`is_supernet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
  now check the prefix length, to ensure they are a true subnet or
  supernet.

## ipaddress 0.1.1

CRAN release: 2020-03-06

Fix for CRAN checks.

## ipaddress 0.1.0

CRAN release: 2020-03-05

First CRAN release

- Added
  [`ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  and
  [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  classes.
  - Full support for both IPv4 and IPv6 address spaces.
  - Efficiently store data in their native representations (i.e. a
    sequence of bits).
  - Classes based on `vctrs` package for full tidyverse compatibility.
- Added functions to determine network membership.
  - [`is_within()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
    and
    [`is_within_any()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
    check if addresses are within networks.
  - [`is_subnet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
    and
    [`is_supernet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
    check if networks are within other networks.
- Added convenience functions to extract IP metadata.
  - [`is_ipv4()`](https://davidchall.github.io/ipaddress/dev/reference/is_ipv6.md)
    and
    [`is_ipv6()`](https://davidchall.github.io/ipaddress/dev/reference/is_ipv6.md)
    classify the address space.
  - [`prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md),
    [`netmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
    and
    [`hostmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
    yield different representations of the network mask.
- Calculations performed in C++ (using `Rcpp` and `AsioHeaders`
  packages) for improved performance.
