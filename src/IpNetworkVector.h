#ifndef __IPADDRESS_NETWORK__
#define __IPADDRESS_NETWORK__

#define ASIO_STANDALONE
// Windows target version: https://docs.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt
#define _WIN32_WINNT 0x0601  // Windows 7
#define ASIO_WINDOWS_RUNTIME

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

using namespace Rcpp;

class IpAddressVector;

class IpNetworkVector {
public:
  std::vector<asio::ip::network_v4> network_v4;
  std::vector<asio::ip::network_v6> network_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

  IpNetworkVector(
    std::vector<asio::ip::network_v4> in_network_v4,
    std::vector<asio::ip::network_v6> in_network_v6,
    std::vector<bool> in_is_ipv6,
    std::vector<bool> in_is_na
  );
  IpNetworkVector(CharacterVector input, bool strict);
  IpNetworkVector(List input);

  // output
  CharacterVector asCharacterVector() const;
  List asList() const;

  IpAddressVector netmask() const;
  IpAddressVector hostmask() const;
};

#endif
