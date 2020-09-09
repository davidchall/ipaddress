#include <Rcpp.h>
#include <asio/ip/network_v6.hpp>
#include <asio/ip/network_v4.hpp>
#include <ipaddress.h>
#include <ipaddress/to_string.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


/*-------------*
 *  Addresses  *
 * ------------*/
// [[Rcpp::export]]
List wrap_parse_address(CharacterVector input) {
  // initialize vectors
  std::size_t vsize = input.size();
  std::vector<IpAddress> output(vsize);

  asio::error_code ec;
  asio::ip::address_v4 tmp_v4;
  asio::ip::address_v6 tmp_v6;

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == NA_STRING) {
      output[i] = IpAddress::make_na();
    } else {
      tmp_v4 = asio::ip::make_address_v4(input[i], ec);
      if (!ec) {
        output[i] = IpAddress::make_ipv4(tmp_v4.to_bytes());
      } else {
        tmp_v6 = asio::ip::make_address_v6(input[i], ec);
        if (!ec) {
          output[i] = IpAddress::make_ipv6(tmp_v6.to_bytes());
        } else {
          output[i] = IpAddress::make_na();
          warnOnRow(i, as<std::string>(input[i]));
        }
      }
    }
  }

  return encode_addresses(output);
}

// [[Rcpp::export]]
CharacterVector wrap_print_address(List x, bool exploded = false) {
  std::vector<IpAddress> address = decode_addresses(x);

  // initialize vectors
  std::size_t vsize = address.size();
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = NA_STRING;
    } else if (exploded && address[i].is_ipv6()) {
      char buffer[40];
      auto bytes = address[i].bytes_v6();
      sprintf(
        buffer,
        "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x",
        bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
        bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]
      );

      output[i] = std::string(buffer);
    } else {
      output[i] = to_string(address[i]);
    }
  }

  return output;
}

// [[Rcpp::export]]
DataFrame wrap_compare_address(List address_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);

  // initialize vectors
  std::size_t vsize = address.size();
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
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      out_addr1[i] = NA_INTEGER;
      out_addr2[i] = NA_INTEGER;
      out_addr3[i] = NA_INTEGER;
      out_addr4[i] = NA_INTEGER;
      out_addr5[i] = NA_INTEGER;
      out_addr6[i] = NA_INTEGER;
      out_addr7[i] = NA_INTEGER;
      out_addr8[i] = NA_INTEGER;
      out_v6[i] = NA_LOGICAL;
    } else if (address[i].is_ipv6()) {
      r_type_v6 bytes = encode_address<r_type_v6>(address[i]);
      out_addr1[i] = (ntohl(bytes[0]) & left_mask) >> 16;
      out_addr2[i] = (ntohl(bytes[0]) & right_mask);
      out_addr3[i] = (ntohl(bytes[1]) & left_mask) >> 16;
      out_addr4[i] = (ntohl(bytes[1]) & right_mask);
      out_addr5[i] = (ntohl(bytes[2]) & left_mask) >> 16;
      out_addr6[i] = (ntohl(bytes[2]) & right_mask);
      out_addr7[i] = (ntohl(bytes[3]) & left_mask) >> 16;
      out_addr8[i] = (ntohl(bytes[3]) & right_mask);
      out_v6[i] = true;
    } else {
      r_type_v4 bytes = encode_address<r_type_v4>(address[i]);
      out_addr1[i] = (ntohl(bytes[0]) & left_mask) >> 16;
      out_addr2[i] = (ntohl(bytes[0]) & right_mask);
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


/*------------*
 *  Networks  *
 * -----------*/
// [[Rcpp::export]]
List wrap_parse_network(CharacterVector input, bool strict, bool is_interface) {
  // initialize vectors
  std::size_t vsize = input.size();
  std::vector<IpNetwork> output(vsize);

  asio::error_code ec;
  asio::ip::network_v4 tmp_v4;
  asio::ip::network_v6 tmp_v6;

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i] == NA_STRING) {
      output[i] = IpNetwork::make_na();
    } else {

      // Parse IPv4
      tmp_v4 = asio::ip::make_network_v4(input[i], ec);
      if (!ec) {
        if (is_interface || tmp_v4 == tmp_v4.canonical()) {
          output[i] = IpNetwork::make_ipv4(tmp_v4.address().to_bytes(), tmp_v4.prefix_length());
        } else if (strict) {
          output[i] = IpNetwork::make_na();
          warnOnRow(i, as<std::string>(input[i]), "host bits set");
        } else {
          tmp_v4 = tmp_v4.canonical();
          output[i] = IpNetwork::make_ipv4(tmp_v4.address().to_bytes(), tmp_v4.prefix_length());
        }
      }

      // Parse IPv6
      else {
        tmp_v6 = asio::ip::make_network_v6(input[i], ec);
        if (!ec) {
          if (is_interface || tmp_v6 == tmp_v6.canonical()) {
            output[i] = IpNetwork::make_ipv6(tmp_v6.address().to_bytes(), tmp_v6.prefix_length());
          } else if (strict) {
            output[i] = IpNetwork::make_na();
            warnOnRow(i, as<std::string>(input[i]), "host bits set");
          } else {
            tmp_v6 = tmp_v6.canonical();
            output[i] = IpNetwork::make_ipv6(tmp_v6.address().to_bytes(), tmp_v6.prefix_length());
          }
        } else {
          output[i] = IpNetwork::make_na();
          warnOnRow(i, as<std::string>(input[i]));
        }
      }
    }
  }

  return encode_networks(output);
}

// [[Rcpp::export]]
List wrap_construct_network_from_address(List address_r, IntegerVector prefix_length, bool strict, bool is_interface) {
  std::vector<IpAddress> address = decode_addresses(address_r);

  // initialize vectors
  std::size_t vsize = address.size();
  std::vector<IpNetwork> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na() || prefix_length[i] == NA_INTEGER) {
      output[i] = IpNetwork::make_na();
    } else if (address[i].is_ipv6()) {

      // Construct IPv6
      if (prefix_length[i] < 0 || prefix_length[i] > 128) {
        output[i] = IpNetwork::make_na();
        asio::ip::address_v6 asio_address(address[i].bytes_v6());
        std::string cidr = asio_address.to_string() + "/" + std::to_string(prefix_length[i]);
        warnOnRow(i, cidr, "prefix length out-of-bounds");
      } else {
        asio::ip::network_v6 tmp_v6(asio::ip::address_v6(address[i].bytes_v6()), prefix_length[i]);
        if (is_interface || tmp_v6 == tmp_v6.canonical()) {
          output[i] = IpNetwork::make_ipv6(tmp_v6.address().to_bytes(), tmp_v6.prefix_length());
        } else if (strict) {
          output[i] = IpNetwork::make_na();
          warnOnRow(i, tmp_v6.to_string(), "host bits set");
        } else {
          tmp_v6 = tmp_v6.canonical();
          output[i] = IpNetwork::make_ipv6(tmp_v6.address().to_bytes(), tmp_v6.prefix_length());
        }
      }

    } else {

      // Construct IPv4
      if (prefix_length[i] < 0 || prefix_length[i] > 32) {
        output[i] = IpNetwork::make_na();
        asio::ip::address_v4 asio_address(address[i].bytes_v4());
        std::string cidr = asio_address.to_string() + "/" + std::to_string(prefix_length[i]);
        warnOnRow(i, cidr, "prefix length out-of-bounds");
      } else {
        asio::ip::network_v4 tmp_v4(asio::ip::address_v4(address[i].bytes_v4()), prefix_length[i]);
        if (is_interface || tmp_v4 == tmp_v4.canonical()) {
          output[i] = IpNetwork::make_ipv4(tmp_v4.address().to_bytes(), tmp_v4.prefix_length());
        } else if (strict) {
          output[i] = IpNetwork::make_na();
          warnOnRow(i, tmp_v4.to_string(), "host bits set");
        } else {
          tmp_v4 = tmp_v4.canonical();
          output[i] = IpNetwork::make_ipv4(tmp_v4.address().to_bytes(), tmp_v4.prefix_length());
        }
      }
    }
  }

  return encode_networks(output);
}

// [[Rcpp::export]]
CharacterVector wrap_print_network(List x, bool exploded = false) {
  std::vector<IpNetwork> network = decode_networks(x);

  // initialize vectors
  std::size_t vsize = network.size();
  CharacterVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (network[i].is_na()) {
      output[i] = NA_STRING;
    } else if (exploded && network[i].is_ipv6()) {
      char buffer[50];
      auto bytes = network[i].address().bytes_v6();
      sprintf(
        buffer,
        "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x/%u",
        bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
        bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15],
        network[i].prefix_length()
      );

      output[i] = std::string(buffer);
    } else {
      output[i] = to_string(network[i]);
    }
  }

  return output;
}
