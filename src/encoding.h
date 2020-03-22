#ifndef __IPADDRESS_ENCODING__
#define __IPADDRESS_ENCODING__

#include <bitset>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>


typedef std::array<int32_t, 1> r_address_v4_type;
typedef std::array<int32_t, 4> r_address_v6_type;

template<class RAddress, class CAddress>
RAddress encode_r(const CAddress &x) {
  RAddress x_out;
  typename CAddress::bytes_type x_in = x.to_bytes();

  std::memcpy(x_out.begin(), x_in.begin(), x_in.size());

  return x_out;
}

template<class CAddress, class RAddress>
CAddress decode_r(const RAddress &x_in) {
  typename CAddress::bytes_type x_out;

  std::memcpy(x_out.begin(), x_in.begin(), x_out.size());

  return CAddress(x_out);
}

template<class Address>
std::string encode_binary(const Address &x) {
  typename Address::bytes_type bytes = x.to_bytes();
  std::string bit_string;
  bit_string.reserve(8*sizeof(bytes));

  for (std::size_t i=0; i<sizeof(bytes); ++i) {
    std::bitset<8> bits(bytes[i]);
    bit_string += bits.to_string();
  }

  return bit_string;
}

template<class Address>
Address decode_binary(const std::string &bit_string) {
  typename Address::bytes_type bytes;

  for (std::size_t i=0; i<sizeof(bytes); ++i) {
    std::bitset<8> bits(bit_string.substr(i*8, 8));
    bytes[i] = bits.to_ulong();
  }

  return Address(bytes);
}

#endif
