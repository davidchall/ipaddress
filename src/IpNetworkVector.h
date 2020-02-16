#ifndef __IPADDRESS_NETWORK__
#define __IPADDRESS_NETWORK__

#define ASIO_STANDALONE

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>
#include "IpAddressVector.h"

using namespace Rcpp;

class IpNetworkVector {
private:
  std::vector<asio::ip::network_v4> network_v4;
  std::vector<asio::ip::network_v6> network_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

  asio::ip::address_v6 netmask_v6(int prefix_length) const;

public:
  IpNetworkVector(
    std::vector<asio::ip::network_v4> in_network_v4,
    std::vector<asio::ip::network_v6> in_network_v6,
    std::vector<bool> in_is_ipv6,
    std::vector<bool> in_is_na
  );
  IpNetworkVector(CharacterVector input);
  IpNetworkVector(List input);

  // output
  CharacterVector asCharacterVector() const;
  List asList() const;

  IpAddressVector netmask() const;
};

#endif
