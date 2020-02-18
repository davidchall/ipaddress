#ifndef __IPADDRESS_MASKING__
#define __IPADDRESS_MASKING__

#define ASIO_STANDALONE
// Windows target version: https://docs.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt
#define _WIN32_WINNT 0x0601  // Windows 7
#define ASIO_WINDOWS_RUNTIME

#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

asio::ip::address_v6::bytes_type netmask_bytes_v6(int prefix_length);
asio::ip::address_v6 netmask_v6(int prefix_length);
asio::ip::address_v6 hostmask_v6(int prefix_length);

bool in_network(const asio::ip::address_v6 &address, const asio::ip::network_v6 &network);
bool in_network(const asio::ip::address_v4 &address, const asio::ip::network_v4 &network);

#endif
