#include "IpAddressVector.h"
#include "IpNetworkVector.h"
#include "encoding.h"
#include "masking.h"
#include "utils.h"

#include <asio/ip/tcp.hpp>

using namespace Rcpp;


/*----------------*
 *  Constructors  *
 *----------------*/

IpAddressVector::IpAddressVector(CharacterVector input) {
  std::size_t vsize = input.size();

  // initialize vectors
  address_v4.assign(vsize, asio::ip::address_v4());
  address_v6.assign(vsize, asio::ip::address_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  asio::error_code ec;

  for (std::size_t i=0; i<vsize; ++i) {
    if (input[i] == NA_STRING) {
      is_na[i] = true;
    } else {
      address_v4[i] = asio::ip::make_address_v4(input[i], ec);
      if (ec) {
        address_v6[i] = asio::ip::make_address_v6(input[i], ec);
        if (ec) {
          is_na[i] = true;
          warnInvalidInput(i, Rcpp::as<std::string>(input[i]));
        } else {
          is_ipv6[i] = true;
        }
      }
    }
  }
}

IpAddressVector::IpAddressVector(List input) {
  // extract data
  IntegerVector in_addr1 = input["address1"];
  IntegerVector in_addr2 = input["address2"];
  IntegerVector in_addr3 = input["address3"];
  IntegerVector in_addr4 = input["address4"];
  LogicalVector in_v6 = input["is_ipv6"];

  std::size_t vsize = in_v6.size();

  // initialize vectors
  address_v4.assign(vsize, asio::ip::address_v4());
  address_v6.assign(vsize, asio::ip::address_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (in_v6[i] == NA_LOGICAL) {
      is_na[i] = true;
    } else if (in_v6[i]) {
      r_address_v6_type bytes = {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]};
      address_v6[i] = decode_r<asio::ip::address_v6>(bytes);
      is_ipv6[i] = true;
    } else {
      r_address_v4_type bytes = {in_addr1[i]};
      address_v4[i] = decode_r<asio::ip::address_v4>(bytes);
    }
  }
}

IpAddressVector IpAddressVector::decodePacked(List input) {
  std::size_t vsize = input.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> address_v4(vsize);
  std::vector<asio::ip::address_v6> address_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (input[i] == R_NilValue) {
      is_na[i] = true;
      continue;
    }

    RawVector raw = input[i];
    if (raw.size() == 4) {
      asio::ip::address_v4::bytes_type bytes;
      std::copy(raw.begin(), raw.end(), bytes.begin());
      address_v4[i] = asio::ip::address_v4(bytes);
    } else if (raw.size() == 16) {
      asio::ip::address_v6::bytes_type bytes;
      std::copy(raw.begin(), raw.end(), bytes.begin());
      address_v6[i] = asio::ip::address_v6(bytes);
      is_ipv6[i] = true;
    } else {
      is_na[i] = true;
      warnInvalidInput(i, "unable to decode");
    }
  }

  return IpAddressVector(address_v4, address_v6, is_ipv6, is_na);
}

IpAddressVector IpAddressVector::decodeInteger(CharacterVector input, Nullable<LogicalVector> in_v6) {
  std::size_t vsize = input.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> address_v4(vsize);
  std::vector<asio::ip::address_v6> address_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  bool guess_ipv6 = in_v6.isNull();

  for (std::size_t i=0; i<vsize; ++i) {
    if (input[i] == NA_STRING) {
      is_na[i] = true;
      continue;
    }

    std::string integer_string(input[i]);
    if (guess_ipv6) {
      try {
        address_v4[i] = decode_integer<asio::ip::address_v4>(integer_string);
      } catch (...) {
        try {
          address_v6[i] = decode_integer<asio::ip::address_v6>(integer_string);
          is_ipv6[i] = true;
        } catch (...) {
          warnInvalidInput(i, integer_string);
          is_na[i] = true;
        }
      }
    } else if (in_v6.as().at(i)) {
      try {
        address_v6[i] = decode_integer<asio::ip::address_v6>(integer_string);
        is_ipv6[i] = true;
      } catch (...) {
        warnInvalidInput(i, integer_string);
        is_na[i] = true;
      }
    } else {
      try {
        address_v4[i] = decode_integer<asio::ip::address_v4>(integer_string);
      } catch (...) {
        warnInvalidInput(i, integer_string);
        is_na[i] = true;
      }
    }
  }

  return IpAddressVector(address_v4, address_v6, is_ipv6, is_na);
}

IpAddressVector IpAddressVector::decodeBinary(CharacterVector input) {
  std::size_t vsize = input.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> address_v4(vsize);
  std::vector<asio::ip::address_v6> address_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (input[i] == NA_STRING) {
      is_na[i] = true;
      continue;
    }

    std::string bit_string(input[i]);
    if (bit_string.find_first_not_of("01") != std::string::npos) {
      is_na[i] = true;
      warnInvalidInput(i, "contains non-binary characters");
    } else if (bit_string.size() == 128) {
      address_v6[i] = decode_binary<asio::ip::address_v6>(bit_string);
      is_ipv6[i] = true;
    } else if (bit_string.size() == 32) {
      address_v4[i] = decode_binary<asio::ip::address_v4>(bit_string);
    } else {
      is_na[i] = true;
      warnInvalidInput(i, "incorrect number of bits");
    }
  }

  return IpAddressVector(address_v4, address_v6, is_ipv6, is_na);
}

List IpAddressVector::decodeHostname(CharacterVector input) {
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
    std::vector<asio::ip::address_v4> address_v4;
    std::vector<asio::ip::address_v6> address_v6;
    std::vector<bool> is_ipv6;
    std::vector<bool> is_na;

    if (input[i] == NA_STRING) {
      address_v4.resize(1);
      address_v6.resize(1);
      is_ipv6.resize(1);
      is_na.resize(1, true);
    } else {
      std::string hostname(input[i]);
      // forward DNS resolution
      auto results = resolver.resolve(hostname, "http", ec);

      if (ec) {
        if (ec != asio::error::host_not_found) {
          warnInvalidInput(i, hostname, ec.message());
        }
        address_v4.resize(1);
        address_v6.resize(1);
        is_ipv6.resize(1);
        is_na.resize(1, true);
      } else {
        for (auto const& entry : results) {
          auto address = entry.endpoint().address();
          if (address.is_v4()) {
            address_v4.push_back(address.to_v4());
            address_v6.push_back(asio::ip::address_v6());
            is_ipv6.push_back(false);
            is_na.push_back(false);
          } else {
            address_v6.push_back(address.to_v6());
            address_v4.push_back(asio::ip::address_v4());
            is_ipv6.push_back(true);
            is_na.push_back(false);
          }
        }
      }
    }

    output[i] = IpAddressVector(address_v4, address_v6, is_ipv6, is_na).encodeR();
  }

  return output;
}

IpAddressVector IpAddressVector::createNetmask(IntegerVector in_pfx, LogicalVector in_v6) {
  std::size_t vsize = in_v6.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> address_v4(vsize);
  std::vector<asio::ip::address_v6> address_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (in_v6[i] == NA_LOGICAL || in_pfx[i] == NA_INTEGER) {
      is_na[i] = true;
    } else if (in_v6[i]) {
      address_v6[i] = get_netmask<asio::ip::address_v6>(in_pfx[i]);
      is_ipv6[i] = true;
    } else {
      address_v4[i] = get_netmask<asio::ip::address_v4>(in_pfx[i]);
    }
  }

  return IpAddressVector(address_v4, address_v6, is_ipv6, is_na);
}

IpAddressVector IpAddressVector::createHostmask(IntegerVector in_pfx, LogicalVector in_v6) {
  std::size_t vsize = in_v6.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> address_v4(vsize);
  std::vector<asio::ip::address_v6> address_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (in_v6[i] == NA_LOGICAL || in_pfx[i] == NA_INTEGER) {
      is_na[i] = true;
    } else if (in_v6[i]) {
      address_v6[i] = get_hostmask<asio::ip::address_v6>(in_pfx[i]);
      is_ipv6[i] = true;
    } else {
      address_v4[i] = get_hostmask<asio::ip::address_v4>(in_pfx[i]);
    }
  }

  return IpAddressVector(address_v4, address_v6, is_ipv6, is_na);
}

void IpAddressVector::warnInvalidInput(unsigned int index, const std::string &input, const std::string &reason) {
  // Indexes are 1-based in R
  std::string msg = "Invalid value on row " + std::to_string(index + 1) + ": " + input;
  if (!reason.empty()) {
    msg += " (" + reason + ")";
  }

  Rf_warningcall(R_NilValue, msg.c_str());
}


/*----------*
 *  Output  *
 *----------*/

List IpAddressVector::encodeR() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  IntegerVector out_addr1(vsize);
  IntegerVector out_addr2(vsize);
  IntegerVector out_addr3(vsize);
  IntegerVector out_addr4(vsize);
  LogicalVector out_v6(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      r_address_v6_type bytes = encode_r<r_address_v6_type>(address_v6[i]);
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_v6[i] = true;
    } else {
      r_address_v4_type bytes = encode_r<r_address_v4_type>(address_v4[i]);
      out_addr1[i] = bytes[0];
    }
  }

  if (out_addr1.size() != out_v6.size() ||
      out_addr2.size() != out_v6.size() ||
      out_addr3.size() != out_v6.size() ||
      out_addr4.size() != out_v6.size()) {
    stop("Consistuent vectors have unequal sizes");
  }

  List result = List::create(
    _["address1"] = out_addr1,
    _["address2"] = out_addr2,
    _["address3"] = out_addr3,
    _["address4"] = out_addr4,
    _["is_ipv6"] = out_v6
  );

  result.attr("class") = CharacterVector::create(
    "ip_address",
    "vctrs_rcrd",
    "vctrs_vctr"
  );

  return result;
}

CharacterVector IpAddressVector::encodeStrings() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_STRING;
    } else if (is_ipv6[i]) {
      output[i] = address_v6[i].to_string();
    } else {
      output[i] = address_v4[i].to_string();
    }
  }

  return output;
}

List IpAddressVector::encodePacked() const {
  std::size_t vsize = is_na.size();

  List output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = R_NilValue;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6::bytes_type bytes = address_v6[i].to_bytes();
      RawVector raw(bytes.size());
      std::copy(bytes.begin(), bytes.end(), raw.begin());
      output[i] = raw;
    } else {
      asio::ip::address_v4::bytes_type bytes = address_v4[i].to_bytes();
      RawVector raw(bytes.size());
      std::copy(bytes.begin(), bytes.end(), raw.begin());
      output[i] = raw;
    }
  }

  return output;
}

CharacterVector IpAddressVector::encodeInteger() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_STRING;
    } else if (is_ipv6[i]) {
      output[i] = encode_integer(address_v6[i]);
    } else {
      output[i] = encode_integer(address_v4[i]);
    }
  }

  return output;
}

CharacterVector IpAddressVector::encodeBinary() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_STRING;
    } else if (is_ipv6[i]) {
      output[i] = encode_binary(address_v6[i]);
    } else {
      output[i] = encode_binary(address_v4[i]);
    }
  }

  return output;
}

List IpAddressVector::encodeHostnames() const {
  std::size_t vsize = is_na.size();
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
    if (is_na[i]) {
      hostnames.push_back(NA_STRING);
    } else {
      if (is_ipv6[i]) {
        endpoint.address(address_v6[i]);
      } else {
        endpoint.address(address_v4[i]);
      }

      // reverse DNS resolution
      auto results = resolver.resolve(endpoint, ec);

      if (ec) {
        warnInvalidInput(i, endpoint.address().to_string(), ec.message());
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

DataFrame IpAddressVector::encodeComparable() const {
  std::size_t vsize = is_na.size();

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
    if (is_na[i]) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_addr5[i] = NA_INTEGER;
      out_addr6[i] = NA_INTEGER;
      out_addr7[i] = NA_INTEGER;
      out_addr8[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      r_address_v6_type bytes = encode_r<r_address_v6_type>(address_v6[i]);
      out_addr1[i] = (bytes[0] & left_mask) >> 16;
      out_addr2[i] = (bytes[0] & right_mask);
      out_addr3[i] = (bytes[1] & left_mask) >> 16;
      out_addr4[i] = (bytes[1] & right_mask);
      out_addr5[i] = (bytes[2] & left_mask) >> 16;
      out_addr6[i] = (bytes[2] & right_mask);
      out_addr7[i] = (bytes[3] & left_mask) >> 16;
      out_addr8[i] = (bytes[3] & right_mask);
      out_v6[i] = true;
    } else {
      r_address_v4_type bytes = encode_r<r_address_v4_type>(address_v4[i]);
      out_addr1[i] = (bytes[0] & left_mask) >> 16;
      out_addr2[i] = (bytes[0] & right_mask);
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
    stop("Consistuent vectors have unequal sizes");
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


/*-------------*
 *  Operators  *
 *-------------*/
IpAddressVector IpAddressVector::operator~() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i]) {
      out_address_v6[i] = bitwise_not(address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_not(address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}

IpAddressVector IpAddressVector::operator&(const IpAddressVector &rhs) const {
  std::size_t vsize = is_na.size();

  if (rhs.is_na.size() != vsize) {
    stop("Addresses must have same length");
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i] || rhs.is_na[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i] != rhs.is_ipv6[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i]) {
      out_address_v6[i] = bitwise_and(address_v6[i], rhs.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_and(address_v4[i], rhs.address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}

IpAddressVector IpAddressVector::operator|(const IpAddressVector &rhs) const {
  std::size_t vsize = is_na.size();

  if (rhs.is_na.size() != vsize) {
    stop("Addresses must have same length");
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i] || rhs.is_na[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i] != rhs.is_ipv6[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i]) {
      out_address_v6[i] = bitwise_or(address_v6[i], rhs.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_or(address_v4[i], rhs.address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}

IpAddressVector IpAddressVector::operator^(const IpAddressVector &rhs) const {
  std::size_t vsize = is_na.size();

  if (rhs.is_na.size() != vsize) {
    stop("Addresses must have same length");
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i] || rhs.is_na[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i] != rhs.is_ipv6[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i]) {
      out_address_v6[i] = bitwise_xor(address_v6[i], rhs.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_xor(address_v4[i], rhs.address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}

IpAddressVector IpAddressVector::operator+(const IntegerVector &rhs) const {
  std::size_t vsize = is_na.size();

  if (rhs.size() != static_cast<R_xlen_t>(vsize)) {
    stop("Addresses must have same length");
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6 tmp_addr = advance_ip(address_v6[i], rhs[i]);

      if (rhs[i] > 0 && tmp_addr < address_v6[i]) {
        out_is_na[i] = true;
        warnInvalidInput(i, address_v6[i].to_string() + " + " + std::to_string(rhs[i]),
                         "out-of-range");
      } else if (rhs[i] < 0 && tmp_addr > address_v6[i]) {
        out_is_na[i] = true;
        warnInvalidInput(i, address_v6[i].to_string() + " - " + std::to_string(-rhs[i]),
                         "out-of-range");
      } else {
        out_address_v6[i] = tmp_addr;
        out_is_ipv6[i] = true;
      }
    } else {
      asio::ip::address_v4 tmp_addr = advance_ip(address_v4[i], rhs[i]);

      if (rhs[i] > 0 && tmp_addr < address_v4[i]) {
        out_is_na[i] = true;
        warnInvalidInput(i, address_v4[i].to_string() + " + " + std::to_string(rhs[i]),
                         "out-of-range");
      } else if (rhs[i] < 0 && tmp_addr > address_v4[i]) {
        out_is_na[i] = true;
        warnInvalidInput(i, address_v4[i].to_string() + " - " + std::to_string(-rhs[i]),
                         "out-of-range");
      } else {
        out_address_v4[i] = tmp_addr;
      }
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}


/*-----------------------*
 *  Other functionality  *
 *-----------------------*/

LogicalVector IpAddressVector::isWithin(const IpNetworkVector &network) const {
  std::size_t vsize = is_na.size();

  if (network.is_na.size() != vsize) {
    stop("Address and network must have same length");
  }

  // initialize vectors
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i] || network.is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i] != network.is_ipv6[i]) {
      output[i] = false;
    } else if (is_ipv6[i]) {
      output[i] = address_in_network(address_v6[i], network.network_v6[i]);
    } else {
      output[i] = address_in_network(address_v4[i], network.network_v4[i]);
    }
  }

  return output;
}

LogicalVector IpAddressVector::isWithinAny(const IpNetworkVector &network) const {
  std::size_t address_size = is_na.size();
  std::size_t network_size = network.is_na.size();

  // initialize vectors
  LogicalVector output(address_size);

  for (std::size_t i_addr=0; i_addr<address_size; ++i_addr) {
    if (is_na[i_addr]) {
      output[i_addr] = NA_LOGICAL;
    } else {
      output[i_addr] = false;
      for (std::size_t i_netw=0; i_netw<network_size; ++i_netw) {
        if (network.is_na[i_netw] || is_ipv6[i_addr] != network.is_ipv6[i_netw]) {
          continue;
        } else if (is_ipv6[i_addr] && address_in_network(address_v6[i_addr], network.network_v6[i_netw])) {
          output[i_addr] = true;
        } else if (address_in_network(address_v4[i_addr], network.network_v4[i_netw])) {
          output[i_addr] = true;
        }
      }
    }
  }

  return output;
}


/*----------------------*
 *  Reserved addresses  *
 * ---------------------*/
LogicalVector IpAddressVector::isMulticast() const {
  return isTrue(
    [](const asio::ip::address_v4 &x) { return x.is_multicast(); },
    [](const asio::ip::address_v6 &x) { return x.is_multicast(); }
  );
}

LogicalVector IpAddressVector::isUnspecified() const {
  return isTrue(
    [](const asio::ip::address_v4 &x) { return x.is_unspecified(); },
    [](const asio::ip::address_v6 &x) { return x.is_unspecified(); }
  );
}

LogicalVector IpAddressVector::isLoopback() const {
  return isTrue(
    [](const asio::ip::address_v4 &x) { return x.is_loopback(); },
    [](const asio::ip::address_v6 &x) { return x.is_loopback(); }
  );
}

LogicalVector IpAddressVector::isLinkLocal() const {
  return isTrue(
    [](const asio::ip::address_v4 &x) { return (x.to_uint() & 0xFFFF0000) == 0xA9FE0000; },
    [](const asio::ip::address_v6 &x) { return x.is_link_local(); }
  );
}


/*------------------------------*
 *  IPv6 transition mechanisms  *
 * -----------------------------*/
LogicalVector IpAddressVector::isIPv4Mapped() const {
  return isTrue(
    [](const asio::ip::address_v4 &x) { return false; },
    [](const asio::ip::address_v6 &x) { return x.is_v4_mapped(); }
  );
}

IpAddressVector IpAddressVector::extractIPv4Mapped() const {
  return map6to4(
    [](const asio::ip::address_v6 &x) { return x.is_v4_mapped(); },
    [](const asio::ip::address_v6 &x) { return asio::ip::make_address_v4(asio::ip::v4_mapped, x); }
  );
}

LogicalVector IpAddressVector::is6to4() const {
  return isTrue(
    [](const asio::ip::address_v4 &x) { return false; },
    [](const asio::ip::address_v6 &x) { return is_6to4(x); }
  );
}

IpAddressVector IpAddressVector::extract6to4() const {
  return map6to4(
    [](const asio::ip::address_v6 &x) { return is_6to4(x); },
    [](const asio::ip::address_v6 &x) { return extract_6to4(x); }
  );
}

LogicalVector IpAddressVector::isTeredo() const {
  return isTrue(
    [](const asio::ip::address_v4 &x) { return false; },
    [](const asio::ip::address_v6 &x) { return is_teredo(x); }
  );
}

IpAddressVector IpAddressVector::extractTeredoServer() const {
  return map6to4(
    [](const asio::ip::address_v6 &x) { return is_teredo(x); },
    [](const asio::ip::address_v6 &x) { return extract_teredo_server(x); }
  );
}

IpAddressVector IpAddressVector::extractTeredoClient() const {
  return map6to4(
    [](const asio::ip::address_v6 &x) { return is_teredo(x); },
    [](const asio::ip::address_v6 &x) { return extract_teredo_client(x); }
  );
}


/*----------------*
 *  Common tasks  *
 * ---------------*/
LogicalVector IpAddressVector::isTrue(
    const std::function<bool(const asio::ip::address_v4&)>& decide_fn_v4,
    const std::function<bool(const asio::ip::address_v6&)>& decide_fn_v6
) const {
  std::size_t vsize = is_na.size();
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      output[i] = decide_fn_v6(address_v6[i]);
    } else {
      output[i] = decide_fn_v4(address_v4[i]);
    }
  }

  return output;
}

IpAddressVector IpAddressVector::map6to4(
    const std::function<bool(const asio::ip::address_v6&)>& filter_fn,
    const std::function<asio::ip::address_v4(const asio::ip::address_v6&)>& map_fn
) const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_ipv6[i] && filter_fn(address_v6[i])) {
      out_address_v4[i] = map_fn(address_v6[i]);
    } else {
      out_is_na[i] = true;
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}
