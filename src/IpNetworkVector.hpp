#define ASIO_STANDALONE

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>

using namespace Rcpp;

#ifndef __IP_NETWORK_VECTOR__
#define __IP_NETWORK_VECTOR__

class IpNetworkVector {
private:
  std::vector<asio::ip::network_v4> network;
  std::vector<bool> is_na;

public:
  IpNetworkVector(CharacterVector network_r);
  IpNetworkVector(List network_r);

  CharacterVector asCharacterVector() const;
  List asList() const;
};

#endif
