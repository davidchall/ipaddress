#ifndef __IPADDRESS_MASKING__
#define __IPADDRESS_MASKING__

#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

asio::ip::address_v6::bytes_type netmask_bytes_v6(int prefix_length);
asio::ip::address_v6 netmask_v6(int prefix_length);
asio::ip::address_v6 hostmask_v6(int prefix_length);

#endif
