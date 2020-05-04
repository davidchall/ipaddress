#ifndef __IPADDRESS_ENCODING__
#define __IPADDRESS_ENCODING__

#include <algorithm>
#include <bitset>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>
#include <boost/multiprecision/cpp_int.hpp>


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

template<class Address>
std::string encode_integer(const Address &x) {
  typename Address::bytes_type x_bytes = x.to_bytes();

  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<
    8*sizeof(x_bytes), 8*sizeof(x_bytes),
    boost::multiprecision::unsigned_magnitude,
    boost::multiprecision::checked,
    void
  >> x_int;

  // import most-significant byte first (x_bytes stored in network order)
  import_bits(x_int, x_bytes.begin(), x_bytes.end(), 8, true);

  return x_int.str();
}

template<class Address>
Address decode_integer(const std::string& x_int_string) {
  typename Address::bytes_type x_bytes = {};

  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<
    8*sizeof(x_bytes), 8*sizeof(x_bytes),
    boost::multiprecision::unsigned_magnitude,
    boost::multiprecision::checked,
    void
  >> x_int(x_int_string);

  // must export least-significant byte first because boost::multiprecision is
  // aggressively optimized and does not reserve space for unused bits,
  // even though I've declared the size of the integer as 32-bit or 128-bit
  export_bits(x_int, x_bytes.begin(), 8, false);
  std::reverse(x_bytes.begin(), x_bytes.end());

  return Address(x_bytes);
}

#endif
