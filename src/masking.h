#ifndef __IPADDRESS_MASKING__
#define __IPADDRESS_MASKING__

#include <algorithm>


/*---------------------*
 *  Bitwise operators  *
 *---------------------*/

template<class Address>
Address bitwise_not(const Address &addr1) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), result_bytes.begin(),
                 [](unsigned char b1) { return ~b1; });

  return Address(result_bytes);
}

template<class Address>
Address bitwise_and(const Address &addr1, const Address &addr2) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes addr2_bytes = addr2.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), addr2_bytes.begin(), result_bytes.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 & b2; });

  return Address(result_bytes);
}

template<class Address>
Address bitwise_or(const Address &addr1, const Address &addr2) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes addr2_bytes = addr2.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), addr2_bytes.begin(), result_bytes.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 | b2; });

  return Address(result_bytes);
}

template<class Address>
Address bitwise_xor(const Address &addr1, const Address &addr2) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes addr2_bytes = addr2.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), addr2_bytes.begin(), result_bytes.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 ^ b2; });

  return Address(result_bytes);
}


/*--------------*
 *  IP masking  *
 *--------------*/

template<class Address>
Address get_netmask(int prefix_length) {
  typedef typename Address::bytes_type Bytes;
  Bytes result_bytes;

  for (std::size_t i=0; i<sizeof(result_bytes); ++i) {
    int ingest = std::min(prefix_length, 8);
    prefix_length -= ingest;

    uint8_t byte_mask = ingest == 0 ? 0 : 0xff << (8 - ingest);
    std::memcpy(&result_bytes[i], &byte_mask, sizeof(byte_mask));
  }

  return Address(result_bytes);
}

template<class Address>
Address get_hostmask(int prefix_length) {
  return bitwise_not(get_netmask<Address>(prefix_length));
}

template<class Address, class Network>
Address broadcast_address(const Network &network) {
  Address hostmask = get_hostmask<Address>(network.prefix_length());
  return bitwise_or(network.address(), hostmask);
}

template<class Address, class Network>
bool address_in_network(const Address &address, const Network &network) {
  Address netmask = get_netmask<Address>(network.prefix_length());
  return bitwise_and(address, netmask) == network.address();
}

#endif
