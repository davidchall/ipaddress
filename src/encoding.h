#ifndef __IPADDRESS_ENCODING__
#define __IPADDRESS_ENCODING__

#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

typedef std::array<int32_t, 1> r_address_v4_type;
typedef std::array<int32_t, 4> r_address_v6_type;

template<class RAddress, class CAddress>
RAddress encode(CAddress x) {
  RAddress x_out;
  typename CAddress::bytes_type x_in = x.to_bytes();

  for (std::size_t i=0; i<x_out.size(); ++i) {
    std::memcpy(&x_out[i], &x_in[4*i], sizeof(x_out[i]));
  }

  return x_out;
}

template<class CAddress, class RAddress>
CAddress decode(RAddress x_in) {
  typename CAddress::bytes_type x_out;

  for (std::size_t i=0; i<x_in.size(); ++i) {
    std::memcpy(&x_out[4*i], &x_in[i], sizeof(x_in[i]));
  }

  return CAddress(x_out);
}

#endif
