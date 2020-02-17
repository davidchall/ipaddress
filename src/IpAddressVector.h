#ifndef __IPADDRESS_ADDRESS__
#define __IPADDRESS_ADDRESS__

#define ASIO_STANDALONE
// Windows target version: https://docs.microsoft.com/en-us/cpp/porting/modifying-winver-and-win32-winnt
#define _WIN32_WINNT 0x0601  // Windows 7

#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>

using namespace Rcpp;

class IpNetworkVector;

class IpAddressVector {
public:
  std::vector<asio::ip::address_v4> address_v4;
  std::vector<asio::ip::address_v6> address_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

  IpAddressVector(
    std::vector<asio::ip::address_v4> in_address_v4,
    std::vector<asio::ip::address_v6> in_address_v6,
    std::vector<bool> in_is_ipv6,
    std::vector<bool> in_is_na
  );
  IpAddressVector(CharacterVector input);
  IpAddressVector(List input);

  // output
  List asList() const;
  CharacterVector asCharacterVector() const;
  DataFrame compare() const;

  LogicalVector isWithin(const IpNetworkVector &network) const;
  LogicalVector isWithinAny(const IpNetworkVector &network) const;
};

#endif
