#include <Rcpp.h>
#include <ipaddress.h>
#include <ipaddress/to_string.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_netmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6) {
  // initialize vectors
  std::size_t vsize = in_is_ipv6.size();
  std::vector<IpAddress> output(vsize);

  if (static_cast<std::size_t>(in_prefix_length.size()) != vsize) {
    stop("Prefix length and IPv6 status must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (in_is_ipv6[i] == NA_LOGICAL || in_prefix_length[i] == NA_INTEGER) {
      output[i] = IpAddress::make_na();
    } else {
      output[i] = prefix_to_netmask(in_prefix_length[i], in_is_ipv6[i]);
    }
  }

  return encode_addresses(output);
}


// [[Rcpp::export]]
List wrap_hostmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6) {
  // initialize vectors
  std::size_t vsize = in_is_ipv6.size();
  std::vector<IpAddress> output(vsize);

  if (static_cast<std::size_t>(in_prefix_length.size()) != vsize) {
    stop("Prefix length and IPv6 status must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (in_is_ipv6[i] == NA_LOGICAL || in_prefix_length[i] == NA_INTEGER) {
      output[i] = IpAddress::make_na();
    } else {
      output[i] = prefix_to_hostmask(in_prefix_length[i], in_is_ipv6[i]);
    }
  }

  return encode_addresses(output);
}


// [[Rcpp::export]]
IntegerVector wrap_prefix_from_mask(List address_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);

  // initialize vectors
  std::size_t vsize = address.size();
  IntegerVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = NA_INTEGER;
    } else {
      int prefix = netmask_to_prefix(address[i]);
      if (prefix < 0) {
        prefix = hostmask_to_prefix(address[i]);
      }
      if (prefix < 0) {
        warnOnRow(i, to_string(address[i]), "invalid netmask/hostmask");
        output[i] = NA_INTEGER;
      } else {
        output[i] = prefix;
      }
    }
  }

  return output;
}
