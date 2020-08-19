#ifndef __IPADDRESS_ADDRESS__
#define __IPADDRESS_ADDRESS__

#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <ipaddress/warn.h>
#include <ipaddress/encoding.h>


namespace ipaddress {

class IpAddressVector {
public:
  // data storage
  std::vector<asio::ip::address_v4> address_v4;
  std::vector<asio::ip::address_v6> address_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

  /*----------------*
   *  Constructors  *
   *----------------*/
  IpAddressVector(
    std::vector<asio::ip::address_v4> &in_address_v4,
    std::vector<asio::ip::address_v6> &in_address_v6,
    std::vector<bool> &in_is_ipv6,
    std::vector<bool> &in_is_na
  ) : address_v4(in_address_v4), address_v6(in_address_v6), is_ipv6(in_is_ipv6), is_na(in_is_na) {
    if (address_v4.size() != is_na.size() ||
        address_v6.size() != is_na.size() ||
        is_ipv6.size() != is_na.size()) {
      Rcpp::stop("Constituent vectors have unequal sizes"); // # nocov
    }
  }


  // Parse strings (dotted-decimal or dotted-hexidecimal format)
  IpAddressVector(Rcpp::CharacterVector input) {
    std::size_t vsize = input.size();

    // initialize vectors
    address_v4.assign(vsize, asio::ip::address_v4());
    address_v6.assign(vsize, asio::ip::address_v6());
    is_ipv6.assign(vsize, false);
    is_na.assign(vsize, false);

    asio::error_code ec;

    for (std::size_t i=0; i<vsize; ++i) {
      if (i % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }

      if (input[i] == NA_STRING) {
        is_na[i] = true;
      } else {
        address_v4[i] = asio::ip::make_address_v4(input[i], ec);
        if (ec) {
          address_v6[i] = asio::ip::make_address_v6(input[i], ec);
          if (ec) {
            is_na[i] = true;
            warnOnRow(i, Rcpp::as<std::string>(input[i]));
          } else {
            is_ipv6[i] = true;
          }
        }
      }
    }
  }


  // Decode from R class
  IpAddressVector(Rcpp::List input) {
    // extract data
    Rcpp::IntegerVector in_addr1 = input["address1"];
    Rcpp::IntegerVector in_addr2 = input["address2"];
    Rcpp::IntegerVector in_addr3 = input["address3"];
    Rcpp::IntegerVector in_addr4 = input["address4"];
    Rcpp::LogicalVector in_v6 = input["is_ipv6"];

    std::size_t vsize = in_v6.size();

    // initialize vectors
    address_v4.assign(vsize, asio::ip::address_v4());
    address_v6.assign(vsize, asio::ip::address_v6());
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
        address_v6[i] = decode_r<asio::ip::address_v6>(bytes);
        is_ipv6[i] = true;
      } else {
        r_address_v4_type bytes = {in_addr1[i]};
        address_v4[i] = decode_r<asio::ip::address_v4>(bytes);
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
      Rcpp::stop("Constituent vectors have unequal sizes"); // # nocov
    }

    Rcpp::List result = Rcpp::List::create(
      Rcpp::_["address1"] = out_addr1,
      Rcpp::_["address2"] = out_addr2,
      Rcpp::_["address3"] = out_addr3,
      Rcpp::_["address4"] = out_addr4,
      Rcpp::_["is_ipv6"] = out_v6
    );

    result.attr("class") = Rcpp::CharacterVector::create(
      "ip_address",
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
          char buffer[40];
          auto bytes = address_v6[i].to_bytes();
          sprintf(
            buffer,
            "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
            bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
            bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]
          );

          output[i] = std::string(buffer);
        } else {
          output[i] = address_v6[i].to_string();
        }
      } else {
        output[i] = address_v4[i].to_string();
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
