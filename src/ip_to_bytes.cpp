#include <Rcpp.h>
#include <ipaddress.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_decode_bytes(List input) {
  // initialize vectors
  std::size_t vsize = input.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == R_NilValue) {
      output[i] = IpAddress::make_na();
      continue;
    }

    RawVector raw = input[i];
    if (raw.size() == 4) {
      IpAddress::bytes_type_v4 bytes;
      std::copy(raw.begin(), raw.end(), bytes.begin());
      output[i] = IpAddress::make_ipv4(bytes);
    } else if (raw.size() == 16) {
      IpAddress::bytes_type_v6 bytes;
      std::copy(raw.begin(), raw.end(), bytes.begin());
      output[i] = IpAddress::make_ipv6(bytes);
    } else {
      output[i] = IpAddress::make_na();
      warnOnRow(i, "unable to decode (must be 4 or 16 bytes)");
    }
  }

  return encode_addresses(output);
}

// [[Rcpp::export]]
List wrap_encode_bytes(List input) {
  std::vector<IpAddress> address = decode_addresses(input);

  // initialize vectors
  std::size_t vsize = address.size();
  List output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = R_NilValue;
    } else if (address[i].is_ipv6()) {
      auto bytes = address[i].bytes_v6();
      RawVector raw(bytes.size());
      std::copy(bytes.begin(), bytes.end(), raw.begin());
      output[i] = raw;
    } else {
      auto bytes = address[i].bytes_v4();
      RawVector raw(bytes.size());
      std::copy(bytes.begin(), bytes.end(), raw.begin());
      output[i] = raw;
    }
  }

  return output;
}
