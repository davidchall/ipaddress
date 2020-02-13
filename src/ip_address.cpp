#define ASIO_STANDALONE

#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>

using namespace Rcpp;

// [[Rcpp::export]]
IntegerVector ipv4_address_aton(CharacterVector x) {

  IntegerVector out(x.size());

  CharacterVector::iterator it;
  IntegerVector::iterator out_it;

  for (it = x.begin(), out_it = out.begin(); it != x.end(); ++it, ++out_it) {
    if (*it == NA_STRING) {
      *out_it = NA_INTEGER;
    } else {
      asio::ip::address_v4 address = asio::ip::make_address_v4(*it);
      *out_it = (signed int)address.to_uint();
    }
  }

  return out;
}

// [[Rcpp::export]]
CharacterVector ipv4_address_ntoa(IntegerVector x) {

  CharacterVector out(x.size());

  IntegerVector::iterator it;
  CharacterVector::iterator out_it;

  for (it = x.begin(), out_it = out.begin(); it != x.end(); ++it, ++out_it) {
    if (*it == NA_INTEGER) {
      *out_it = NA_STRING;
    } else {
      asio::ip::address_v4 address = asio::ip::make_address_v4((unsigned int)*it);
      *out_it = address.to_string();
    }
  }

  return out;
}
