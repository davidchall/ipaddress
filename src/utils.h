#ifndef __IPADDRESS_UTILS__
#define __IPADDRESS_UTILS__

#include <cstddef>
#include <array>
#include <algorithm>


template<class Address, class Network>
bool address_in_network(Address address, Network network) {
  return network.hosts().find(address) != network.hosts().end();
}

template<std::size_t N>
std::array<unsigned char, N> netmask_bytes(int prefix_length) {
  std::array<unsigned char, N> out;

  for (unsigned int i=0; i<sizeof(out); ++i) {
    int ingest = std::min(prefix_length, 8);
    uint8_t byte_mask = ingest == 0 ? 0 : (1 << 8) - (1 << (8 - ingest));

    std::memcpy(&out[i], &byte_mask, sizeof(byte_mask));

    prefix_length = std::max(prefix_length - 8, 0);
  }

  return out;
}

template<class Address, std::size_t N>
Address netmask(int prefix_length) {
  return Address(netmask_bytes<N>(prefix_length));
}

template<class Address, std::size_t N>
Address hostmask(int prefix_length) {
  std::array<unsigned char, N> hostmask_bytes = netmask_bytes<N>(prefix_length);

  for (unsigned int i=0; i<hostmask_bytes.size(); ++i) {
    hostmask_bytes[i] = ~hostmask_bytes[i];
  }

  return Address(hostmask_bytes);
}

#endif
