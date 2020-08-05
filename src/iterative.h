#ifndef __IPADDRESS_ITERATIVE__
#define __IPADDRESS_ITERATIVE__

#include <vector>
#include <Rcpp/Interrupt.h>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>
#include "masking.h"


template<class Address>
Address advance_ip(const Address &address, int n) {
  if (n == 0)
    return address;

  asio::ip::basic_address_iterator<Address> iter(address);

  if (n > 0) {
    while (n--) {
      if (n % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }
      ++iter;
    }
  }
  else {
    while (n++) {
      if (n % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }
      --iter;
    }
  }

  return *iter;
}

template<class Address, class Network>
std::vector<Network> calculate_subnets(const Network &network, int new_prefix) {
  std::vector<Network> networks;

  Address range_start = network.address();
  Address range_end = broadcast_address<Address>(network);
  Address block_start = range_start;

  unsigned int i = 0;
  while (block_start <= range_end) {
    if (i++ % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    Network network(block_start, new_prefix);
    networks.push_back(network);

    // advance to next block
    Address block_end = broadcast_address<Address>(network);
    block_start = advance_ip(block_end, 1);

    // if block ends on all-ones, then increment operator wraps around to all-zeros
    if (block_start <= range_start) break;
  }

  return networks;
}

template<class Network, class Address>
std::vector<Network> summarize_address_range(const Address &addr1, const Address &addr2) {
  typedef typename Address::bytes_type Bytes;
  int max_prefix = (8 * sizeof(Bytes));
  std::vector<Network> networks;

  // range is covered by 1+ blocks
  Address range_start = addr1 < addr2 ? addr1 : addr2;
  Address range_end = addr1 > addr2 ? addr1 : addr2;
  Address block_start = range_start;

  unsigned int i = 0;
  while (block_start <= range_end) {
    if (i++ % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    int prefix = max_prefix;
    if (block_start != range_end) {
      Address diff_bits = bitwise_xor(block_start, range_end);

      prefix = max_prefix - std::min(
        count_trailing_zero_bits(block_start),
        std::max(
          max_prefix - count_leading_zero_bits(diff_bits) - 1,
          count_trailing_zero_bits(bitwise_not(diff_bits))
        )
      );
    }

    Network network(block_start, prefix);
    networks.push_back(network);

    // advance to next block
    Address block_end = broadcast_address<Address>(network);
    block_start = advance_ip(block_end, 1);

    // if block ends on all-ones, then increment operator wraps around to all-zeros
    if (block_start <= range_start) break;
  }

  return networks;
}

template<class Address, class Network>
std::vector<Address> calculate_hosts(const Network &network, bool exclude_unusable, bool is_ipv6) {
  unsigned int max_prefix_length = is_ipv6 ? 128 : 32;
  unsigned int bits_used = max_prefix_length - network.prefix_length();

  std::vector<Address> hosts;
  hosts.reserve(1 << bits_used);

  asio::ip::basic_address_iterator<Address> ip_begin(network.address());
  asio::ip::basic_address_iterator<Address> ip_end(broadcast_address<Address>(network));

  if (is_ipv6) {
    // IPv6 does not use final address as broadcast address
    ip_end++;

    // exclude subnet router anycast address
    if (exclude_unusable && (bits_used != 1)) {
      ip_begin++;
    }
  } else {
    // exclude network and broadcast addresses
    if (exclude_unusable && (bits_used != 1)) {
      ip_begin++;
    } else {
      ip_end++;
    }
  }

  unsigned int i = 0;
  while (ip_begin != ip_end) {
    if (i++ % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    hosts.push_back(*ip_begin++);
  }

  return hosts;
}

#endif
