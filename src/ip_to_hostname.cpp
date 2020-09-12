#include <Rcpp.h>
#include <asio/ip/tcp.hpp>
#include <ipaddress.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_decode_hostname(CharacterVector input) {
  // initialize vectors
  std::size_t vsize = input.size();
  List outputs(vsize);

  asio::io_context io_context;
  asio::ip::tcp::resolver resolver(io_context);
  asio::ip::tcp::endpoint endpoint;
  asio::error_code ec;

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 100 == 0) {
      checkUserInterrupt();
    }

    // initialize vector
    std::vector<IpAddress> output;

    if (input[i] == NA_STRING) {
      output.push_back(IpAddress::make_na());
    } else {
      std::string hostname(input[i]);
      // forward DNS resolution
      auto results = resolver.resolve(hostname, "http", ec);

      if (ec) {
        if (ec != asio::error::host_not_found) {
          warnOnRow(i, hostname, ec.message()); // # nocov
        }
        output.push_back(IpAddress::make_na());
      } else {
        for (auto const& entry : results) {
          auto address = entry.endpoint().address();
          if (address.is_v4()) {
            output.push_back(IpAddress::make_ipv4(address.to_v4().to_bytes()));
          } else {
            output.push_back(IpAddress::make_ipv6(address.to_v6().to_bytes()));
          }
        }
      }
    }

    outputs[i] = encode_addresses(output);
  }

  return outputs;
}

// [[Rcpp::export]]
List wrap_encode_hostname(List input) {
  std::vector<IpAddress> address = decode_addresses(input);

  // initialize vectors
  std::size_t vsize = address.size();
  List outputs(vsize);

  asio::io_context io_context;
  asio::ip::tcp::resolver resolver(io_context);
  asio::ip::tcp::endpoint endpoint;
  asio::error_code ec;

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 100 == 0) {
      checkUserInterrupt();
    }

    CharacterVector hostnames;
    if (address[i].is_na()) {
      hostnames.push_back(NA_STRING);
    } else {
      if (address[i].is_ipv6()) {
        asio::ip::address_v6 asio_address(address[i].bytes_v6());
        endpoint.address(asio_address);
      } else {
        asio::ip::address_v4 asio_address(address[i].bytes_v4());
        endpoint.address(asio_address);
      }

      // reverse DNS resolution
      auto results = resolver.resolve(endpoint, ec);

      if (ec) { // # nocov start
        warnOnRow(i, endpoint.address().to_string(), ec.message());
        hostnames.push_back(NA_STRING);
      } else { // # nocov end
        for (auto const& entry : results) {
          // unresolved hostnames often returned as original IP address
          if (entry.host_name() != endpoint.address().to_string()) {
            hostnames.push_back(entry.host_name());
          }
        }
        if (hostnames.size() == 0) {
          hostnames.push_back(NA_STRING);
        }
      }
    }

    outputs[i] = hostnames;
  }

  return outputs;
}
