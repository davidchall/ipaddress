#ifndef __IPADDRESS_ENCODING__
#define __IPADDRESS_ENCODING__

#include <vector>
#include <Rcpp.h>
#include <ipaddress/IpAddress.h>
#include <ipaddress/IpNetwork.h>


namespace ipaddress {

typedef std::array<int32_t, 1> r_type_v4;
typedef std::array<int32_t, 4> r_type_v6;


template<class CBytes, class RBytes>
CBytes decode_address(const RBytes &input) {
  CBytes output;
  std::memcpy(output.begin(), input.begin(), output.size());
  return output;
}


template<class RBytes>
RBytes encode_address(const IpAddress &input) {
  RBytes output;
  std::memcpy(output.begin(), input.begin(), input.n_bytes());
  return output;
}


inline std::vector<IpAddress> decode_addresses(Rcpp::List input) {
  if (!input.inherits("ip_address")) {
    Rcpp::stop("Attempted to decode ip_address vector from invalid R object."); // # nocov
  }

  // extract data
  Rcpp::IntegerVector in_addr1 = input["address1"];
  Rcpp::IntegerVector in_addr2 = input["address2"];
  Rcpp::IntegerVector in_addr3 = input["address3"];
  Rcpp::IntegerVector in_addr4 = input["address4"];
  Rcpp::LogicalVector in_v6 = input["is_ipv6"];

  // initialize vectors
  std::size_t vsize = in_v6.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    if (in_v6[i] == NA_LOGICAL) {
      output[i] = IpAddress::make_na();
    } else if (in_v6[i]) {
      r_type_v6 r_bytes{ {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]} };

      output[i] = IpAddress::make_ipv6(decode_address<IpAddress::bytes_type_v6>(r_bytes));
    } else {
      r_type_v4 r_bytes{ {in_addr1[i]} };

      output[i] = IpAddress::make_ipv4(decode_address<IpAddress::bytes_type_v4>(r_bytes));
    }
  }

  return output;
}


inline std::vector<IpNetwork> decode_networks(Rcpp::List input) {
  if (!(input.inherits("ip_network") || input.inherits("ip_interface"))) {
    Rcpp::stop("Attempted to decode ip_network or ip_interface vector from invalid R object."); // # nocov
  }

  // extract data
  Rcpp::IntegerVector in_addr1 = input["address1"];
  Rcpp::IntegerVector in_addr2 = input["address2"];
  Rcpp::IntegerVector in_addr3 = input["address3"];
  Rcpp::IntegerVector in_addr4 = input["address4"];
  Rcpp::IntegerVector in_pfx = input["prefix"];
  Rcpp::LogicalVector in_v6 = input["is_ipv6"];

  // initialize vectors
  std::size_t vsize = in_v6.size();
  std::vector<IpNetwork> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    if (in_v6[i] == NA_LOGICAL) {
      output[i] = IpNetwork::make_na();
    } else if (in_v6[i]) {
      r_type_v6 r_bytes{ {in_addr1[i], in_addr2[i], in_addr3[i], in_addr4[i]} };

      output[i] = IpNetwork::make_ipv6(decode_address<IpAddress::bytes_type_v6>(r_bytes), in_pfx[i]);
    } else {
      r_type_v4 r_bytes{ {in_addr1[i]} };

      output[i] = IpNetwork::make_ipv4(decode_address<IpAddress::bytes_type_v4>(r_bytes), in_pfx[i]);
    }
  }

  return output;
}


inline Rcpp::List encode_addresses(const std::vector<IpAddress> &input) {
  // initialize vectors
  std::size_t vsize = input.size();
  Rcpp::IntegerVector out_addr1(vsize);
  Rcpp::IntegerVector out_addr2(vsize);
  Rcpp::IntegerVector out_addr3(vsize);
  Rcpp::IntegerVector out_addr4(vsize);
  Rcpp::LogicalVector out_v6(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    if (input[i].is_na()) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (input[i].is_ipv6()) {
      r_type_v6 bytes = encode_address<r_type_v6>(input[i]);
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_v6[i] = true;
    } else {
      r_type_v4 bytes = encode_address<r_type_v4>(input[i]);
      out_addr1[i] = bytes[0];
    }
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


inline Rcpp::List encode_networks(const std::vector<IpNetwork> &input) {
  // initialize vectors
  std::size_t vsize = input.size();
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

    if (input[i].is_na()) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_pfx[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (input[i].is_ipv6()) {
      r_type_v6 bytes = encode_address<r_type_v6>(input[i].address());
      out_addr1[i] = bytes[0];
      out_addr2[i] = bytes[1];
      out_addr3[i] = bytes[2];
      out_addr4[i] = bytes[3];
      out_pfx[i] = input[i].prefix_length();
      out_v6[i] = true;
    } else {
      r_type_v4 bytes = encode_address<r_type_v4>(input[i].address());
      out_addr1[i] = bytes[0];
      out_pfx[i] = input[i].prefix_length();
    }
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

}

#endif
