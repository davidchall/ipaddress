#ifndef __IPADDRESS_MASKING__
#define __IPADDRESS_MASKING__

#include <algorithm>
#include <ipaddress/IpAddress.h>
#include <ipaddress/IpNetwork.h>
#include <ipaddress/bitwise.h>
#include <ipaddress/count_zeros.h>


namespace ipaddress {

inline IpAddress prefix_to_netmask(int prefix_length, bool is_ipv6) {
  IpAddress result = is_ipv6 ? IpAddress::make_ipv6() : IpAddress::make_ipv4();

  for (std::size_t i=0; i<result.n_bytes(); ++i) {
    int ingest = std::min(prefix_length, 8);
    prefix_length -= ingest;

    uint8_t byte_mask = ingest == 0 ? 0 : 0xff << (8 - ingest);
    std::memcpy(&result.bytes[i], &byte_mask, sizeof(byte_mask));
  }

  return result;
}

inline IpAddress prefix_to_hostmask(int prefix_length, bool is_ipv6) {
  return bitwise_not(prefix_to_netmask(prefix_length, is_ipv6));
}

inline int netmask_to_prefix(const IpAddress &mask) {
  int trailing_zeros = count_trailing_zero_bits(mask);
  int prefix = mask.n_bits() - trailing_zeros;

  // catch non-mask addresses (mixed zeros and ones)
  const IpAddress valid_mask = prefix_to_netmask(prefix, mask.is_ipv6());
  return mask == valid_mask ? prefix: -1;
}

inline int hostmask_to_prefix(const IpAddress &mask) {
  return netmask_to_prefix(bitwise_not(mask));
}

inline IpAddress broadcast_address(const IpNetwork &network) {
  if (network.is_na()) {
    return IpAddress::make_na();
  }
  IpAddress hostmask = prefix_to_hostmask(network.prefix_length(), network.is_ipv6());
  return bitwise_or(network.address(), hostmask);
}

inline bool address_in_network(const IpAddress &address, const IpNetwork &network) {
  if (address.is_na() || network.is_na()) {
    return false;
  }
  if (address.is_ipv6() != network.is_ipv6()) {
    return false;
  }
  IpAddress netmask = prefix_to_netmask(network.prefix_length(), network.is_ipv6());
  return bitwise_and(address, netmask) == network.address();
}

}

#endif
