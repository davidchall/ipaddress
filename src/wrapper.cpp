#define ASIO_STANDALONE

#include <Rcpp.h>
#include "IpAddressVector.h"
#include "IpNetworkVector.h"

using namespace Rcpp;

// [[Rcpp::export]]
List address_aton(CharacterVector x) {
  return IpAddressVector(x).asList();
}

// [[Rcpp::export]]
CharacterVector address_ntoa(List x) {
  return IpAddressVector(x).asCharacterVector();
}

// [[Rcpp::export]]
List network_aton(CharacterVector x) {
  return IpNetworkVector(x).asList();
}

// [[Rcpp::export]]
CharacterVector network_ntoa(List x) {
  return IpNetworkVector(x).asCharacterVector();
}
