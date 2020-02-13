#define ASIO_STANDALONE

#include <Rcpp.h>
#include "IpNetworkVector.hpp"

using namespace Rcpp;

// [[Rcpp::export]]
List ipv4_network_aton(CharacterVector x) {
  return IpNetworkVector(x).toList();
}

// [[Rcpp::export]]
CharacterVector ipv4_network_ntoa(IntegerVector address, IntegerVector prefix) {
  return IpNetworkVector(address, prefix).toCharacterVector();
}
