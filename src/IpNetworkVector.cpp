#include "IpNetworkVector.h"
#include "IpAddressVector.h"
#include "encoding.h"
#include "masking.h"


/*----------------*
 *  Constructors  *
 *----------------*/

IpNetworkVector::IpNetworkVector(CharacterVector input, bool strict) {
  std::size_t vsize = input.size();

  // initialize vectors
  network_v4.assign(vsize, asio::ip::network_v4());
  network_v6.assign(vsize, asio::ip::network_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  asio::error_code ec;
  asio::ip::network_v4 tmp_v4;
  asio::ip::network_v6 tmp_v6;

  for (std::size_t i=0; i<vsize; ++i) {
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
          warnInvalidInput(i, as<std::string>(input[i]), "host bits set");
        } else {
          network_v4[i] = tmp_v4.canonical();
        }
      }

      // Parse IPv6
      else {
        tmp_v6 = asio::ip::make_network_v6(input[i], ec);
        if (!ec) {
          if (tmp_v6 == tmp_v6.canonical()) {
            network_v6[i] = tmp_v6;
            is_ipv6[i] = true;
          } else if (strict) {
            is_na[i] = true;
            warnInvalidInput(i, as<std::string>(input[i]), "host bits set");
          } else {
            network_v6[i] = tmp_v6.canonical();
            is_ipv6[i] = true;
          }
        } else {
          is_na[i] = true;
          warnInvalidInput(i, as<std::string>(input[i]));
        }
      }
    }
  }
}

IpNetworkVector::IpNetworkVector(List input) {
  // extract data
  IntegerVector in_addr1 = input["address1"];
  IntegerVector in_addr2 = input["address2"];
  IntegerVector in_addr3 = input["address3"];
  IntegerVector in_addr4 = input["address4"];
  IntegerVector in_pfx = input["prefix"];
  LogicalVector in_v6 = input["is_ipv6"];

  std::size_t vsize = in_v6.size();

  // initialize vectors
  network_v4.assign(vsize, asio::ip::network_v4());
  network_v6.assign(vsize, asio::ip::network_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (in_v6[i] == NA_LOGICAL) {
      is_na[i] = true;
    } else if (in_v6[i]) {
      r_address_v6_type bytes = {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]};
      asio::ip::address_v6 tmp_addr = decode<asio::ip::address_v6>(bytes);
      network_v6[i] = asio::ip::network_v6(tmp_addr, in_pfx[i]);
      is_ipv6[i] = true;
    } else {
      r_address_v4_type bytes = {in_addr1[i]};
      asio::ip::address_v4 tmp_addr = decode<asio::ip::address_v4>(bytes);
      network_v4[i] = asio::ip::network_v4(tmp_addr, in_pfx[i]);
    }
  }
}

IpNetworkVector::IpNetworkVector(IpAddressVector address, IntegerVector prefix_length, bool strict) {
  std::size_t vsize = address.is_na.size();

  // initialize vectors
  network_v4.assign(vsize, asio::ip::network_v4());
  network_v6.assign(vsize, asio::ip::network_v6());
  is_ipv6.assign(vsize, false);
  is_na.assign(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (address.is_na[i] || prefix_length[i] == NA_INTEGER) {
      is_na[i] = true;
    } else if (address.is_ipv6[i]) {

      // Construct IPv6
      if (prefix_length[i] < 0 || prefix_length[i] > 128) {
        is_na[i] = true;
        std::string cidr = address.address_v6[i].to_string() + "/" + std::to_string(prefix_length[i]);
        warnInvalidInput(i, cidr);
      } else {
        asio::ip::network_v6 tmp_v6(address.address_v6[i], prefix_length[i]);
        if (tmp_v6 == tmp_v6.canonical()) {
          network_v6[i] = tmp_v6;
          is_ipv6[i] = true;
        } else if (strict) {
          is_na[i] = true;
          warnInvalidInput(i, tmp_v6.to_string(), "host bits set");
        } else {
          network_v6[i] = tmp_v6.canonical();
          is_ipv6[i] = true;
        }
      }

    } else {

      // Construct IPv4
      if (prefix_length[i] < 0 || prefix_length[i] > 32) {
        is_na[i] = true;
        std::string cidr = address.address_v4[i].to_string() + "/" + std::to_string(prefix_length[i]);
        warnInvalidInput(i, cidr);
      } else {
        asio::ip::network_v4 tmp_v4(address.address_v4[i], prefix_length[i]);
        if (tmp_v4 == tmp_v4.canonical()) {
          network_v4[i] = tmp_v4;
        } else if (strict) {
          is_na[i] = true;
          warnInvalidInput(i, tmp_v4.to_string(), "host bits set");
        } else {
          network_v4[i] = tmp_v4.canonical();
        }
      }

    }
  }
}

void IpNetworkVector::warnInvalidInput(unsigned int index, const std::string &input, const std::string &reason) {
  // Indexes are 1-based in R
  std::string msg = "Invalid input in row " + std::to_string(index + 1) + ": " + input;
  if (!reason.empty()) {
    msg += " (" + reason + ")";
  }

  Rf_warningcall(R_NilValue, msg.c_str());
}


/*----------*
 *  Output  *
 *----------*/

List IpNetworkVector::encodeR() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  IntegerVector out_addr1(vsize);
  IntegerVector out_addr2(vsize);
  IntegerVector out_addr3(vsize);
  IntegerVector out_addr4(vsize);
  IntegerVector out_pfx(vsize);
  LogicalVector out_v6(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_pfx[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      r_address_v6_type bytes = encode<r_address_v6_type>(network_v6[i].address());
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_pfx[i] = network_v6[i].prefix_length();
      out_v6[i] = true;
    } else {
      r_address_v4_type bytes = encode<r_address_v4_type>(network_v4[i].address());
      out_addr1[i] = bytes[0];
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

CharacterVector IpNetworkVector::encodeStrings() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
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


/*-----------------------*
 *  Other functionality  *
 *-----------------------*/
IpAddressVector IpNetworkVector::broadcastAddress() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize);
  std::vector<bool> out_is_na(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      out_is_na[i] = true;
    } else if (is_ipv6[i]) {
      out_address_v6[i] = broadcast_address<asio::ip::address_v6>(network_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = broadcast_address<asio::ip::address_v4>(network_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}

IpAddressVector IpNetworkVector::hosts(bool exclude_unusable) const {
  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4;
  std::vector<asio::ip::address_v6> out_address_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  if (is_na.size() != 1) {
    // pass
  } else if (is_na[0]) {
    out_address_v4.resize(1);
    out_address_v6.resize(1);
    out_is_ipv6.resize(1);
    out_is_na.resize(1, true);
  } else if (exclude_unusable && is_ipv6[0] && network_v6[0].prefix_length() == 128) {
    // pass
  } else if (exclude_unusable && !is_ipv6[0] && network_v4[0].prefix_length() == 32) {
    // pass
  } else if (is_ipv6[0]) {
    asio::ip::address_v6_iterator ip_begin(network_v6[0].address());
    asio::ip::address_v6_iterator ip_end(broadcast_address<asio::ip::address_v6>(network_v6[0]));

    // IPv6 does not use final address as broadcast address
    ip_end++;

    // exclude subnet router anycast address
    if (exclude_unusable && (network_v6[0].prefix_length() != 127)) {
      ip_begin++;
    }

    std::copy(ip_begin, ip_end, std::back_inserter(out_address_v6));

    std::size_t vsize = out_address_v6.size();
    out_address_v4.resize(vsize);
    out_is_ipv6.resize(vsize, true);
    out_is_na.resize(vsize, false);
  } else {
    asio::ip::address_v4_iterator ip_begin(network_v4[0].address());
    asio::ip::address_v4_iterator ip_end(broadcast_address<asio::ip::address_v4>(network_v4[0]));

    // exclude network and broadcast addresses
    if (exclude_unusable && (network_v4[0].prefix_length() != 31)) {
      ip_begin++;
    } else {
      ip_end++;
    }

    std::copy(ip_begin, ip_end, std::back_inserter(out_address_v4));

    std::size_t vsize = out_address_v4.size();
    out_address_v6.resize(vsize);
    out_is_ipv6.resize(vsize, false);
    out_is_na.resize(vsize, false);
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}


/*----------------------*
 *  Reserved addresses  *
 * ---------------------*/
LogicalVector IpNetworkVector::isMulticast() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6 first = network_v6[i].address();
      asio::ip::address_v6 last = broadcast_address<asio::ip::address_v6>(network_v6[i]);
      output[i] = first.is_multicast() && last.is_multicast();
    } else {
      asio::ip::address_v4 first = network_v4[i].address();
      asio::ip::address_v4 last = broadcast_address<asio::ip::address_v4>(network_v4[i]);
      output[i] = first.is_multicast() && last.is_multicast();
    }
  }

  return output;
}

LogicalVector IpNetworkVector::isUnspecified() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6 first = network_v6[i].address();
      asio::ip::address_v6 last = broadcast_address<asio::ip::address_v6>(network_v6[i]);
      output[i] = first.is_unspecified() && last.is_unspecified();
    } else {
      asio::ip::address_v4 first = network_v4[i].address();
      asio::ip::address_v4 last = broadcast_address<asio::ip::address_v4>(network_v4[i]);
      output[i] = first.is_unspecified() && last.is_unspecified();
    }
  }

  return output;
}

LogicalVector IpNetworkVector::isLoopback() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6 first = network_v6[i].address();
      asio::ip::address_v6 last = broadcast_address<asio::ip::address_v6>(network_v6[i]);
      output[i] = first.is_loopback() && last.is_loopback();
    } else {
      asio::ip::address_v4 first = network_v4[i].address();
      asio::ip::address_v4 last = broadcast_address<asio::ip::address_v4>(network_v4[i]);
      output[i] = first.is_loopback() && last.is_loopback();
    }
  }

  return output;
}

LogicalVector IpNetworkVector::isLinkLocal() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6 first = network_v6[i].address();
      asio::ip::address_v6 last = broadcast_address<asio::ip::address_v6>(network_v6[i]);
      output[i] = first.is_link_local() && last.is_link_local();
    } else {
      asio::ip::address_v4 first = network_v4[i].address();
      asio::ip::address_v4 last = broadcast_address<asio::ip::address_v4>(network_v4[i]);
      // asio::ip::address_v4::is_link_local() doesn't exist
      output[i] = ((first.to_uint() & 0xFFFF0000) == 0xA9FE0000) &&
        ((last.to_uint() & 0xFFFF0000) == 0xA9FE0000);
    }
  }

  return output;
}

LogicalVector IpNetworkVector::isIPv4Mapped() const {
  std::size_t vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6 first = network_v6[i].address();
      asio::ip::address_v6 last = broadcast_address<asio::ip::address_v6>(network_v6[i]);
      output[i] = first.is_v4_mapped() && last.is_v4_mapped();
    } else {
      output[i] = false;
    }
  }

  return output;
}
