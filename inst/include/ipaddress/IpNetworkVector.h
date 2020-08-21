#ifndef __IPADDRESS_NETWORK__
#define __IPADDRESS_NETWORK__

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>
#include <ipaddress/IpAddressVector.h>
#include <ipaddress/warn.h>
#include <ipaddress/encoding.h>


namespace ipaddress {

class IpNetworkVector {
public:
  // data storage
  std::vector<asio::ip::network_v4> network_v4;
  std::vector<asio::ip::network_v6> network_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

  /*----------------*
   *  Constructors  *
   *----------------*/
  IpNetworkVector(
    std::vector<asio::ip::network_v4> in_network_v4,
    std::vector<asio::ip::network_v6> in_network_v6,
    std::vector<bool> in_is_ipv6,
    std::vector<bool> in_is_na
  ) : network_v4(in_network_v4), network_v6(in_network_v6), is_ipv6(in_is_ipv6), is_na(in_is_na) {
    if (network_v4.size() != is_na.size() ||
        network_v6.size() != is_na.size() ||
        is_ipv6.size() != is_na.size()) {
      Rcpp::stop("Constituent vectors have unequal sizes"); // # nocov
    }
  }


  // Parse strings (CIDR format)
  IpNetworkVector(Rcpp::CharacterVector input, bool strict, bool is_interface = false) {
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
      if (i % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }

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


  // Construct from address + prefix length
  IpNetworkVector(const IpAddressVector &address, Rcpp::IntegerVector prefix_length,
                  bool strict, bool is_interface) {
    std::size_t vsize = address.size();

    // initialize vectors
    network_v4.assign(vsize, asio::ip::network_v4());
    network_v6.assign(vsize, asio::ip::network_v6());
    is_ipv6.assign(vsize, false);
    is_na.assign(vsize, false);

    for (std::size_t i=0; i<vsize; ++i) {
      if (i % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }

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

  // Decode from R class
  IpNetworkVector(Rcpp::List input) {
    // extract data
    Rcpp::IntegerVector in_addr1 = input["address1"];
    Rcpp::IntegerVector in_addr2 = input["address2"];
    Rcpp::IntegerVector in_addr3 = input["address3"];
    Rcpp::IntegerVector in_addr4 = input["address4"];
    Rcpp::IntegerVector in_pfx = input["prefix"];
    Rcpp::LogicalVector in_v6 = input["is_ipv6"];

    std::size_t vsize = in_v6.size();

    // initialize vectors
    network_v4.assign(vsize, asio::ip::network_v4());
    network_v6.assign(vsize, asio::ip::network_v6());
    is_ipv6.assign(vsize, false);
    is_na.assign(vsize, false);

    for (std::size_t i=0; i<vsize; ++i) {
      if (i % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }

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


  /*----------*
   *  Output  *
   *----------*/
  // Encode to R class
  Rcpp::List encodeR() const {
    std::size_t vsize = size();

    // initialize vectors
    Rcpp::IntegerVector out_addr1(vsize);
    Rcpp::IntegerVector out_addr2(vsize);
    Rcpp::IntegerVector out_addr3(vsize);
    Rcpp::IntegerVector out_addr4(vsize);
    Rcpp::IntegerVector out_pfx(vsize);
    Rcpp::LogicalVector out_v6(vsize);

    for (std::size_t i=0; i<vsize; ++i) {
      if (i % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }

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
      Rcpp::stop("Constituent vectors have unequal sizes"); // # nocov
    }

    Rcpp::List result = Rcpp::List::create(
      Rcpp::_["address1"] = out_addr1,
      Rcpp::_["address2"] = out_addr2,
      Rcpp::_["address3"] = out_addr3,
      Rcpp::_["address4"] = out_addr4,
      Rcpp::_["prefix"] = out_pfx,
      Rcpp::_["is_ipv6"] = out_v6
    );

    result.attr("class") = Rcpp::CharacterVector::create(
      "ip_network",
      "vctrs_rcrd",
      "vctrs_vctr"
    );

    return result;
  }


  // Encode to strings
  Rcpp::CharacterVector encodeStrings(bool exploded = false) const {
    std::size_t vsize = size();

    // initialize vectors
    Rcpp::CharacterVector output(vsize);

    for (std::size_t i=0; i<vsize; ++i) {
      if (i % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }

      if (is_na[i]) {
        output[i] = NA_STRING;
      } else if (is_ipv6[i]) {
        if (exploded) {
          char buffer[50];
          auto bytes = network_v6[i].address().to_bytes();
          sprintf(
            buffer,
            "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x/%u",
            bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
            bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15],
            network_v6[i].prefix_length()
          );

          output[i] = std::string(buffer);
        } else {
          output[i] = network_v6[i].to_string();
        }
      } else {
        output[i] = network_v4[i].to_string();
      }
    }

    return output;
  }

  // size of vector
  std::size_t size() const {
    return is_na.size();
  }
};

}

#endif
