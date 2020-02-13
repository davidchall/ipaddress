#define ASIO_STANDALONE

#include <Rcpp.h>
#include "IpAddressVector.hpp"

using namespace Rcpp;


// [[Rcpp::export]]
IntegerVector ipv4_address_aton(CharacterVector x) {
  return IpAddressVector(x).toIntegerVector();
}

// [[Rcpp::export]]
CharacterVector ipv4_address_ntoa(IntegerVector x) {
  return IpAddressVector(x).toCharacterVector();
}
