#include <Rcpp.h>
#include <ipaddress/IpAddressVector.h>
#include <ipaddress/IpNetworkVector.h>

using namespace Rcpp;
using namespace ipaddress;


/*-------------*
 *  Addresses  *
 * ------------*/
// [[Rcpp::export]]
List wrap_parse_address(CharacterVector x) {
  return IpAddressVector(x).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_print_address(List x) {
  return IpAddressVector(x).encodeStrings();
}

// [[Rcpp::export]]
DataFrame wrap_compare_address(List address_r) {
  IpAddressVector address(address_r);

  std::size_t vsize = address.size();

  // initialize vectors
  IntegerVector out_addr1(vsize);
  IntegerVector out_addr2(vsize);
  IntegerVector out_addr3(vsize);
  IntegerVector out_addr4(vsize);
  IntegerVector out_addr5(vsize);
  IntegerVector out_addr6(vsize);
  IntegerVector out_addr7(vsize);
  IntegerVector out_addr8(vsize);
  LogicalVector out_v6(vsize);

  uint32_t right_mask = (1 << 16) - 1;
  uint32_t left_mask = ~right_mask;

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_na[i]) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_addr5[i] = NA_INTEGER;
      out_addr6[i] = NA_INTEGER;
      out_addr7[i] = NA_INTEGER;
      out_addr8[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (address.is_ipv6[i]) {
      r_address_v6_type bytes = encode_r<r_address_v6_type>(address.address_v6[i]);
      out_addr1[i] = (ntohl(bytes[0]) & left_mask) >> 16;
      out_addr2[i] = (ntohl(bytes[0]) & right_mask);
      out_addr3[i] = (ntohl(bytes[1]) & left_mask) >> 16;
      out_addr4[i] = (ntohl(bytes[1]) & right_mask);
      out_addr5[i] = (ntohl(bytes[2]) & left_mask) >> 16;
      out_addr6[i] = (ntohl(bytes[2]) & right_mask);
      out_addr7[i] = (ntohl(bytes[3]) & left_mask) >> 16;
      out_addr8[i] = (ntohl(bytes[3]) & right_mask);
      out_v6[i] = true;
    } else {
      r_address_v4_type bytes = encode_r<r_address_v4_type>(address.address_v4[i]);
      out_addr1[i] = (ntohl(bytes[0]) & left_mask) >> 16;
      out_addr2[i] = (ntohl(bytes[0]) & right_mask);
    }
  }

  if (out_addr1.size() != out_v6.size() ||
      out_addr2.size() != out_v6.size() ||
      out_addr3.size() != out_v6.size() ||
      out_addr4.size() != out_v6.size() ||
      out_addr5.size() != out_v6.size() ||
      out_addr6.size() != out_v6.size() ||
      out_addr7.size() != out_v6.size() ||
      out_addr8.size() != out_v6.size()) {
    stop("Constituent vectors have unequal sizes"); // # nocov
  }

  return DataFrame::create(
    _["is_ipv6"] = out_v6,
    _["address1"] = out_addr1,
    _["address2"] = out_addr2,
    _["address3"] = out_addr3,
    _["address4"] = out_addr4,
    _["address5"] = out_addr5,
    _["address6"] = out_addr6,
    _["address7"] = out_addr7,
    _["address8"] = out_addr8
  );
}


/*------------*
 *  Networks  *
 * -----------*/
// [[Rcpp::export]]
List wrap_parse_network(CharacterVector x, bool strict) {
  return IpNetworkVector(x, strict).encodeR();
}

// [[Rcpp::export]]
List wrap_construct_network_from_address(List address_r, IntegerVector prefix_length, bool strict) {
  IpAddressVector address(address_r);

  return IpNetworkVector(address, prefix_length, strict, false).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_print_network(List x) {
  return IpNetworkVector(x).encodeStrings();
}


/*--------------*
 *  Interfaces  *
 * -------------*/
// [[Rcpp::export]]
List wrap_parse_interface(CharacterVector x) {
  return IpNetworkVector(x, false, true).encodeR();
}

// [[Rcpp::export]]
List wrap_construct_interface_from_address(List address, IntegerVector prefix_length) {
  return IpNetworkVector(IpAddressVector(address), prefix_length, false, true).encodeR();
}
