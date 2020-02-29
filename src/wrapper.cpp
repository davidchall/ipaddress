#include <Rcpp.h>
#include "IpAddressVector.h"
#include "IpNetworkVector.h"

using namespace Rcpp;

/*-------------------------*
 *  Encoding and decoding  *
 * ------------------------*/
// [[Rcpp::export]]
List parse_address_wrapper(CharacterVector x) {
  return IpAddressVector(x).encodeR();
}

// [[Rcpp::export]]
CharacterVector print_address_wrapper(List x) {
  return IpAddressVector(x).encodeStrings();
}

// [[Rcpp::export]]
List parse_network_wrapper(CharacterVector x, bool strict) {
  return IpNetworkVector(x, strict).encodeR();
}
}

// [[Rcpp::export]]
CharacterVector print_network_wrapper(List x) {
  return IpNetworkVector(x).encodeStrings();
}


/*------------------------*
 *  Comparison operators  *
 * -----------------------*/
// [[Rcpp::export]]
DataFrame compare_address_wrapper(List x) {
  return IpAddressVector(x).encodeComparable();
}


/*---------------*
 *  Bit masking  *
 * --------------*/
// [[Rcpp::export]]
List netmask_wrapper(List x) {
  return IpAddressVector::createNetmask(x["is_ipv6"], x["prefix"]).encodeR();
}

// [[Rcpp::export]]
List hostmask_wrapper(List x) {
  return IpAddressVector::createHostmask(x["is_ipv6"], x["prefix"]).encodeR();
}

// [[Rcpp::export]]
LogicalVector is_within_wrapper(List address_r, List network_r) {
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

  return address.isWithin(network);
}

// [[Rcpp::export]]
LogicalVector is_within_any_wrapper(List address_r, List network_r) {
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

  return address.isWithinAny(network);
}
