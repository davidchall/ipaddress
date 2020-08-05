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
Address prefix_to_netmask(int prefix_length) {
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
Address prefix_to_hostmask(int prefix_length) {
  return bitwise_not(prefix_to_netmask<Address>(prefix_length));
}

template<class Address>
int count_trailing_zero_bits(const Address &address) {
  typedef typename Address::bytes_type Bytes;

  if (address == Address()) {
    return 8 * sizeof(Bytes);
  }

  Bytes addr_bytes = address.to_bytes();
  int zeros = 0;
  for (std::size_t i=0; i<sizeof(Bytes); ++i) {
    uint32_t ingest = addr_bytes[sizeof(Bytes)-1-i];

    if (ingest == 0) {
      zeros += 8;
    } else {
      zeros += __builtin_ctz(ingest);
      break;
    }
  }

  return zeros;
}

template<class Address>
int count_leading_zero_bits(const Address &address) {
  typedef typename Address::bytes_type Bytes;

  if (address == Address()) {
    return 8 * sizeof(Bytes);
  }

  Bytes addr_bytes = address.to_bytes();
  int zeros = 0;
  for (std::size_t i=0; i<sizeof(Bytes); ++i) {
    uint32_t ingest = addr_bytes[i];

    if (ingest == 0) {
      zeros += 8;
    } else {
      // ingest is 32-bits but only uses final 8-bits
      zeros += __builtin_clz(ingest) - 24;
      break;
    }
  }

  return zeros;
}

template<class Address>
int netmask_to_prefix(const Address &mask) {
  typedef typename Address::bytes_type Bytes;

  int trailing_zeros = count_trailing_zero_bits(mask);
  int prefix = (8 * sizeof(Bytes)) - trailing_zeros;

  // catch non-mask addresses (mixed zeros and ones)
  Address valid_mask = prefix_to_netmask<Address>(prefix);
  return mask == valid_mask ? prefix: -1;
}

template<class Address>
int hostmask_to_prefix(const Address &mask) {
  return netmask_to_prefix(bitwise_not(mask));
}

template<class Network, class Address>
Network common_network(const Address &addr1, const Address &addr2) {
  int prefix = count_leading_zero_bits(bitwise_xor(addr1, addr2));
  Address start_address = bitwise_and(addr1, prefix_to_netmask<Address>(prefix));

  return Network(start_address, prefix);
}

template<class Address, class Network>
Address broadcast_address(const Network &network) {
  Address hostmask = prefix_to_hostmask<Address>(network.prefix_length());
  return bitwise_or(network.address(), hostmask);
}

template<class Address, class Network>
bool address_in_network(const Address &address, const Network &network) {
  Address netmask = prefix_to_netmask<Address>(network.prefix_length());
  return bitwise_and(address, netmask) == network.address();
}

#endif
