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
List to_packed_address_wrapper(List x) {
  return IpAddressVector(x).encodePacked();
}

// [[Rcpp::export]]
List from_packed_address_wrapper(List x) {
  return IpAddressVector::decodePacked(x).encodeR();
}

// [[Rcpp::export]]
CharacterVector to_binary_address_wrapper(List x) {
  return IpAddressVector(x).encodeBinary();
}

// [[Rcpp::export]]
List from_binary_address_wrapper(CharacterVector x) {
  return IpAddressVector::decodeBinary(x).encodeR();
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
List parse_interface_wrapper(CharacterVector x) {
  return IpNetworkVector(x, false, true).encodeR();
}

// [[Rcpp::export]]
List construct_interface_wrapper(List address, IntegerVector prefix_length) {
  return IpNetworkVector(IpAddressVector(address), prefix_length, false, true).encodeR();
}

// [[Rcpp::export]]
CharacterVector print_network_wrapper(List x) {
  return IpNetworkVector(x).encodeStrings();
}

// [[Rcpp::export]]
List encode_hostname_wrapper(List x) {
  return IpAddressVector(x).encodeHostnames();
}

// [[Rcpp::export]]
List decode_hostname_wrapper(CharacterVector x) {
  return IpAddressVector::decodeHostname(x);
}


/*----------------*
 *  Other output  *
 * ---------------*/
// [[Rcpp::export]]
DataFrame compare_address_wrapper(List x) {
  return IpAddressVector(x).encodeComparable();
}

// [[Rcpp::export]]
List hosts_wrapper(List network_r, bool exclude_unusable) {
  return IpNetworkVector(network_r).hosts(exclude_unusable).encodeR();
}

// [[Rcpp::export]]
List sample_wrapper(List network_r, unsigned int size) {
  return IpNetworkVector(network_r).sample(size).encodeR();
}


/*-------------*
 *  Operators  *
 *-------------*/
// [[Rcpp::export]]
List bitwise_not_wrapper(List lhs) {
  IpAddressVector result = ~IpAddressVector(lhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List bitwise_and_wrapper(List lhs, List rhs) {
  IpAddressVector result = IpAddressVector(lhs) & IpAddressVector(rhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List bitwise_or_wrapper(List lhs, List rhs) {
  IpAddressVector result = IpAddressVector(lhs) | IpAddressVector(rhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List bitwise_xor_wrapper(List lhs, List rhs) {
  IpAddressVector result = IpAddressVector(lhs) ^ IpAddressVector(rhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List addition_wrapper(List lhs, IntegerVector rhs) {
  IpAddressVector result = IpAddressVector(lhs) + rhs;
  return result.encodeR();
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


/*----------------------*
 *  Reserved addresses  *
 * ---------------------*/
// [[Rcpp::export]]
LogicalVector is_multicast_address_wrapper(List address_r) {
  return IpAddressVector(address_r).isMulticast();
}

// [[Rcpp::export]]
LogicalVector is_multicast_network_wrapper(List network_r) {
  return IpNetworkVector(network_r).isMulticast();
}

// [[Rcpp::export]]
LogicalVector is_unspecified_address_wrapper(List address_r) {
  return IpAddressVector(address_r).isUnspecified();
}

// [[Rcpp::export]]
LogicalVector is_unspecified_network_wrapper(List network_r) {
  return IpNetworkVector(network_r).isUnspecified();
}

// [[Rcpp::export]]
LogicalVector is_loopback_address_wrapper(List address_r) {
  return IpAddressVector(address_r).isLoopback();
}

// [[Rcpp::export]]
LogicalVector is_loopback_network_wrapper(List network_r) {
  return IpNetworkVector(network_r).isLoopback();
}

// [[Rcpp::export]]
LogicalVector is_link_local_address_wrapper(List address_r) {
  return IpAddressVector(address_r).isLinkLocal();
}

// [[Rcpp::export]]
LogicalVector is_link_local_network_wrapper(List network_r) {
  return IpNetworkVector(network_r).isLinkLocal();
}


/*------------------------------*
 *  IPv6 transition mechanisms  *
 * -----------------------------*/
// [[Rcpp::export]]
LogicalVector is_ipv4_mapped_address_wrapper(List address_r) {
  return IpAddressVector(address_r).isIPv4Mapped();
}

// [[Rcpp::export]]
LogicalVector is_ipv4_mapped_network_wrapper(List network_r) {
  return IpNetworkVector(network_r).isIPv4Mapped();
}

// [[Rcpp::export]]
List extract_ipv4_mapped_wrapper(List address_r) {
  return IpAddressVector(address_r).extractIPv4Mapped().encodeR();
}

// [[Rcpp::export]]
LogicalVector is_6to4_address_wrapper(List address_r) {
  return IpAddressVector(address_r).is6to4();
}

// [[Rcpp::export]]
LogicalVector is_6to4_network_wrapper(List network_r) {
  return IpNetworkVector(network_r).is6to4();
}

// [[Rcpp::export]]
List extract_6to4_wrapper(List address_r) {
  return IpAddressVector(address_r).extract6to4().encodeR();
}

// [[Rcpp::export]]
LogicalVector is_teredo_address_wrapper(List address_r) {
  return IpAddressVector(address_r).isTeredo();
}

// [[Rcpp::export]]
LogicalVector is_teredo_network_wrapper(List network_r) {
  return IpNetworkVector(network_r).isTeredo();
}

// [[Rcpp::export]]
List extract_teredo_server_wrapper(List address_r) {
  return IpAddressVector(address_r).extractTeredoServer().encodeR();
}

// [[Rcpp::export]]
List extract_teredo_client_wrapper(List address_r) {
  return IpAddressVector(address_r).extractTeredoClient().encodeR();
}
