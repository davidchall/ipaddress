#include <Rcpp.h>
#include <ipaddress.h>
#include <ipaddress/to_string.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


std::vector<IpNetwork> calculate_subnets(const IpNetwork &network, int new_prefix) {
  std::vector<IpNetwork> result;

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
    if (block_start <= range_start) break;
  }

  return result;
}


std::vector<IpAddress> calculate_hosts(const IpNetwork &network, bool exclude_unusable) {
  unsigned int max_prefix_length = network.address().n_bits();
  unsigned int bits_used = max_prefix_length - network.prefix_length();

  std::vector<IpAddress> hosts;
  hosts.reserve(1 << bits_used);

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
List wrap_broadcast_address(List network_r) {
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::size_t vsize = network.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    output[i] = broadcast_address(network[i]);
  }

  return encode_addresses(output);
}


/*------------------------------------*
 *  Netmask, hostmask, prefix length  *
 * -----------------------------------*/

// [[Rcpp::export]]
List wrap_netmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6) {
  // initialize vectors
  std::size_t vsize = in_is_ipv6.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (in_is_ipv6[i] == NA_LOGICAL || in_prefix_length[i] == NA_INTEGER) {
      output[i] = IpAddress::make_na();
    } else {
      output[i] = prefix_to_netmask(in_prefix_length[i], in_is_ipv6[i]);
    }
  }

  return encode_addresses(output);
}

// [[Rcpp::export]]
List wrap_hostmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6) {
  // initialize vectors
  std::size_t vsize = in_is_ipv6.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (in_is_ipv6[i] == NA_LOGICAL || in_prefix_length[i] == NA_INTEGER) {
      output[i] = IpAddress::make_na();
    } else {
      output[i] = prefix_to_hostmask(in_prefix_length[i], in_is_ipv6[i]);
    }
  }

  return encode_addresses(output);
}

// [[Rcpp::export]]
IntegerVector wrap_prefix_from_mask(List address_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);

  // initialize vectors
  std::size_t vsize = address.size();
  IntegerVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = NA_INTEGER;
    } else {
      int prefix = netmask_to_prefix(address[i]);
      if (prefix == -1) {
        prefix = hostmask_to_prefix(address[i]);
      }
      if (prefix == -1) {
        warnOnRow(i, to_string(address[i]), "invalid netmask/hostmask");
        output[i] = NA_INTEGER;
      } else {
        output[i] = prefix;
      }
    }
  }

  return output;
}


/*----------------------*
 *  Network membership  *
 * ---------------------*/

// [[Rcpp::export]]
LogicalVector wrap_is_within(List address_r, List network_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);
  std::vector<IpNetwork> network = decode_networks(network_r);

  std::size_t vsize = address.size();

  if (network.size() != vsize) {
    stop("Address and network must have same length"); // # nocov
  }

  // initialize vectors
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na() || network[i].is_na()) {
      output[i] = NA_LOGICAL;
    } else {
      output[i] = address_in_network(address[i], network[i]);
    }
  }

  return output;
}

// [[Rcpp::export]]
LogicalVector wrap_is_within_any(List address_r, List network_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);
  std::vector<IpNetwork> network = decode_networks(network_r);

  std::size_t address_size = address.size();
  std::size_t network_size = network.size();

  // initialize vectors
  LogicalVector output(address_size);

  unsigned int i = 0;
  for (std::size_t i_addr=0; i_addr<address_size; ++i_addr) {
    if (address[i_addr].is_na()) {
      output[i_addr] = NA_LOGICAL;
    } else {
      output[i_addr] = false;
      for (std::size_t i_netw=0; i_netw<network_size; ++i_netw) {
        if (i++ % 10000 == 0) {
          checkUserInterrupt();
        }

        if (network[i_netw].is_na() || address[i_addr].is_ipv6() != network[i_netw].is_ipv6()) {
          continue;
        } else if (address[i_addr].is_ipv6()) {
          if (address_in_network(address[i_addr], network[i_netw])) {
            output[i_addr] = true;
          }
        } else if (address_in_network(address[i_addr], network[i_netw])) {
          output[i_addr] = true;
        }
      }
    }
  }

  return output;
}

/*---------*
 *  Other  *
 * --------*/

// [[Rcpp::export]]
List wrap_network_hosts(List network_r, bool exclude_unusable) {
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::vector<IpAddress> output;

  if (network.size() != 1) {
    // pass
  } else if (network[0].is_na()) {
    output.push_back(IpAddress::make_na());
  } else if (exclude_unusable && network[0].prefix_length() == network[0].address().n_bits()) {
    // pass
  } else {
    output = calculate_hosts(network[0], exclude_unusable);
  }

  return encode_addresses(output);
}

// [[Rcpp::export]]
List wrap_subnets(List network_r, IntegerVector new_prefix) {
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::vector<IpNetwork> output;

  if (network.size() != 1) {
    // pass
  } else if (network[0].is_na() || new_prefix[0] == NA_INTEGER) {
    output.push_back(IpNetwork::make_na());
  } else {
    output = calculate_subnets(network[0], new_prefix[0]);
  }

  return encode_networks(output);
}

inline IpNetwork common_network(const IpAddress &addr1, const IpAddress &addr2) {
  if (addr1.is_na() || addr2.is_na() || (addr1.is_ipv6() != addr2.is_ipv6())) {
    return IpNetwork::make_na();
  }

  int prefix = count_leading_zero_bits(bitwise_xor(addr1, addr2));
  IpAddress netmask = prefix_to_netmask(prefix, addr1.is_ipv6());
  IpAddress start_address = bitwise_and(addr1, netmask);

  return IpNetwork(start_address, prefix);
}

// [[Rcpp::export]]
List wrap_smallest_common_network(List address1_r, List address2_r) {
  std::vector<IpAddress> address1 = decode_addresses(address1_r);
  std::vector<IpAddress> address2 = decode_addresses(address2_r);

  std::size_t vsize = address1.size();

  if (address2.size() != vsize) {
    stop("Addresses must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<IpNetwork> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    output[i] = common_network(address1[i], address2[i]);
  }

  return encode_networks(output);
}
