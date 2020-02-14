#define ASIO_STANDALONE

#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>

using namespace Rcpp;

#ifndef __IP_ADDRESS_VECTOR__
#define __IP_ADDRESS_VECTOR__

class IpAddressVector {
private:
  std::vector<asio::ip::address_v4> address;
  std::vector<bool> is_na;

public:
  IpAddressVector(CharacterVector address_r);
  IpAddressVector(IntegerVector address_r);

  CharacterVector asCharacterVector() const;
  IntegerVector asIntegerVector() const;
};

#endif
