#ifndef __IPADDRESS_ENCODING__
#define __IPADDRESS_ENCODING__

#define ASIO_STANDALONE

#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

int32_t encode_ipv4(asio::ip::address_v4 x);
asio::ip::address_v4 decode_ipv4(int32_t x);
std::array<int32_t, 4> encode_ipv6(asio::ip::address_v6 x);
asio::ip::address_v6 decode_ipv6(std::array<int32_t, 4> x);

#endif
