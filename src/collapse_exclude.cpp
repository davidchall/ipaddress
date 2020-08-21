#include <Rcpp.h>
#include <ipaddress/IpNetworkVector.h>
#include "collapse_exclude.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_collapse_networks(List input_r) {
  IpNetworkVector input(input_r);

  // extract networks (IPv4 & IPv6 handled independently)
  std::vector<asio::ip::network_v4> pre_collapse_v4;
  std::vector<asio::ip::network_v6> pre_collapse_v6;
  for (std::size_t i=0; i<input.size(); ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input.is_na[i]) {
      // pass
    } else if (input.is_ipv6[i]) {
      pre_collapse_v6.push_back(input.network_v6[i]);
    } else {
      pre_collapse_v4.push_back(input.network_v4[i]);
    }
  }

  // collapse networks
  std::vector<asio::ip::network_v4> post_collapse_v4 = collapse_networks(pre_collapse_v4);
  std::vector<asio::ip::network_v6> post_collapse_v6 = collapse_networks(pre_collapse_v6);

  // fill output vectors
  std::vector<asio::ip::network_v4> out_network_v4;
  std::vector<asio::ip::network_v6> out_network_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  std::copy(post_collapse_v4.begin(), post_collapse_v4.end(), std::back_inserter(out_network_v4));
  std::fill_n(std::back_inserter(out_network_v6), post_collapse_v4.size(), asio::ip::network_v6());
  std::fill_n(std::back_inserter(out_is_ipv6), post_collapse_v4.size(), false);
  std::fill_n(std::back_inserter(out_is_na), post_collapse_v4.size(), false);

  std::copy(post_collapse_v6.begin(), post_collapse_v6.end(), std::back_inserter(out_network_v6));
  std::fill_n(std::back_inserter(out_network_v4), post_collapse_v6.size(), asio::ip::network_v4());
  std::fill_n(std::back_inserter(out_is_ipv6), post_collapse_v6.size(), true);
  std::fill_n(std::back_inserter(out_is_na), post_collapse_v6.size(), false);

  return IpNetworkVector(out_network_v4, out_network_v6, out_is_ipv6, out_is_na).encodeR();
}


// [[Rcpp::export]]
List wrap_exclude_networks(List include_r, List exclude_r) {
  IpNetworkVector include(include_r);
  IpNetworkVector exclude(exclude_r);

  // extract include networks (IPv4 & IPv6 handled independently)
  std::vector<asio::ip::network_v4> include_v4;
  std::vector<asio::ip::network_v6> include_v6;
  for (std::size_t i=0; i<include.size(); ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (include.is_na[i]) {
      // pass
    } else if (include.is_ipv6[i]) {
      include_v6.push_back(include.network_v6[i]);
    } else {
      include_v4.push_back(include.network_v4[i]);
    }
  }

  // extract exclude networks (IPv4 & IPv6 handled independently)
  std::vector<asio::ip::network_v4> exclude_v4;
  std::vector<asio::ip::network_v6> exclude_v6;
  for (std::size_t i=0; i<exclude.size(); ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (exclude.is_na[i]) {
      // pass
    } else if (exclude.is_ipv6[i]) {
      exclude_v6.push_back(exclude.network_v6[i]);
    } else {
      exclude_v4.push_back(exclude.network_v4[i]);
    }
  }

  // exclude networks
  std::vector<asio::ip::network_v4> post_exclusion_v4 = exclude_networks(include_v4, exclude_v4);
  std::vector<asio::ip::network_v6> post_exclusion_v6 = exclude_networks(include_v6, exclude_v6);

  // fill output vectors
  std::vector<asio::ip::network_v4> out_network_v4;
  std::vector<asio::ip::network_v6> out_network_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  std::copy(post_exclusion_v4.begin(), post_exclusion_v4.end(), std::back_inserter(out_network_v4));
  std::fill_n(std::back_inserter(out_network_v6), post_exclusion_v4.size(), asio::ip::network_v6());
  std::fill_n(std::back_inserter(out_is_ipv6), post_exclusion_v4.size(), false);
  std::fill_n(std::back_inserter(out_is_na), post_exclusion_v4.size(), false);

  std::copy(post_exclusion_v6.begin(), post_exclusion_v6.end(), std::back_inserter(out_network_v6));
  std::fill_n(std::back_inserter(out_network_v4), post_exclusion_v6.size(), asio::ip::network_v4());
  std::fill_n(std::back_inserter(out_is_ipv6), post_exclusion_v6.size(), true);
  std::fill_n(std::back_inserter(out_is_na), post_exclusion_v6.size(), false);

  return IpNetworkVector(out_network_v4, out_network_v6, out_is_ipv6, out_is_na).encodeR();
}
