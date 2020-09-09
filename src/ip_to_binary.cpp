#include <Rcpp.h>
#include <ipaddress.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


std::string encode_binary(const IpAddress &x) {
  std::string bit_string;
  bit_string.reserve(x.n_bits());

  for (std::size_t i=0; i<x.n_bytes(); ++i) {
    std::bitset<8> bits(x.bytes[i]);
    bit_string += bits.to_string();
  }

  return bit_string;
}

IpAddress decode_binary(const std::string &bit_string, bool is_ipv6) {
  IpAddress output(IpAddress::bytes_type_both(), is_ipv6, false);

  for (std::size_t i=0; i<output.n_bytes(); ++i) {
    std::bitset<8> bits(bit_string.substr(i*8, 8));
    output.bytes[i] = bits.to_ulong();
  }

  return output;
}

// [[Rcpp::export]]
List wrap_decode_binary(CharacterVector input) {
  // initialize vectors
  std::size_t vsize = input.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == NA_STRING) {
      output[i] = IpAddress::make_na();
      continue;
    }

    std::string bit_string(input[i]);
    if (bit_string.find_first_not_of("01") != std::string::npos) {
      output[i] = IpAddress::make_na();
      warnOnRow(i, bit_string, "contains non-binary characters");
    } else if (bit_string.size() == 128) {
      output[i] = decode_binary(bit_string, true);
    } else if (bit_string.size() == 32) {
      output[i] = decode_binary(bit_string, false);
    } else {
      output[i] = IpAddress::make_na();
      warnOnRow(i, bit_string, "incorrect number of bits");
    }
  }

  return encode_addresses(output);
}

// [[Rcpp::export]]
CharacterVector wrap_encode_binary(List input) {
  std::vector<IpAddress> address = decode_addresses(input);

  // initialize vectors
  std::size_t vsize = address.size();
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = NA_STRING;
    } else {
      output[i] = encode_binary(address[i]);
    }
  }

  return output;
}
