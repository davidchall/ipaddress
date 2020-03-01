#ifndef __IPADDRESS_UTILS__
#define __IPADDRESS_UTILS__

#include <algorithm>


template<class Address, class Network>
bool address_in_network(Address address, Network network) {
  return network.hosts().find(address) != network.hosts().end();
}

template<class Bytes>
Bytes netmask_bytes(int prefix_length) {
  Bytes out;
  uint8_t mask_all = 0xff;

  for (unsigned int i=0; i<sizeof(out); ++i) {
    int ingest = std::min(prefix_length, 8);
    prefix_length -= ingest;

    uint8_t byte_mask = ingest == 0 ? 0 : mask_all << (8 - ingest);
    std::memcpy(&out[i], &byte_mask, sizeof(byte_mask));
  }

  return out;
}

template<class Address>
Address netmask(int prefix_length) {
  typedef typename Address::bytes_type Bytes;
  return Address(netmask_bytes<Bytes>(prefix_length));
}

template<class Address>
Address hostmask(int prefix_length) {
  typedef typename Address::bytes_type Bytes;
  Bytes bytes = netmask_bytes<Bytes>(prefix_length);

  // flip bits
  std::transform(bytes.begin(), bytes.end(), bytes.begin(), [](unsigned char c) { return ~c; });

  return Address(bytes);
}

#endif
