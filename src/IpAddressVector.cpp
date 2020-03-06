#include "IpAddressVector.h"
#include "IpNetworkVector.h"
#include "encoding.h"
#include "masking.h"


/*----------------*
 *  Constructors  *
 *----------------*/

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
          warnInvalidInput(i, as<std::string>(input[i]));
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
    if (in_v6[i] == NA_LOGICAL) {
      is_na[i] = true;
    } else if (in_v6[i]) {
      r_address_v6_type bytes = {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]};
      address_v6[i] = decode<asio::ip::address_v6>(bytes);
      is_ipv6[i] = true;
    } else {
      r_address_v4_type bytes = {in_addr1[i]};
      address_v4[i] = decode<asio::ip::address_v4>(bytes);
    }
  }
}

IpAddressVector IpAddressVector::createNetmask(IntegerVector in_pfx, LogicalVector in_v6) {
  unsigned int vsize = in_v6.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> address_v4(vsize);
  std::vector<asio::ip::address_v6> address_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  for (unsigned int i=0; i<vsize; ++i) {
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
  unsigned int vsize = in_v6.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> address_v4(vsize);
  std::vector<asio::ip::address_v6> address_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  for (unsigned int i=0; i<vsize; ++i) {
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
  std::string msg = "Invalid input in row " + std::to_string(index + 1) + ": " + input;
  if (!reason.empty()) {
    msg += " (" + reason + ")";
  }

  Rf_warningcall(R_NilValue, msg.c_str());
}


/*----------*
 *  Output  *
 *----------*/

List IpAddressVector::encodeR() const {
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
      r_address_v6_type bytes = encode<r_address_v6_type>(address_v6[i]);
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_v6[i] = true;
    } else {
      r_address_v4_type bytes = encode<r_address_v4_type>(address_v4[i]);
      out_addr1[i] = bytes[0];
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

CharacterVector IpAddressVector::encodeStrings() const {
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

DataFrame IpAddressVector::encodeComparable() const {
  unsigned int vsize = is_na.size();

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

  for (unsigned int i=0; i<vsize; ++i) {
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
      r_address_v6_type bytes = encode<r_address_v6_type>(address_v6[i]);
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
      r_address_v4_type bytes = encode<r_address_v4_type>(address_v4[i]);
      out_addr1[i] = (bytes[0] & left_mask) >> 16;
      out_addr2[i] = (bytes[0] & right_mask);
    }
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

List IpAddressVector::packed() const {
  unsigned int vsize = is_na.size();

  List output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      RawVector raw(0);
      output[i] = raw;
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


/*---------------------*
 *  Bitwise operators  *
 *---------------------*/
IpAddressVector IpAddressVector::operator&(const IpAddressVector &rhs) const {
  unsigned int vsize = is_na.size();

  if (rhs.is_na.size() != vsize) {
    stop("Addresses must have same length");
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (unsigned int i=0; i<vsize; ++i) {
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
  unsigned int vsize = is_na.size();

  if (rhs.is_na.size() != vsize) {
    stop("Addresses must have same length");
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (unsigned int i=0; i<vsize; ++i) {
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

IpAddressVector IpAddressVector::operator~() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (unsigned int i=0; i<vsize; ++i) {
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


/*-----------------------*
 *  Other functionality  *
 *-----------------------*/

LogicalVector IpAddressVector::isWithin(const IpNetworkVector &network) const {
  unsigned int vsize = is_na.size();

  if (network.is_na.size() != vsize) {
    stop("Address and network must have same length");
  }

  // initialize vectors
  LogicalVector output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
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
  unsigned int address_size = is_na.size();
  unsigned int network_size = network.is_na.size();

  // initialize vectors
  LogicalVector output(address_size);

  for (unsigned int i_addr=0; i_addr<address_size; ++i_addr) {
    if (is_na[i_addr]) {
      output[i_addr] = NA_LOGICAL;
    } else {
      output[i_addr] = false;
      for (unsigned int i_netw=0; i_netw<network_size; ++i_netw) {
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
  unsigned int vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      output[i] = address_v6[i].is_multicast();
    } else {
      output[i] = address_v4[i].is_multicast();
    }
  }

  return output;
}

LogicalVector IpAddressVector::isUnspecified() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      output[i] = address_v6[i].is_unspecified();
    } else {
      output[i] = address_v4[i].is_unspecified();
    }
  }

  return output;
}

LogicalVector IpAddressVector::isLoopback() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      output[i] = address_v6[i].is_loopback();
    } else {
      output[i] = address_v4[i].is_loopback();
    }
  }

  return output;
}

LogicalVector IpAddressVector::isLinkLocal() const {
  unsigned int vsize = is_na.size();

  // initialize vectors
  LogicalVector output(vsize);

  for (unsigned int i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      output[i] = address_v6[i].is_link_local();
    } else {
      // asio::ip::address_v4::is_link_local() doesn't exist
      output[i] = (address_v4[i].to_uint() & 0xFFFF0000) == 0xA9FE0000;
    }
  }

  return output;
}
