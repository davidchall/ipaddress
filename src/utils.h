#ifndef __IPADDRESS_UTILS__
#define __IPADDRESS_UTILS__

#include <asio/ip/address_v4_iterator.hpp>
#include <asio/ip/address_v6_iterator.hpp>


template<class Address>
Address advance_ip(const Address &address, int n) {
  if (n == 0)
    return address;

  asio::ip::basic_address_iterator<Address> iter(address);

  if (n > 0)
    while (n--)
      ++iter;
  else
    while (n++)
      --iter;

  return *iter;
}

bool is_6to4(const asio::ip::address_v6 &address);
asio::ip::address_v4 extract_6to4(const asio::ip::address_v6 &address);
bool is_teredo(const asio::ip::address_v6 &address);
asio::ip::address_v4 extract_teredo_server(const asio::ip::address_v6 &address);
asio::ip::address_v4 extract_teredo_client(const asio::ip::address_v6 &address);

#endif
