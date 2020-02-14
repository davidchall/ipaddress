#define ASIO_STANDALONE

#include <Rcpp.h>
#include "IpAddressVector.hpp"
#include "IpNetworkVector.hpp"

using namespace Rcpp;

// [[Rcpp::export]]
IntegerVector ipv4_address_aton(CharacterVector x) {
  return IpAddressVector(x).asIntegerVector();
}

// [[Rcpp::export]]
CharacterVector ipv4_address_ntoa(IntegerVector x) {
  return IpAddressVector(x).asCharacterVector();
}

// [[Rcpp::export]]
List ipv4_network_aton(CharacterVector x) {
  return IpNetworkVector(x).asList();
}

// [[Rcpp::export]]
CharacterVector ipv4_network_ntoa(List network) {
  return IpNetworkVector(network).asCharacterVector();
}
