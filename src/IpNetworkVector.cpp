#include "IpNetworkVector.h"
#include "encoding.h"

IpNetworkVector::IpNetworkVector(CharacterVector input) {
  unsigned int vsize = input.size();

  // initialize vectors
  network_v4.assign(vsize, asio::ip::network_v4());
  network_v6.assign(vsize, asio::ip::network_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  asio::error_code ec;

  for (unsigned int i=0; i<vsize; ++i) {
    if (input[i] == NA_STRING) {
      is_na[i] = true;
    } else {
      network_v4[i] = asio::ip::make_network_v4(input[i], ec);
      if (ec) {
        network_v6[i] = asio::ip::make_network_v6(input[i], ec);
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

IpNetworkVector::IpNetworkVector(List input) {
  // extract data
  IntegerVector in_addr1 = as<IntegerVector>(input["address1"]);
  IntegerVector in_addr2 = as<IntegerVector>(input["address2"]);
  IntegerVector in_addr3 = as<IntegerVector>(input["address3"]);
  IntegerVector in_addr4 = as<IntegerVector>(input["address4"]);
  IntegerVector in_pfx = as<IntegerVector>(input["prefix"]);
  LogicalVector in_v6 = as<LogicalVector>(input["is_ipv6"]);

  unsigned int vsize = in_v6.size();

  // initialize vectors
  network_v4.assign(vsize, asio::ip::network_v4());
  network_v6.assign(vsize, asio::ip::network_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  for (unsigned int i=0; i<vsize; ++i) {
    if (in_addr1[i] == NA_INTEGER) {
      is_na[i] = true;
    } else if (in_v6[i]) {
      std::array<int32_t, 4> bytes = {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]};
      asio::ip::address_v6 tmp_addr = decode_ipv6(bytes);
      network_v6[i] = asio::ip::network_v6(tmp_addr, in_pfx[i]);
      is_ipv6[i] = true;
    } else {
      asio::ip::address_v4 tmp_addr = decode_ipv4(in_addr1[i]);
      network_v4[i] = asio::ip::network_v4(tmp_addr, in_pfx[i]);
    }
  }
}

List IpNetworkVector::asList() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  IntegerVector out_addr1(vsize);
  IntegerVector out_addr2(vsize);
  IntegerVector out_addr3(vsize);
  IntegerVector out_addr4(vsize);
  IntegerVector out_pfx(vsize);
  LogicalVector out_v6(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_pfx[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      std::array<int32_t, 4> bytes = encode_ipv6(network_v6[i].address());
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_pfx[i] = network_v6[i].prefix_length();
      out_v6[i] = true;
    } else {
      out_addr1[i] = encode_ipv4(network_v4[i].address());
      out_pfx[i] = network_v4[i].prefix_length();
    }
  }

  return List::create(
    _["address1"] = out_addr1,
    _["address2"] = out_addr2,
    _["address3"] = out_addr3,
    _["address4"] = out_addr4,
    _["prefix"] = out_pfx,
    _["is_ipv6"] = out_v6
  );
}

CharacterVector IpNetworkVector::asCharacterVector() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_STRING;
    } else if (is_ipv6[i]) {
      output[i] = network_v6[i].to_string();
    } else {
      output[i] = network_v4[i].to_string();
    }
  }

  return output;
}
