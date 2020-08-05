#include "IpNetworkVector.h"
#include "IpAddressVector.h"
#include "encoding.h"
#include "masking.h"
#include "iterative.h"
#include "sample.h"
#include "utils.h"

using namespace Rcpp;


/*----------------*
 *  Constructors  *
 *----------------*/

IpNetworkVector::IpNetworkVector(CharacterVector input,
                                 bool strict, bool is_interface) {
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
        if (is_interface) {
          network_v4[i] = tmp_v4;
        } else if (tmp_v4 == tmp_v4.canonical()) {
          network_v4[i] = tmp_v4;
        } else if (strict) {
          is_na[i] = true;
          warnOnRow(i, Rcpp::as<std::string>(input[i]), "host bits set");
        } else {
          network_v4[i] = tmp_v4.canonical();
        }
      }

      // Parse IPv6
      else {
        tmp_v6 = asio::ip::make_network_v6(input[i], ec);
        if (!ec) {
          if (is_interface) {
            network_v6[i] = tmp_v6;
            is_ipv6[i] = true;
          } else if (tmp_v6 == tmp_v6.canonical()) {
            network_v6[i] = tmp_v6;
            is_ipv6[i] = true;
          } else if (strict) {
            is_na[i] = true;
            warnOnRow(i, Rcpp::as<std::string>(input[i]), "host bits set");
          } else {
            network_v6[i] = tmp_v6.canonical();
            is_ipv6[i] = true;
          }
        } else {
          is_na[i] = true;
          warnOnRow(i, Rcpp::as<std::string>(input[i]));
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
      asio::ip::address_v6 tmp_addr = decode_r<asio::ip::address_v6>(bytes);
      network_v6[i] = asio::ip::network_v6(tmp_addr, in_pfx[i]);
      is_ipv6[i] = true;
    } else {
      r_address_v4_type bytes = {in_addr1[i]};
      asio::ip::address_v4 tmp_addr = decode_r<asio::ip::address_v4>(bytes);
      network_v4[i] = asio::ip::network_v4(tmp_addr, in_pfx[i]);
    }
  }
}

IpNetworkVector::IpNetworkVector(IpAddressVector address, IntegerVector prefix_length,
                                 bool strict, bool is_interface) {
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
        warnOnRow(i, cidr, "prefix length out-of-bounds");
      } else {
        asio::ip::network_v6 tmp_v6(address.address_v6[i], prefix_length[i]);
        if (is_interface) {
          network_v6[i] = tmp_v6;
          is_ipv6[i] = true;
        } else if (tmp_v6 == tmp_v6.canonical()) {
          network_v6[i] = tmp_v6;
          is_ipv6[i] = true;
        } else if (strict) {
          is_na[i] = true;
          warnOnRow(i, tmp_v6.to_string(), "host bits set");
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
        warnOnRow(i, cidr, "prefix length out-of-bounds");
      } else {
        asio::ip::network_v4 tmp_v4(address.address_v4[i], prefix_length[i]);
        if (is_interface) {
          network_v4[i] = tmp_v4;
        } else if (tmp_v4 == tmp_v4.canonical()) {
          network_v4[i] = tmp_v4;
        } else if (strict) {
          is_na[i] = true;
          warnOnRow(i, tmp_v4.to_string(), "host bits set");
        } else {
          network_v4[i] = tmp_v4.canonical();
        }
      }

    }
  }
}

IpNetworkVector IpNetworkVector::smallestCommonNetwork(const IpAddressVector &address1, const IpAddressVector &address2) {
  std::size_t vsize = address1.is_na.size();

  if (address2.is_na.size() != vsize) {
    stop("Addresses must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::network_v4> network_v4(vsize);
  std::vector<asio::ip::network_v6> network_v6(vsize);
  std::vector<bool> is_ipv6(vsize, false);
  std::vector<bool> is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (address1.is_na[i] || address2.is_na[i]) {
      is_na[i] = true;
    } else if (address1.is_ipv6[i] != address2.is_ipv6[i]) {
      is_na[i] = true;
    } else if (address1.is_ipv6[i]) {
      network_v6[i] = common_network<asio::ip::network_v6>(address1.address_v6[i], address2.address_v6[i]);
      is_ipv6[i] = true;
    } else {
      network_v4[i] = common_network<asio::ip::network_v4>(address1.address_v4[i], address2.address_v4[i]);
    }
  }

  return IpNetworkVector(network_v4, network_v6, is_ipv6, is_na);
}

List IpNetworkVector::summarizeAddressRange(const IpAddressVector &address1, const IpAddressVector &address2) {
  std::size_t vsize = address1.is_na.size();
  List output(vsize);

  if (address2.is_na.size() != vsize) {
    stop("Addresses must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    // initialize vectors
    std::vector<asio::ip::network_v4> network_v4;
    std::vector<asio::ip::network_v6> network_v6;
    std::vector<bool> is_ipv6;
    std::vector<bool> is_na;

    if (address1.is_na[i] || address2.is_na[i]) {
      network_v4.resize(1);
      network_v6.resize(1);
      is_ipv6.resize(1);
      is_na.resize(1, true);
    } else if (address1.is_ipv6[i] != address2.is_ipv6[i]) {
      network_v4.resize(1);
      network_v6.resize(1);
      is_ipv6.resize(1);
      is_na.resize(1, true);
    } else if (address1.is_ipv6[i]) {
      network_v6 = summarize_address_range<asio::ip::network_v6>(address1.address_v6[i], address2.address_v6[i]);

      std::size_t vsize = network_v6.size();
      network_v4.resize(vsize);
      is_ipv6.resize(vsize, true);
      is_na.resize(vsize);
    } else {
      network_v4 = summarize_address_range<asio::ip::network_v4>(address1.address_v4[i], address2.address_v4[i]);

      std::size_t vsize = network_v4.size();
      network_v6.resize(vsize);
      is_ipv6.resize(vsize);
      is_na.resize(vsize);
    }

    output[i] = IpNetworkVector(network_v4, network_v6, is_ipv6, is_na).encodeR();
  }

  return output;
}

void IpNetworkVector::warnOnRow(unsigned int index, const std::string &input, const std::string &reason) {
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
      r_address_v6_type bytes = encode_r<r_address_v6_type>(network_v6[i].address());
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_pfx[i] = network_v6[i].prefix_length();
      out_v6[i] = true;
    } else {
      r_address_v4_type bytes = encode_r<r_address_v4_type>(network_v4[i].address());
      out_addr1[i] = bytes[0];
      out_pfx[i] = network_v4[i].prefix_length();
    }
  }

  if (out_addr1.size() != out_v6.size() ||
      out_addr2.size() != out_v6.size() ||
      out_addr3.size() != out_v6.size() ||
      out_addr4.size() != out_v6.size() ||
      out_pfx.size() != out_v6.size()) {
    stop("Constituent vectors have unequal sizes"); // # nocov
  }

  List result = List::create(
    _["address1"] = out_addr1,
    _["address2"] = out_addr2,
    _["address3"] = out_addr3,
    _["address4"] = out_addr4,
    _["prefix"] = out_pfx,
    _["is_ipv6"] = out_v6
  );

  result.attr("class") = CharacterVector::create(
    "ip_network",
    "vctrs_rcrd",
    "vctrs_vctr"
  );

  return result;
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

IpNetworkVector IpNetworkVector::subnets(IntegerVector new_prefix) const {
  // initialize vectors
  std::vector<asio::ip::network_v4> out_network_v4;
  std::vector<asio::ip::network_v6> out_network_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  if (is_na.size() != 1) {
    // pass
  } else if (is_na[0] || new_prefix[0] == NA_INTEGER) {
    out_network_v4.resize(1);
    out_network_v6.resize(1);
    out_is_ipv6.resize(1);
    out_is_na.resize(1, true);
  } else if (is_ipv6[0]) {
    out_network_v6 = calculate_subnets<asio::ip::address_v6>(network_v6[0], new_prefix[0]);

    std::size_t vsize = out_network_v6.size();
    out_network_v4.resize(vsize);
    out_is_ipv6.resize(vsize, true);
    out_is_na.resize(vsize);
  } else {
    out_network_v4 = calculate_subnets<asio::ip::address_v4>(network_v4[0], new_prefix[0]);

    std::size_t vsize = out_network_v4.size();
    out_network_v6.resize(vsize);
    out_is_ipv6.resize(vsize);
    out_is_na.resize(vsize);
  }

  return IpNetworkVector(out_network_v4, out_network_v6, out_is_ipv6, out_is_na);
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
    out_address_v6 = calculate_hosts<asio::ip::address_v6>(network_v6[0], exclude_unusable, true);

    std::size_t vsize = out_address_v6.size();
    out_address_v4.resize(vsize);
    out_is_ipv6.resize(vsize, true);
    out_is_na.resize(vsize, false);
  } else {
    out_address_v4 = calculate_hosts<asio::ip::address_v4>(network_v4[0], exclude_unusable, false);

    std::size_t vsize = out_address_v4.size();
    out_address_v6.resize(vsize);
    out_is_ipv6.resize(vsize, false);
    out_is_na.resize(vsize, false);
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}

IpAddressVector IpNetworkVector::sample(unsigned int size) const {
  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4;
  std::vector<asio::ip::address_v6> out_address_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  if (is_na.size() != 1 || is_na[0]) {
    // pass
  } else if (is_ipv6[0]) {
    out_address_v6 = sample_network<asio::ip::address_v6>(network_v6[0], size);
    out_address_v4.resize(size);
    out_is_ipv6.resize(size, true);
    out_is_na.resize(size, false);
  } else {
    out_address_v4 = sample_network<asio::ip::address_v4>(network_v4[0], size);
    out_address_v6.resize(size);
    out_is_ipv6.resize(size, false);
    out_is_na.resize(size, false);
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}


/*----------------------*
 *  Reserved addresses  *
 * ---------------------*/
LogicalVector IpNetworkVector::isMulticast() const {
  return checkCondition(
    [](const asio::ip::address_v4 &x) { return x.is_multicast(); },
    [](const asio::ip::address_v6 &x) { return x.is_multicast(); }
  );
}

LogicalVector IpNetworkVector::isUnspecified() const {
  return checkCondition(
    [](const asio::ip::address_v4 &x) { return x.is_unspecified(); },
    [](const asio::ip::address_v6 &x) { return x.is_unspecified(); }
  );
}

LogicalVector IpNetworkVector::isLoopback() const {
  return checkCondition(
    [](const asio::ip::address_v4 &x) { return x.is_loopback(); },
    [](const asio::ip::address_v6 &x) { return x.is_loopback(); }
  );
}

LogicalVector IpNetworkVector::isLinkLocal() const {
  return checkCondition(
    [](const asio::ip::address_v4 &x) { return (x.to_uint() & 0xFFFF0000) == 0xA9FE0000; },
    [](const asio::ip::address_v6 &x) { return x.is_link_local(); }
  );
}

LogicalVector IpNetworkVector::isIPv4Mapped() const {
  return checkCondition(
    [](const asio::ip::address_v4 &x) { return false; },
    [](const asio::ip::address_v6 &x) { return x.is_v4_mapped(); }
  );
}

LogicalVector IpNetworkVector::is6to4() const {
  return checkCondition(
    [](const asio::ip::address_v4 &x) { return false; },
    [](const asio::ip::address_v6 &x) { return is_6to4(x); }
  );
}

LogicalVector IpNetworkVector::isTeredo() const {
  return checkCondition(
    [](const asio::ip::address_v4 &x) { return false; },
    [](const asio::ip::address_v6 &x) { return is_teredo(x); }
  );
}


/*----------------*
 *  Common tasks  *
 * ---------------*/
LogicalVector IpNetworkVector::checkCondition(
    const std::function<bool(const asio::ip::address_v4&)>& condition_v4,
    const std::function<bool(const asio::ip::address_v6&)>& condition_v6
) const {
  std::size_t vsize = is_na.size();
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (is_ipv6[i]) {
      asio::ip::address_v6 first = network_v6[i].address();
      asio::ip::address_v6 last = broadcast_address<asio::ip::address_v6>(network_v6[i]);
      output[i] = condition_v6(first) && condition_v6(last);
    } else {
      asio::ip::address_v4 first = network_v4[i].address();
      asio::ip::address_v4 last = broadcast_address<asio::ip::address_v4>(network_v4[i]);
      output[i] = condition_v4(first) && condition_v4(last);
    }
  }

  return output;
}
