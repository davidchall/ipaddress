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

// [[Rcpp::export]]
List construct_network_wrapper(List address, IntegerVector prefix_length, bool strict) {
  return IpNetworkVector(IpAddressVector(address), prefix_length, strict).encodeR();
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
List netmask_wrapper(IntegerVector prefix_length, LogicalVector is_ipv6) {
  return IpAddressVector::createNetmask(prefix_length, is_ipv6).encodeR();
}

// [[Rcpp::export]]
List hostmask_wrapper(IntegerVector prefix_length, LogicalVector is_ipv6) {
  return IpAddressVector::createHostmask(prefix_length, is_ipv6).encodeR();
}

// [[Rcpp::export]]
List broadcast_address_wrapper(List network_r) {
  return IpNetworkVector(network_r).broadcastAddress().encodeR();
}

// [[Rcpp::export]]
List hosts_wrapper(List network_r, bool exclude_unusable) {
  return IpNetworkVector(network_r).hosts(exclude_unusable).encodeR();
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
