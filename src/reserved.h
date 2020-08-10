#ifndef __IPADDRESS_RESERVED__
#define __IPADDRESS_RESERVED__

#include <asio/ip/address_v4_iterator.hpp>
#include <asio/ip/address_v6_iterator.hpp>


namespace ipaddress {

bool is_6to4(const asio::ip::address_v6 &address);
asio::ip::address_v4 extract_6to4(const asio::ip::address_v6 &address);
bool is_teredo(const asio::ip::address_v6 &address);
asio::ip::address_v4 extract_teredo_server(const asio::ip::address_v6 &address);
asio::ip::address_v4 extract_teredo_client(const asio::ip::address_v6 &address);

}

#endif
