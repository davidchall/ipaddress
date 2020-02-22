#ifndef __IPADDRESS_UTILS__
#define __IPADDRESS_UTILS__

#include <cstddef>
#include <array>
#include <algorithm>


template<class Address, class Network>
bool address_in_network(Address address, Network network) {
  return network.hosts().find(address) != network.hosts().end();
}

template<class Bytes>
Bytes netmask_bytes(int prefix_length) {
  Bytes out;

  for (unsigned int i=0; i<sizeof(out); ++i) {
    int ingest = std::min(prefix_length, 8);
    uint8_t byte_mask = ingest == 0 ? 0 : (1 << 8) - (1 << (8 - ingest));

    std::memcpy(&out[i], &byte_mask, sizeof(byte_mask));

    prefix_length = std::max(prefix_length - 8, 0);
  }

  return out;
}

template<class Address>
Address netmask(int prefix_length) {
  return Address(netmask_bytes<typename Address::bytes_type>(prefix_length));
}

template<class Address>
Address hostmask(int prefix_length) {
  typename Address::bytes_type hostmask_bytes = netmask_bytes<typename Address::bytes_type>(prefix_length);

  for (unsigned int i=0; i<hostmask_bytes.size(); ++i) {
    hostmask_bytes[i] = ~hostmask_bytes[i];
  }

  return Address(hostmask_bytes);
}

#endif
