#include <Rcpp.h>
#include <bitset>
#include <ipaddress.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


std::string encode_binary(const IpAddress &input) {
  std::string output;
  output.reserve(input.n_bits());

  for (auto it = input.begin(); it != input.end(); ++it) {
    std::bitset<8> bits(*it);
    output += bits.to_string();
  }

  return output;
}

IpAddress decode_binary(const std::string &input, bool is_ipv6) {
  IpAddress output = is_ipv6 ? IpAddress::make_ipv6() : IpAddress::make_ipv4();

  unsigned int pos_char = 0;
  for (auto it = output.begin(); it != output.end(); ++it, pos_char += 8) {
    std::bitset<8> bits(input.substr(pos_char, 8));
    *it = bits.to_ulong();
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
CharacterVector wrap_encode_binary(List address_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);

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
