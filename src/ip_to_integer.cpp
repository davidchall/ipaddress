#include <Rcpp.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <ipaddress.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


std::string encode_integer(const IpAddress &x, bool hex) {
  const std::size_t n_bits = x.n_bits();

  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<
    128, 128,
    boost::multiprecision::unsigned_magnitude,
    boost::multiprecision::checked,
    void
    >> x_int;

  // import most-significant byte first (x_bytes stored in network order)
  import_bits(x_int, x.begin(), x.end(), 8, true);

  if (hex) {
    std::stringstream ss;
    ss << "0x" << std::hex << std::setfill('0') << std::setw(n_bits/4) << std::uppercase <<  x_int;
    return ss.str();
  } else {
    return x_int.str();
  }
}


template<class Bytes>
Bytes decode_integer(const std::string& x_int_string) {
  Bytes x_bytes{};

  boost::multiprecision::number<boost::multiprecision::cpp_int_backend<
    8*sizeof(x_bytes), 8*sizeof(x_bytes),
    boost::multiprecision::unsigned_magnitude,
    boost::multiprecision::checked,
    void
    >> x_int(x_int_string);

  // must export least-significant byte first because boost::multiprecision is
  // aggressively optimized and does not reserve space for unused bits,
  // even though I've declared the size of the integer as 32-bit or 128-bit
  export_bits(x_int, x_bytes.begin(), 8, false);
  std::reverse(x_bytes.begin(), x_bytes.end());

  return x_bytes;
}


// [[Rcpp::export]]
List wrap_decode_integer(CharacterVector input, Nullable<LogicalVector> in_is_ipv6) {
  // initialize vectors
  std::size_t vsize = input.size();
  std::vector<IpAddress> output(vsize);

  bool guess_ipv6 = in_is_ipv6.isNull();

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == NA_STRING) {
      output[i] = IpAddress::make_na();
      continue;
    }

    std::string integer_string(input[i]);
    if (guess_ipv6) {
      try {
        auto bytes = decode_integer<IpAddress::bytes_type_v4>(integer_string);
        output[i] = IpAddress::make_ipv4(bytes);
      } catch (...) {
        try {
          auto bytes = decode_integer<IpAddress::bytes_type_v6>(integer_string);
          output[i] = IpAddress::make_ipv6(bytes);
        } catch (...) {
          warnOnRow(i, integer_string);
          output[i] = IpAddress::make_na();
        }
      }
    } else if (in_is_ipv6.as().at(i)) {
      try {
        auto bytes = decode_integer<IpAddress::bytes_type_v6>(integer_string);
        output[i] = IpAddress::make_ipv6(bytes);
      } catch (...) {
        warnOnRow(i, integer_string);
        output[i] = IpAddress::make_na();
      }
    } else {
      try {
        auto bytes = decode_integer<IpAddress::bytes_type_v4>(integer_string);
        output[i] = IpAddress::make_ipv4(bytes);
      } catch (...) {
        warnOnRow(i, integer_string);
        output[i] = IpAddress::make_na();
      }
    }
  }

  return encode_addresses(output);
}


// [[Rcpp::export]]
CharacterVector wrap_encode_integer(List input, bool hex) {
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
      output[i] = encode_integer(address[i], hex);
    }
  }

  return output;
}
