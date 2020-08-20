#include <Rcpp.h>
#include <asio/ip/tcp.hpp>
#include <ipaddress/IpAddressVector.h>
#include "other_repr.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_decode_bytes(List input) {
  std::size_t vsize = input.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == R_NilValue) {
      out_is_na[i] = true;
      continue;
    }

    RawVector raw = input[i];
    if (raw.size() == 4) {
      asio::ip::address_v4::bytes_type bytes;
      std::copy(raw.begin(), raw.end(), bytes.begin());
      out_address_v4[i] = asio::ip::address_v4(bytes);
    } else if (raw.size() == 16) {
      asio::ip::address_v6::bytes_type bytes;
      std::copy(raw.begin(), raw.end(), bytes.begin());
      out_address_v6[i] = asio::ip::address_v6(bytes);
      out_is_ipv6[i] = true;
    } else {
      out_is_na[i] = true;
      warnOnRow(i, "unable to decode");
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_encode_bytes(List input) {
  IpAddressVector address(input);

  std::size_t vsize = address.size();
  List output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_na[i]) {
      output[i] = R_NilValue;
    } else if (address.is_ipv6[i]) {
      asio::ip::address_v6::bytes_type bytes = address.address_v6[i].to_bytes();
      RawVector raw(bytes.size());
      std::copy(bytes.begin(), bytes.end(), raw.begin());
      output[i] = raw;
    } else {
      asio::ip::address_v4::bytes_type bytes = address.address_v4[i].to_bytes();
      RawVector raw(bytes.size());
      std::copy(bytes.begin(), bytes.end(), raw.begin());
      output[i] = raw;
    }
  }

  return output;
}

// [[Rcpp::export]]
List wrap_decode_integer(CharacterVector input, Nullable<LogicalVector> in_is_ipv6) {
  std::size_t vsize = input.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  bool guess_ipv6 = in_is_ipv6.isNull();

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == NA_STRING) {
      out_is_na[i] = true;
      continue;
    }

    std::string integer_string(input[i]);
    if (guess_ipv6) {
      try {
        out_address_v4[i] = decode_integer<asio::ip::address_v4>(integer_string);
      } catch (...) {
        try {
          out_address_v6[i] = decode_integer<asio::ip::address_v6>(integer_string);
          out_is_ipv6[i] = true;
        } catch (...) {
          warnOnRow(i, integer_string);
          out_is_na[i] = true;
        }
      }
    } else if (in_is_ipv6.as().at(i)) {
      try {
        out_address_v6[i] = decode_integer<asio::ip::address_v6>(integer_string);
        out_is_ipv6[i] = true;
      } catch (...) {
        warnOnRow(i, integer_string);
        out_is_na[i] = true;
      }
    } else {
      try {
        out_address_v4[i] = decode_integer<asio::ip::address_v4>(integer_string);
      } catch (...) {
        warnOnRow(i, integer_string);
        out_is_na[i] = true;
      }
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_encode_integer(List input, bool hex) {
  IpAddressVector address(input);

  std::size_t vsize = address.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_na[i]) {
      output[i] = NA_STRING;
    } else if (address.is_ipv6[i]) {
      output[i] = encode_integer(address.address_v6[i], hex);
    } else {
      output[i] = encode_integer(address.address_v4[i], hex);
    }
  }

  return output;
}

// [[Rcpp::export]]
List wrap_decode_binary(CharacterVector input) {
  std::size_t vsize = input.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == NA_STRING) {
      out_is_na[i] = true;
      continue;
    }

    std::string bit_string(input[i]);
    if (bit_string.find_first_not_of("01") != std::string::npos) {
      out_is_na[i] = true;
      warnOnRow(i, bit_string, "contains non-binary characters");
    } else if (bit_string.size() == 128) {
      out_address_v6[i] = decode_binary<asio::ip::address_v6>(bit_string);
      out_is_ipv6[i] = true;
    } else if (bit_string.size() == 32) {
      out_address_v4[i] = decode_binary<asio::ip::address_v4>(bit_string);
    } else {
      out_is_na[i] = true;
      warnOnRow(i, bit_string, "incorrect number of bits");
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
CharacterVector wrap_encode_binary(List input) {
  IpAddressVector address(input);

  std::size_t vsize = address.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_na[i]) {
      output[i] = NA_STRING;
    } else if (address.is_ipv6[i]) {
      output[i] = encode_binary(address.address_v6[i]);
    } else {
      output[i] = encode_binary(address.address_v4[i]);
    }
  }

  return output;
}

// [[Rcpp::export]]
List wrap_decode_hostname(CharacterVector input) {
  std::size_t vsize = input.size();
  List output(vsize);

  asio::io_context io_context;
  asio::ip::tcp::resolver resolver(io_context);
  asio::ip::tcp::endpoint endpoint;
  asio::error_code ec;

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 100 == 0) {
      checkUserInterrupt();
    }

    // initialize vectors
    std::vector<asio::ip::address_v4> out_address_v4;
    std::vector<asio::ip::address_v6> out_address_v6;
    std::vector<bool> out_is_ipv6;
    std::vector<bool> out_is_na;

    if (input[i] == NA_STRING) {
      out_address_v4.resize(1);
      out_address_v6.resize(1);
      out_is_ipv6.resize(1);
      out_is_na.resize(1, true);
    } else {
      std::string hostname(input[i]);
      // forward DNS resolution
      auto results = resolver.resolve(hostname, "http", ec);

      if (ec) {
        if (ec != asio::error::host_not_found) {
          warnOnRow(i, hostname, ec.message());
        }
        out_address_v4.resize(1);
        out_address_v6.resize(1);
        out_is_ipv6.resize(1);
        out_is_na.resize(1, true);
      } else {
        for (auto const& entry : results) {
          auto address = entry.endpoint().address();
          if (address.is_v4()) {
            out_address_v4.push_back(address.to_v4());
            out_address_v6.push_back(asio::ip::address_v6());
            out_is_ipv6.push_back(false);
            out_is_na.push_back(false);
          } else {
            out_address_v6.push_back(address.to_v6());
            out_address_v4.push_back(asio::ip::address_v4());
            out_is_ipv6.push_back(true);
            out_is_na.push_back(false);
          }
        }
      }
    }

    output[i] = IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
  }

  return output;
}

// [[Rcpp::export]]
List wrap_encode_hostname(List input) {
  IpAddressVector address(input);

  std::size_t vsize = address.size();
  List output(vsize);

  asio::io_context io_context;
  asio::ip::tcp::resolver resolver(io_context);
  asio::ip::tcp::endpoint endpoint;
  asio::error_code ec;

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 100 == 0) {
      checkUserInterrupt();
    }

    CharacterVector hostnames;
    if (address.is_na[i]) {
      hostnames.push_back(NA_STRING);
    } else {
      if (address.is_ipv6[i]) {
        endpoint.address(address.address_v6[i]);
      } else {
        endpoint.address(address.address_v4[i]);
      }

      // reverse DNS resolution
      auto results = resolver.resolve(endpoint, ec);

      if (ec) {
        warnOnRow(i, endpoint.address().to_string(), ec.message());
        hostnames.push_back(NA_STRING);
      } else {
        for (auto const& entry : results) {
          // unresolved hostnames often returned as original IP address
          if (entry.host_name() != endpoint.address().to_string()) {
            hostnames.push_back(entry.host_name());
          }
        }
        if (hostnames.size() == 0) {
          hostnames.push_back(NA_STRING);
        }
      }
    }

    output[i] = hostnames;
  }

  return output;
}

// [[Rcpp::export]]
CharacterVector wrap_reverse_pointer(List input) {
  IpAddressVector address(input);

  std::size_t vsize = address.size();
  std::ostringstream os;
  char buffer[40];

  // initialize vectors
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_na[i]) {
      output[i] = NA_STRING;
    } else if (address.is_ipv6[i]) {
      auto bytes = address.address_v6[i].to_bytes();

      sprintf(
        buffer,
        "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
        bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
        bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]
      );
      std::string str(buffer);
      std::reverse(str.begin(), str.end());
      std::copy(str.begin(), str.end(), std::ostream_iterator<char>(os, "."));
      str = os.str();
      str += "ip.arpa";

      output[i] = str;
    } else {
      auto bytes = address.address_v4[i].to_bytes();
      sprintf(
        buffer,
        "%i.%i.%i.%i.in-addr.arpa",
        bytes[3], bytes[2], bytes[1], bytes[0]
      );

      output[i] = std::string(buffer);
    }
  }

  return output;
}
