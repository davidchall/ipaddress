#include "IpNetworkVector.h"
#include "IpAddressVector.h"
#include "encoding.h"
#include "utils.h"


IpNetworkVector::IpNetworkVector(
  std::vector<asio::ip::network_v4> in_network_v4,
  std::vector<asio::ip::network_v6> in_network_v6,
  std::vector<bool> in_is_ipv6,
  std::vector<bool> in_is_na
) : network_v4(in_network_v4), network_v6(in_network_v6), is_ipv6(in_is_ipv6), is_na(in_is_na) { }

IpNetworkVector::IpNetworkVector(CharacterVector input, bool strict) {
  unsigned int vsize = input.size();

  // initialize vectors
  network_v4.assign(vsize, asio::ip::network_v4());
  network_v6.assign(vsize, asio::ip::network_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  asio::error_code ec;
  asio::ip::network_v4 tmp_v4;
  asio::ip::network_v6 tmp_v6;

  for (unsigned int i=0; i<vsize; ++i) {
    if (input[i] == NA_STRING) {
      is_na[i] = true;
    } else {

      // Parse IPv4
      tmp_v4 = asio::ip::make_network_v4(input[i], ec);
      if (!ec) {
        if (tmp_v4 == tmp_v4.canonical()) {
          network_v4[i] = tmp_v4;
        } else if (strict) {
          is_na[i] = true;
          warning("Invalid argument: " + input[i] + " has host bits set");
        } else {
          network_v4[i] = tmp_v4.canonical();
        }
      }

      // Parse IPv4
      else {
        tmp_v6 = asio::ip::make_network_v6(input[i], ec);
        if (!ec) {
          if (tmp_v6 == tmp_v6.canonical()) {
            network_v6[i] = tmp_v6;
            is_ipv6[i] = true;
          } else if (strict) {
            is_na[i] = true;
            warning("Invalid argument: " + input[i] + " has host bits set");
          } else {
            network_v6[i] = tmp_v6.canonical();
            is_ipv6[i] = true;
          }
        } else {
          is_na[i] = true;
          warning("Invalid argument: " + input[i]);
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
      address_v6_r_bytes_type bytes = {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]};
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
      address_v6_r_bytes_type bytes = encode_ipv6(network_v6[i].address());
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

IpAddressVector IpNetworkVector::netmask() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      continue;
    } else if (is_ipv6[i]) {
      out_address_v6[i] = netmask2<asio::ip::address_v6, 16>(network_v6[i].prefix_length());
    } else {
      out_address_v4[i] = netmask2<asio::ip::address_v4, 4>(network_v4[i].prefix_length());
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, is_ipv6, is_na);
}

IpAddressVector IpNetworkVector::hostmask() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      continue;
    } else if (is_ipv6[i]) {
      out_address_v6[i] = hostmask2<asio::ip::address_v6, 16>(network_v6[i].prefix_length());
    } else {
      out_address_v4[i] = hostmask2<asio::ip::address_v4, 4>(network_v4[i].prefix_length());
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, is_ipv6, is_na);
}
