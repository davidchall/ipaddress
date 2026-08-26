# Package index

## Data classes

- [`ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_address.md)
  : Vector of IP addresses
- [`ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_network.md)
  : Vector of IP networks
- [`ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_interface.md)
  : Vector of IP interfaces
- [`is_ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_test.md)
  [`is_ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_test.md)
  [`is_ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_test.md)
  : Test for IP vector
- [`as_ip_address()`](https://davidchall.github.io/ipaddress/dev/reference/ip_cast.md)
  [`as_ip_interface()`](https://davidchall.github.io/ipaddress/dev/reference/ip_cast.md)
  [`as_ip_network()`](https://davidchall.github.io/ipaddress/dev/reference/ip_cast.md)
  : Cast to IP vector
- [`format(`*`<ip_address>`*`)`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md)
  [`format(`*`<ip_interface>`*`)`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md)
  [`format(`*`<ip_network>`*`)`](https://davidchall.github.io/ipaddress/dev/reference/ip_format.md)
  : Format IP vector

## Other representations

- [`ip_to_binary()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md)
  [`binary_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_binary.md)
  : Represent address as binary
- [`ip_to_bytes()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md)
  [`bytes_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_bytes.md)
  : Represent address as raw bytes
- [`ip_to_hex()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md)
  [`hex_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hex.md)
  : Represent address as hexadecimal
- [`ip_to_integer()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  [`integer_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_integer.md)
  : Represent address as integer
- [`ip_to_hostname()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
  [`ip_to_hostname_all()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
  [`hostname_to_ip()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
  [`hostname_to_ip_all()`](https://davidchall.github.io/ipaddress/dev/reference/ip_to_hostname.md)
  : Translate address to/from hostname
- [`reverse_pointer()`](https://davidchall.github.io/ipaddress/dev/reference/reverse_pointer.md)
  : Reverse DNS pointer

## Address space

- [`is_ipv4()`](https://davidchall.github.io/ipaddress/dev/reference/is_ipv6.md)
  [`is_ipv6()`](https://davidchall.github.io/ipaddress/dev/reference/is_ipv6.md)
  : Version of the address space
- [`max_prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/max_prefix_length.md)
  : Size of the address space
- [`is_private()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  [`is_global()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  [`is_multicast()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  [`is_unspecified()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  [`is_reserved()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  [`is_loopback()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  [`is_link_local()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  [`is_site_local()`](https://davidchall.github.io/ipaddress/dev/reference/is_reserved.md)
  : Reserved addresses
- [`is_ipv4_mapped()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)
  [`is_6to4()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)
  [`is_teredo()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)
  [`extract_ipv4_mapped()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)
  [`extract_6to4()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)
  [`extract_teredo_server()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)
  [`extract_teredo_client()`](https://davidchall.github.io/ipaddress/dev/reference/ipv6-transition.md)
  : IPv6 transition mechanisms
- [`ip_operators`](https://davidchall.github.io/ipaddress/dev/reference/ip_operators.md)
  [`%<<%`](https://davidchall.github.io/ipaddress/dev/reference/ip_operators.md)
  [`%>>%`](https://davidchall.github.io/ipaddress/dev/reference/ip_operators.md)
  : Operators for IP addresses

## Network membership

- [`network_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
  [`broadcast_address()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
  [`num_addresses()`](https://davidchall.github.io/ipaddress/dev/reference/network_size.md)
  : Network size
- [`prefix_length()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  [`netmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  [`hostmask()`](https://davidchall.github.io/ipaddress/dev/reference/netmask.md)
  : Network mask
- [`common_network()`](https://davidchall.github.io/ipaddress/dev/reference/common_network.md)
  : Find the common network of two addresses
- [`is_within()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
  [`is_within_any()`](https://davidchall.github.io/ipaddress/dev/reference/address_in_network.md)
  : Network membership of addresses
- [`is_supernet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
  [`is_subnet()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
  [`overlaps()`](https://davidchall.github.io/ipaddress/dev/reference/network_in_network.md)
  : Network membership of other networks
- [`supernet()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
  [`subnets()`](https://davidchall.github.io/ipaddress/dev/reference/traverse_hierarchy.md)
  : Traverse the network hierarchy

## Address ranges

- [`summarize_address_range()`](https://davidchall.github.io/ipaddress/dev/reference/summarize_address_range.md)
  : List constituent networks of an address range
- [`collapse_networks()`](https://davidchall.github.io/ipaddress/dev/reference/collapse_networks.md)
  : Collapse contiguous and overlapping networks
- [`exclude_networks()`](https://davidchall.github.io/ipaddress/dev/reference/exclude_networks.md)
  : Remove networks from others

## Generating addresses

- [`sample_ipv4()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
  [`sample_ipv6()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
  [`sample_network()`](https://davidchall.github.io/ipaddress/dev/reference/sample.md)
  : Sample random addresses
- [`seq(`*`<ip_network>`*`)`](https://davidchall.github.io/ipaddress/dev/reference/sequence.md)
  [`hosts()`](https://davidchall.github.io/ipaddress/dev/reference/sequence.md)
  : List addresses within a network

## Datasets

- [`country_networks()`](https://davidchall.github.io/ipaddress/dev/reference/country_networks.md)
  : Country-level IP networks
- [`iana_ipv4`](https://davidchall.github.io/ipaddress/dev/reference/iana_ipv4.md)
  : IPv4 address space allocation
- [`iana_ipv6`](https://davidchall.github.io/ipaddress/dev/reference/iana_ipv6.md)
  : IPv6 address space allocation
