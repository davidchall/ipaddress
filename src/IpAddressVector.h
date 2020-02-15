#ifndef __IPADDRESS_ADDRESS__
#define __IPADDRESS_ADDRESS__

#define ASIO_STANDALONE

#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>

using namespace Rcpp;

class IpAddressVector {
private:
  std::vector<asio::ip::address_v4> address_v4;
  std::vector<asio::ip::address_v6> address_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

public:
  IpAddressVector(CharacterVector input);
  IpAddressVector(List input);

  List asList() const;
  CharacterVector asCharacterVector() const;
};

#endif
