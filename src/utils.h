#ifndef __IPADDRESS_UTILS__
#define __IPADDRESS_UTILS__

#include <algorithm>


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
Address netmask(unsigned int prefix_length) {
  typedef typename Address::bytes_type Bytes;
  return Address(netmask_bytes<Bytes>(prefix_length));
}

template<class Address>
Address hostmask(unsigned int prefix_length) {
  typedef typename Address::bytes_type Bytes;
  Bytes bytes = netmask_bytes<Bytes>(prefix_length);

  // flip bits
  std::transform(bytes.begin(), bytes.end(), bytes.begin(), [](unsigned char c) { return ~c; });

  return Address(bytes);
}

template<class Address, class Network>
Address broadcast_address(const Network &network) {
  typedef typename Address::bytes_type Bytes;
  Bytes network_bytes = network.address().to_bytes();
  Bytes hostmask_bytes = hostmask<Address>(network.prefix_length()).to_bytes();
  Bytes broadcast_bytes;

  std::transform(network_bytes.begin(), network_bytes.end(), hostmask_bytes.begin(), broadcast_bytes.begin(),
                 [](unsigned char net, unsigned char mask) { return net | mask; });

  return Address(broadcast_bytes);
}

template<class Address, class Network>
bool address_in_network(const Address &address, const Network &network) {
  typedef typename Address::bytes_type Bytes;
  Bytes address_bytes = address.to_bytes();
  Bytes network_bytes = network.address().to_bytes();
  Bytes netmask_bytes2 = netmask_bytes<Bytes>(network.prefix_length());

  for (unsigned int i=0; i<address_bytes.size(); ++i) {
    if ((address_bytes[i] & netmask_bytes2[i]) != network_bytes[i]) {
      return false;
    }
  }

  return true;
}

#endif
