#include <Rcpp.h>
#include <ipaddress.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


IpAddress decode_ipv4_hex(const std::string& hex) {
  uint32_t input = host_to_network_long(std::stoul(hex, nullptr, 16));

  IpAddress::bytes_type_v4 output;
  std::memcpy(output.begin(), &input, output.size());
  return IpAddress::make_ipv4(output);
}


IpAddress decode_ipv6_hex(const std::string& hex) {
  // strip base
  std::string x = hex.substr(2, hex.size());

  // left pad
  unsigned int total_chars = 32;
  if (x.size() < total_chars) {
    x.insert(x.begin(), total_chars - x.size(), '0');
  }

  std::size_t j = 0;
  std::array<uint32_t, 4> input;
  for (std::size_t i=0; i<x.size(); i += 8) {
    input[j++] = host_to_network_long(std::stoul(x.substr(i, 8), nullptr, 16));
  }

  IpAddress::bytes_type_v6 output;
  std::memcpy(output.begin(), input.begin(), output.size());
  return IpAddress::make_ipv6(output);
}


// [[Rcpp::export]]
List wrap_decode_hex(CharacterVector input, LogicalVector in_is_ipv6) {
  // initialize vectors
  std::size_t vsize = input.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 8192 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == NA_STRING) {
      output[i] = IpAddress::make_na();
      continue;
    }

    std::string hex(input[i]);
    if (in_is_ipv6[i]) {
      output[i] = decode_ipv6_hex(hex);
    } else {
      output[i] = decode_ipv4_hex(hex);
    }
  }

  return encode_addresses(output);
}


// [[Rcpp::export]]
CharacterVector wrap_encode_hex(List input) {
  std::vector<IpAddress> address = decode_addresses(input);

  // initialize vectors
  std::size_t vsize = address.size();
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 8192 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = NA_STRING;
    } else if (address[i].is_ipv6()) {
      char buffer[40];
      auto bytes = address[i].bytes_v6();
      snprintf(
        buffer, 40,
        "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
        bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
        bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]
      );

      output[i] = "0x" + std::string(buffer);
    } else {
      char buffer[10];
      auto bytes = address[i].bytes_v4();
      snprintf(
        buffer, 10,
        "%02X%02X%02X%02X",
        bytes[0], bytes[1], bytes[2], bytes[3]
      );

      output[i] = "0x" + std::string(buffer);
    }
  }

  return output;
}
