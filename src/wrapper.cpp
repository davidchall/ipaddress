#include <Rcpp.h>
#include "IpAddressVector.h"
#include "IpNetworkVector.h"

using namespace Rcpp;

/*-----------------------------------*
 *  Encoding and decoding addresses  *
 * ----------------------------------*/
// [[Rcpp::export]]
List wrap_parse_address(CharacterVector x) {
  return IpAddressVector(x).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_print_address(List x) {
  return IpAddressVector(x).encodeStrings();
}

// [[Rcpp::export]]
List wrap_encode_packed(List x) {
  return IpAddressVector(x).encodePacked();
}

// [[Rcpp::export]]
List wrap_decode_packed(List x) {
  return IpAddressVector::decodePacked(x).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_encode_integer(List x) {
  return IpAddressVector(x).encodeInteger();
}

// [[Rcpp::export]]
List wrap_decode_integer(CharacterVector x, Nullable<LogicalVector> is_ipv6) {
  return IpAddressVector::decodeInteger(x, is_ipv6).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_encode_binary(List x) {
  return IpAddressVector(x).encodeBinary();
}

// [[Rcpp::export]]
List wrap_decode_binary(CharacterVector x) {
  return IpAddressVector::decodeBinary(x).encodeR();
}

// [[Rcpp::export]]
List wrap_encode_hostname(List x) {
  return IpAddressVector(x).encodeHostnames();
}

// [[Rcpp::export]]
List wrap_decode_hostname(CharacterVector x) {
  return IpAddressVector::decodeHostname(x);
}


/*----------------------------------*
 *  Encoding and decoding networks  *
 * ---------------------------------*/
// [[Rcpp::export]]
List wrap_parse_network(CharacterVector x, bool strict) {
  return IpNetworkVector(x, strict).encodeR();
}

// [[Rcpp::export]]
List wrap_construct_network_from_address(List address, IntegerVector prefix_length, bool strict) {
  return IpNetworkVector(IpAddressVector(address), prefix_length, strict).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_print_network(List x) {
  return IpNetworkVector(x).encodeStrings();
}


/*------------------------------------*
 *  Encoding and decoding interfaces  *
 * -----------------------------------*/
// [[Rcpp::export]]
List wrap_parse_interface(CharacterVector x) {
  return IpNetworkVector(x, false, true).encodeR();
}

// [[Rcpp::export]]
List wrap_construct_interface_from_address(List address, IntegerVector prefix_length) {
  return IpNetworkVector(IpAddressVector(address), prefix_length, false, true).encodeR();
}


/*----------------*
 *  Other output  *
 * ---------------*/
// [[Rcpp::export]]
DataFrame wrap_compare_address(List x) {
  return IpAddressVector(x).encodeComparable();
}

// [[Rcpp::export]]
List wrap_network_hosts(List network_r, bool exclude_unusable) {
  return IpNetworkVector(network_r).hosts(exclude_unusable).encodeR();
}

// [[Rcpp::export]]
List wrap_sample_network(List network_r, unsigned int size) {
  return IpNetworkVector(network_r).sample(size).encodeR();
}


/*-------------*
 *  Operators  *
 *-------------*/
// [[Rcpp::export]]
List wrap_bitwise_not(List lhs) {
  IpAddressVector result = ~IpAddressVector(lhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_and(List lhs, List rhs) {
  IpAddressVector result = IpAddressVector(lhs) & IpAddressVector(rhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_or(List lhs, List rhs) {
  IpAddressVector result = IpAddressVector(lhs) | IpAddressVector(rhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_xor(List lhs, List rhs) {
  IpAddressVector result = IpAddressVector(lhs) ^ IpAddressVector(rhs);
  return result.encodeR();
}

// [[Rcpp::export]]
List wrap_add_integer(List lhs, IntegerVector rhs) {
  IpAddressVector result = IpAddressVector(lhs) + rhs;
  return result.encodeR();
}


/*---------------*
 *  Bit masking  *
 * --------------*/
// [[Rcpp::export]]
List wrap_netmask(IntegerVector prefix_length, LogicalVector is_ipv6) {
  return IpAddressVector::createNetmask(prefix_length, is_ipv6).encodeR();
}

// [[Rcpp::export]]
List wrap_hostmask(IntegerVector prefix_length, LogicalVector is_ipv6) {
  return IpAddressVector::createHostmask(prefix_length, is_ipv6).encodeR();
}

// [[Rcpp::export]]
List wrap_broadcast_address(List network_r) {
  return IpNetworkVector(network_r).broadcastAddress().encodeR();
}

// [[Rcpp::export]]
LogicalVector wrap_is_within(List address_r, List network_r) {
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

  return address.isWithin(network);
}

// [[Rcpp::export]]
LogicalVector wrap_is_within_any(List address_r, List network_r) {
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

  return address.isWithinAny(network);
}


/*----------------------*
 *  Reserved addresses  *
 * ---------------------*/
// [[Rcpp::export]]
LogicalVector wrap_is_multicast(List x) {
  if (x.inherits("ip_address")) {
    return IpAddressVector(x).isMulticast();
  } else {
    return IpNetworkVector(x).isMulticast();
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_unspecified(List x) {
  if (x.inherits("ip_address")) {
    return IpAddressVector(x).isUnspecified();
  } else {
    return IpNetworkVector(x).isUnspecified();
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_loopback(List x) {
  if (x.inherits("ip_address")) {
    return IpAddressVector(x).isLoopback();
  } else {
    return IpNetworkVector(x).isLoopback();
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_link_local(List x) {
  if (x.inherits("ip_address")) {
    return IpAddressVector(x).isLinkLocal();
  } else {
    return IpNetworkVector(x).isLinkLocal();
  }
}


/*------------------------------*
 *  IPv6 transition mechanisms  *
 * -----------------------------*/
// [[Rcpp::export]]
LogicalVector wrap_is_ipv4_mapped(List x) {
  if (x.inherits("ip_address")) {
    return IpAddressVector(x).isIPv4Mapped();
  } else {
    return IpNetworkVector(x).isIPv4Mapped();
  }
}

// [[Rcpp::export]]
List wrap_extract_ipv4_mapped(List address_r) {
  return IpAddressVector(address_r).extractIPv4Mapped().encodeR();
}

// [[Rcpp::export]]
LogicalVector wrap_is_6to4(List x) {
  if (x.inherits("ip_address")) {
    return IpAddressVector(x).is6to4();
  } else {
    return IpNetworkVector(x).is6to4();
  }
}

// [[Rcpp::export]]
List wrap_extract_6to4(List address_r) {
  return IpAddressVector(address_r).extract6to4().encodeR();
}

// [[Rcpp::export]]
LogicalVector wrap_is_teredo(List x) {
  if (x.inherits("ip_address")) {
    return IpAddressVector(x).isTeredo();
  } else {
    return IpNetworkVector(x).isTeredo();
  }
}

// [[Rcpp::export]]
List wrap_extract_teredo_server(List address_r) {
  return IpAddressVector(address_r).extractTeredoServer().encodeR();
}

// [[Rcpp::export]]
List wrap_extract_teredo_client(List address_r) {
  return IpAddressVector(address_r).extractTeredoClient().encodeR();
}
