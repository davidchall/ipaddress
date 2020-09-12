#include <Rcpp.h>
#include <ipaddress.h>

using namespace Rcpp;
using namespace ipaddress;


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


// [[Rcpp::export]]
LogicalVector wrap_is_within(List address_r, List network_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::size_t vsize = address.size();
  LogicalVector output(vsize);

  if (network.size() != vsize) {
    stop("Address and network must have same length"); // # nocov
  }

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

  // initialize vectors
  LogicalVector output(address.size());

  unsigned int i = 0;
  for (std::size_t i_addr=0; i_addr<address.size(); ++i_addr) {
    if (address[i_addr].is_na()) {
      output[i_addr] = NA_LOGICAL;
    } else {
      output[i_addr] = false;
      for (std::size_t i_netw=0; i_netw<network.size(); ++i_netw) {
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


IpNetwork common_network(const IpAddress &addr1, const IpAddress &addr2) {
  if (addr1.is_na() || addr2.is_na() || (addr1.is_ipv6() != addr2.is_ipv6())) {
    return IpNetwork::make_na();
  }

  unsigned int prefix = count_leading_zero_bits(bitwise_xor(addr1, addr2));
  IpAddress netmask = prefix_to_netmask(prefix, addr1.is_ipv6());
  IpAddress start_address = bitwise_and(addr1, netmask);

  return IpNetwork(start_address, prefix);
}


// [[Rcpp::export]]
List wrap_smallest_common_network(List address1_r, List address2_r) {
  std::vector<IpAddress> address1 = decode_addresses(address1_r);
  std::vector<IpAddress> address2 = decode_addresses(address2_r);

  // initialize vectors
  std::size_t vsize = address1.size();
  std::vector<IpNetwork> output(vsize);

  if (address2.size() != vsize) {
    stop("Addresses must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    output[i] = common_network(address1[i], address2[i]);
  }

  return encode_networks(output);
}
