#ifndef __IPADDRESS_MASKING__
#define __IPADDRESS_MASKING__

#include <ipaddress/IpAddress.h>
#include <ipaddress/IpNetwork.h>
#include <ipaddress/bitwise.h>
#include <ipaddress/count_zeros.h>


namespace ipaddress {

inline IpAddress prefix_to_netmask(unsigned int prefix_length, bool is_ipv6) {
  IpAddress result = is_ipv6 ? IpAddress::make_ipv6() : IpAddress::make_ipv4();

  unsigned int bits_to_ingest = prefix_length;
  for (auto it = result.begin(); it != result.end(); ++it) {
    if (bits_to_ingest == 0) {
      break;
    } else if (bits_to_ingest >= CHAR_BIT) {
      *it = 0xFF;
      bits_to_ingest -= CHAR_BIT;
    } else {
      *it = 0xFF << (CHAR_BIT - bits_to_ingest);
      bits_to_ingest = 0;
    }
  }

  return result;
}

inline IpAddress prefix_to_hostmask(unsigned int prefix_length, bool is_ipv6) {
  return bitwise_not(prefix_to_netmask(prefix_length, is_ipv6));
}

inline int netmask_to_prefix(const IpAddress &mask) {
  int trailing_zeros = count_trailing_zero_bits(mask);
  int prefix = mask.n_bits() - trailing_zeros;

  // catch non-mask addresses (mixed zeros and ones)
  const IpAddress valid_mask = prefix_to_netmask(prefix, mask.is_ipv6());
  return mask == valid_mask ? prefix : -1;
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

inline bool is_subnet(const IpNetwork &network, const IpNetwork &other) {
  return address_in_network(network.address(), other)
    && (network.prefix_length() >= other.prefix_length());
}

}

#endif
