#ifndef __IPADDRESS_UTILS__
#define __IPADDRESS_UTILS__

#include <asio/ip/address_v4_iterator.hpp>
#include <asio/ip/address_v6_iterator.hpp>


asio::ip::address_v4 advance_ip(asio::ip::address_v4 address, int n) {
  if (n == 0)
    return address;

  asio::ip::address_v4_iterator iter(address);

  if (n > 0)
    while (n--)
      ++iter;
  else
    while (n++)
      --iter;

  return *iter;
}

asio::ip::address_v6 advance_ip(asio::ip::address_v6 address, int n) {
  if (n == 0)
    return address;

  asio::ip::address_v6_iterator iter(address);

  if (n > 0)
    while (n--)
      ++iter;
  else
    while (n++)
      --iter;

  return *iter;
}

#endif
