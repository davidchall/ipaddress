#ifndef __IPADDRESS_ENCODING__
#define __IPADDRESS_ENCODING__

#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>


typedef std::array<int32_t, 1> r_address_v4_type;
typedef std::array<int32_t, 4> r_address_v6_type;

template<class RAddress, class CAddress>
RAddress encode(const CAddress &x) {
  RAddress x_out;
  typename CAddress::bytes_type x_in = x.to_bytes();

  std::memcpy(x_out.begin(), x_in.begin(), x_in.size());

  return x_out;
}

template<class CAddress, class RAddress>
CAddress decode(const RAddress &x_in) {
  typename CAddress::bytes_type x_out;

  std::memcpy(x_out.begin(), x_in.begin(), x_out.size());

  return CAddress(x_out);
}

#endif
