#include "IpAddressVector.h"
#include "encoding.h"

IpAddressVector::IpAddressVector(CharacterVector input) {
  unsigned int vsize = input.size();

  // initialize vectors
  address_v4.assign(vsize, asio::ip::address_v4());
  address_v6.assign(vsize, asio::ip::address_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  asio::error_code ec;

  for (unsigned int i=0; i<vsize; ++i) {
    if (input[i] == NA_STRING) {
      is_na[i] = true;
    } else {
      address_v4[i] = asio::ip::make_address_v4(input[i], ec);
      if (ec) {
        address_v6[i] = asio::ip::make_address_v6(input[i], ec);
        if (ec) {
          is_na[i] = true;
          warning(ec.message() + ": " + input[i]);
        } else {
          is_ipv6[i] = true;
        }
      }
    }
  }
}

IpAddressVector::IpAddressVector(List input) {
  // extract data
  IntegerVector in_addr1 = as<IntegerVector>(input["address1"]);
  IntegerVector in_addr2 = as<IntegerVector>(input["address2"]);
  IntegerVector in_addr3 = as<IntegerVector>(input["address3"]);
  IntegerVector in_addr4 = as<IntegerVector>(input["address4"]);
  LogicalVector in_v6 = as<LogicalVector>(input["is_ipv6"]);

  unsigned int vsize = in_v6.size();

  // initialize vectors
  address_v4.assign(vsize, asio::ip::address_v4());
  address_v6.assign(vsize, asio::ip::address_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  for (unsigned int i=0; i<vsize; ++i) {
    if (in_addr1[i] == NA_INTEGER) {
      is_na[i] = true;
    } else if (in_v6[i]) {
      std::array<int32_t, 4> bytes = {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]};
      address_v6[i] = decode_ipv6(bytes);
      is_ipv6[i] = true;
    } else {
      address_v4[i] = decode_ipv4(in_addr1[i]);
    }
  }
}

List IpAddressVector::asList() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  IntegerVector out_addr1(vsize);
  IntegerVector out_addr2(vsize);
  IntegerVector out_addr3(vsize);
  IntegerVector out_addr4(vsize);
  LogicalVector out_v6(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      std::array<int32_t, 4> bytes = encode_ipv6(address_v6[i]);
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_v6[i] = true;
    } else {
      out_addr1[i] = encode_ipv4(address_v4[i]);
    }
  }

  return List::create(
    _["address1"] = out_addr1,
    _["address2"] = out_addr2,
    _["address3"] = out_addr3,
    _["address4"] = out_addr4,
    _["is_ipv6"] = out_v6
  );
}

CharacterVector IpAddressVector::asCharacterVector() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
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
