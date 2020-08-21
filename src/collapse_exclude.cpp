#include <Rcpp.h>
#include <ipaddress/IpNetworkVector.h>
#include "collapse_exclude.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_collapse_networks(List input_r) {
  IpNetworkVector input(input_r);
  std::size_t vsize = input.size();

  // extract networks (IPv4 & IPv6 handled independently)
  std::vector<asio::ip::network_v4> uncollapsed_v4;
  std::vector<asio::ip::network_v6> uncollapsed_v6;
  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input.is_na[i]) {
      // pass
    } else if (input.is_ipv6[i]) {
      uncollapsed_v6.push_back(input.network_v6[i]);
    } else {
      uncollapsed_v4.push_back(input.network_v4[i]);
    }
  }

  // collapse networks
  std::vector<asio::ip::network_v4> collapsed_v4 = collapse(uncollapsed_v4);
  std::vector<asio::ip::network_v6> collapsed_v6 = collapse(uncollapsed_v6);

  // fill output vectors
  std::vector<asio::ip::network_v4> out_network_v4;
  std::vector<asio::ip::network_v6> out_network_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  std::copy(collapsed_v4.begin(), collapsed_v4.end(), std::back_inserter(out_network_v4));
  std::fill_n(std::back_inserter(out_network_v6), collapsed_v4.size(), asio::ip::network_v6());
  std::fill_n(std::back_inserter(out_is_ipv6), collapsed_v4.size(), false);
  std::fill_n(std::back_inserter(out_is_na), collapsed_v4.size(), false);

  std::copy(collapsed_v6.begin(), collapsed_v6.end(), std::back_inserter(out_network_v6));
  std::fill_n(std::back_inserter(out_network_v4), collapsed_v6.size(), asio::ip::network_v4());
  std::fill_n(std::back_inserter(out_is_ipv6), collapsed_v6.size(), true);
  std::fill_n(std::back_inserter(out_is_na), collapsed_v6.size(), false);

  return IpNetworkVector(out_network_v4, out_network_v6, out_is_ipv6, out_is_na).encodeR();
}
