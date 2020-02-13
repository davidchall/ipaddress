#define ASIO_STANDALONE

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>

using namespace Rcpp;

// [[Rcpp::export]]
List ipv4_network_aton(CharacterVector x) {

  IntegerVector address(x.size());
  IntegerVector prefix(x.size());

  CharacterVector::iterator it;
  IntegerVector::iterator a_it;
  IntegerVector::iterator p_it;

  for (it = x.begin(), a_it = address.begin(), p_it = prefix.begin(); it != x.end(); ++it, ++a_it, ++p_it) {
    if (*it == NA_STRING) {
      *a_it = NA_INTEGER;
      *p_it = NA_INTEGER;
    } else {
      asio::ip::network_v4 network = asio::ip::make_network_v4(*it);
      *a_it = (signed int)network.network().to_uint();
      *p_it = network.prefix_length();
    }
  }

  return List::create(
    _["address"] = address,
    _["prefix"] = prefix
  );
}

// [[Rcpp::export]]
CharacterVector ipv4_network_ntoa(IntegerVector address, IntegerVector prefix) {

  CharacterVector out(address.size());

  IntegerVector::iterator a_it;
  IntegerVector::iterator p_it;
  CharacterVector::iterator out_it;

  for (a_it = address.begin(), p_it = prefix.begin(), out_it = out.begin(); a_it != address.end(); ++a_it, ++p_it, ++out_it) {
    if (*a_it == NA_INTEGER || *p_it == NA_INTEGER) {
      *out_it = NA_STRING;
    } else {
      asio::ip::address_v4 address = asio::ip::make_address_v4((unsigned int)*a_it);
      asio::ip::network_v4 network = asio::ip::network_v4(address, *p_it);
      *out_it = network.to_string();
    }
  }

  return out;
}
