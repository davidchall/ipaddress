#ifndef __IPADDRESS_STRING__
#define __IPADDRESS_STRING__

#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>
#include <ipaddress/IpNetwork.h>

/* String representation
 *
 * These `ipaddress::to_string()` functions yield a string representation
 * of an ipaddress::IpAddress or ipaddress::IpNetwork object. For example:
 *  - "192.168.0.1"
 *  - "2001:db8:85a3::8a2e:370:7334"
 *  - "192.168.0.0/24"
 *  - "2001:db8::/48"
 *
 * These functions rely upon the Asio library, so you'll need to add
 * `LinkingTo: AsioHeaders` to your package DESCRIPTION file if you want to
 * use them. You'll also need to `#include <ipaddress/to_string.h>` because
 * they aren't included in the main `ipaddress.h` header.
 */

namespace ipaddress {

inline std::string to_string(const IpAddress &address) {
  if (address.is_na()) {
    return std::string();
  } else if (address.is_ipv6()) {
    asio::ip::address_v6 asio_address(address.bytes_v6());
    return asio_address.to_string();
  } else {
    asio::ip::address_v4 asio_address(address.bytes_v4());
    return asio_address.to_string();
  }
}

inline std::string to_string(const IpNetwork &network) {
  if (network.is_na()) {
    return std::string();
  } else if (network.is_ipv6()) {
    asio::ip::address_v6 asio_address(network.address().bytes_v6());
    asio::ip::network_v6 asio_network(asio_address, network.prefix_length());
    return asio_network.to_string();
  } else {
    asio::ip::address_v4 asio_address(network.address().bytes_v4());
    asio::ip::network_v4 asio_network(asio_address, network.prefix_length());
    return asio_network.to_string();
  }
}

}

#endif
