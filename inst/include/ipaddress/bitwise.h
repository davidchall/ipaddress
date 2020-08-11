#ifndef __IPADDRESS_BITWISE__
#define __IPADDRESS_BITWISE__

#include <algorithm>

namespace ipaddress {

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

}

#endif
