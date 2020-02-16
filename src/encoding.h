#ifndef __IPADDRESS_ENCODING__
#define __IPADDRESS_ENCODING__

#define ASIO_STANDALONE

#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

typedef int32_t address_v4_r_bytes_type;
typedef std::array<int32_t, 4> address_v6_r_bytes_type;

address_v4_r_bytes_type encode_ipv4(asio::ip::address_v4 x);
asio::ip::address_v4 decode_ipv4(address_v4_r_bytes_type x);
address_v6_r_bytes_type encode_ipv6(asio::ip::address_v6 x);
asio::ip::address_v6 decode_ipv6(address_v6_r_bytes_type x);

#endif
