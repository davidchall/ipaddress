#include <Rcpp.h>
#include <ipaddress.h>

using namespace Rcpp;
using namespace ipaddress;


std::vector<IpAddress> calculate_hosts(const IpNetwork &network, bool exclude_unusable) {
  unsigned int bits_used = network.max_prefix_length() - network.prefix_length();

  std::vector<IpAddress> hosts;
  hosts.reserve(1 << bits_used);

  // setup pseudo-iterators in IP space
  IpAddress ip_begin = network.address();
  IpAddress ip_end = broadcast_address(network);

  if (network.is_ipv6()) {
    // IPv6 does not use final address as broadcast address
    ++ip_end;

    // exclude subnet router anycast address
    if (exclude_unusable && (bits_used != 1)) {
      ++ip_begin;
    }
  } else {
    // exclude network and broadcast addresses
    if (exclude_unusable && (bits_used != 1)) {
      ++ip_begin;
    } else {
      ++ip_end;
    }
  }

  unsigned int i = 0;
  while (ip_begin != ip_end) {
    if (i++ % 10000 == 0) {
      checkUserInterrupt();
    }

    hosts.push_back(ip_begin);
    ++ip_begin;
  }

  return hosts;
}


// [[Rcpp::export]]
List wrap_network_hosts(List network_r, bool exclude_unusable) {
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::vector<IpAddress> output;

  if (network.size() != 1) {
    // pass
  } else if (network[0].is_na()) {
    output.push_back(IpAddress::make_na());
  } else if (exclude_unusable && (network[0].prefix_length() == network[0].max_prefix_length())) {
    // pass
  } else {
    output = calculate_hosts(network[0], exclude_unusable);
  }

  return encode_addresses(output);
}


std::vector<IpNetwork> calculate_subnets(const IpNetwork &network, int new_prefix) {
  std::vector<IpNetwork> result;

  // setup pseudo-iterators in IP space
  IpAddress range_start = network.address();
  IpAddress range_end = broadcast_address(network);
  IpAddress block_start = range_start;

  unsigned int i = 0;
  while (block_start <= range_end) {
    if (i++ % 10000 == 0) {
      checkUserInterrupt();
    }

    IpNetwork network(block_start, new_prefix);
    result.push_back(network);

    // advance to next block
    block_start = ++broadcast_address(network);

    // if block ends on all-ones, then increment operator wraps around to all-zeros
    if (block_start <= range_start) {
      break;
    }
  }

  return result;
}


// [[Rcpp::export]]
List wrap_subnets(List network_r, IntegerVector new_prefix) {
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::vector<IpNetwork> output;

  if ((network.size() != 1) || (new_prefix.size() != 1)) {
    // pass
  } else if (network[0].is_na() || new_prefix[0] == NA_INTEGER) {
    output.push_back(IpNetwork::make_na());
  } else {
    output = calculate_subnets(network[0], new_prefix[0]);
  }

  return encode_networks(output);
}
