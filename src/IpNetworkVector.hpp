#ifndef __IPADDRESS_NETWORK__
#define __IPADDRESS_NETWORK__

#define ASIO_STANDALONE

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

using namespace Rcpp;

class IpNetworkVector {
private:
  std::vector<asio::ip::network_v4> network_v4;
  std::vector<asio::ip::network_v6> network_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

public:
  IpNetworkVector(CharacterVector input);
  IpNetworkVector(List input);

  CharacterVector asCharacterVector() const;
  List asList() const;
};

#endif
