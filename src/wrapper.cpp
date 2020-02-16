#define ASIO_STANDALONE

#include <Rcpp.h>
#include "IpAddressVector.h"
#include "IpNetworkVector.h"

using namespace Rcpp;

// [[Rcpp::export]]
List parse_address_wrapper(CharacterVector x) {
  return IpAddressVector(x).asList();
}

// [[Rcpp::export]]
CharacterVector print_address_wrapper(List x) {
  return IpAddressVector(x).asCharacterVector();
}

// [[Rcpp::export]]
List parse_network_wrapper(CharacterVector x) {
  return IpNetworkVector(x).asList();
}

// [[Rcpp::export]]
CharacterVector print_network_wrapper(List x) {
  return IpNetworkVector(x).asCharacterVector();
}

// [[Rcpp::export]]
List netmask_wrapper(List x) {
  return IpNetworkVector(x).netmask().asList();
}
