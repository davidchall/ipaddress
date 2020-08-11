#include <Rcpp.h>
#include <ipaddress/IpAddressVector.h>
#include <ipaddress/IpNetworkVector.h>
#include "masking.h"
#include "iterative.h"
#include "sample.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_broadcast_address(List network_r) {
  IpNetworkVector network(network_r);

  std::size_t vsize = network.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize);
  std::vector<bool> out_is_na(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (network.is_na[i]) {
      out_is_na[i] = true;
    } else if (network.is_ipv6[i]) {
      out_address_v6[i] = broadcast_address<asio::ip::address_v6>(network.network_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = broadcast_address<asio::ip::address_v4>(network.network_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}


/*------------------------------------*
 *  Netmask, hostmask, prefix length  *
 * -----------------------------------*/

// [[Rcpp::export]]
List wrap_netmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6) {
  std::size_t vsize = in_is_ipv6.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (in_is_ipv6[i] == NA_LOGICAL || in_prefix_length[i] == NA_INTEGER) {
      out_is_na[i] = true;
    } else if (in_is_ipv6[i]) {
      out_address_v6[i] = prefix_to_netmask<asio::ip::address_v6>(in_prefix_length[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = prefix_to_netmask<asio::ip::address_v4>(in_prefix_length[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_hostmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6) {
  std::size_t vsize = in_is_ipv6.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (in_is_ipv6[i] == NA_LOGICAL || in_prefix_length[i] == NA_INTEGER) {
      out_is_na[i] = true;
    } else if (in_is_ipv6[i]) {
      out_address_v6[i] = prefix_to_hostmask<asio::ip::address_v6>(in_prefix_length[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = prefix_to_hostmask<asio::ip::address_v4>(in_prefix_length[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
IntegerVector wrap_prefix_from_mask(List address_r) {
  IpAddressVector address(address_r);

  std::size_t vsize = address.size();

  // initialize vectors
  IntegerVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_na[i]) {
      output[i] = NA_INTEGER;
    } else if (address.is_ipv6[i]) {
      int prefix = netmask_to_prefix(address.address_v6[i]);
      if (prefix == -1) {
        prefix = hostmask_to_prefix(address.address_v6[i]);
      }
      if (prefix == -1) {
        warnOnRow(i, address.address_v6[i].to_string(), "invalid netmask/hostmask");
        output[i] = NA_INTEGER;
      } else {
        output[i] = prefix;
      }
    } else {
      int prefix = netmask_to_prefix(address.address_v4[i]);
      if (prefix == -1) {
        prefix = hostmask_to_prefix(address.address_v4[i]);
      }
      if (prefix == -1) {
        warnOnRow(i, address.address_v4[i].to_string(), "invalid netmask/hostmask");
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
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

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

    if (address.is_na[i] || network.is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (address.is_ipv6[i] != network.is_ipv6[i]) {
      output[i] = false;
    } else if (address.is_ipv6[i]) {
      output[i] = address_in_network(address.address_v6[i], network.network_v6[i]);
    } else {
      output[i] = address_in_network(address.address_v4[i], network.network_v4[i]);
    }
  }

  return output;
}

// [[Rcpp::export]]
LogicalVector wrap_is_within_any(List address_r, List network_r) {
  IpAddressVector address(address_r);
  IpNetworkVector network(network_r);

  std::size_t address_size = address.size();
  std::size_t network_size = network.size();

  // initialize vectors
  LogicalVector output(address_size);

  unsigned int i = 0;
  for (std::size_t i_addr=0; i_addr<address_size; ++i_addr) {
    if (address.is_na[i_addr]) {
      output[i_addr] = NA_LOGICAL;
    } else {
      output[i_addr] = false;
      for (std::size_t i_netw=0; i_netw<network_size; ++i_netw) {
        if (i++ % 10000 == 0) {
          checkUserInterrupt();
        }

        if (network.is_na[i_netw] || address.is_ipv6[i_addr] != network.is_ipv6[i_netw]) {
          continue;
        } else if (address.is_ipv6[i_addr]) {
          if (address_in_network(address.address_v6[i_addr], network.network_v6[i_netw])) {
            output[i_addr] = true;
          }
        } else if (address_in_network(address.address_v4[i_addr], network.network_v4[i_netw])) {
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
  IpNetworkVector network(network_r);

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4;
  std::vector<asio::ip::address_v6> out_address_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  if (network.size() != 1) {
    // pass
  } else if (network.is_na[0]) {
    out_address_v4.resize(1);
    out_address_v6.resize(1);
    out_is_ipv6.resize(1);
    out_is_na.resize(1, true);
  } else if (exclude_unusable && network.is_ipv6[0] && network.network_v6[0].prefix_length() == 128) {
    // pass
  } else if (exclude_unusable && !network.is_ipv6[0] && network.network_v4[0].prefix_length() == 32) {
    // pass
  } else if (network.is_ipv6[0]) {
    out_address_v6 = calculate_hosts<asio::ip::address_v6>(network.network_v6[0], exclude_unusable, true);

    std::size_t vsize = out_address_v6.size();
    out_address_v4.resize(vsize);
    out_is_ipv6.resize(vsize, true);
    out_is_na.resize(vsize, false);
  } else {
    out_address_v4 = calculate_hosts<asio::ip::address_v4>(network.network_v4[0], exclude_unusable, false);

    std::size_t vsize = out_address_v4.size();
    out_address_v6.resize(vsize);
    out_is_ipv6.resize(vsize, false);
    out_is_na.resize(vsize, false);
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_subnets(List network_r, IntegerVector new_prefix) {
  IpNetworkVector network(network_r);

  // initialize vectors
  std::vector<asio::ip::network_v4> out_network_v4;
  std::vector<asio::ip::network_v6> out_network_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  if (network.size() != 1) {
    // pass
  } else if (network.is_na[0] || new_prefix[0] == NA_INTEGER) {
    out_network_v4.resize(1);
    out_network_v6.resize(1);
    out_is_ipv6.resize(1);
    out_is_na.resize(1, true);
  } else if (network.is_ipv6[0]) {
    out_network_v6 = calculate_subnets<asio::ip::address_v6>(network.network_v6[0], new_prefix[0]);

    std::size_t vsize = out_network_v6.size();
    out_network_v4.resize(vsize);
    out_is_ipv6.resize(vsize, true);
    out_is_na.resize(vsize);
  } else {
    out_network_v4 = calculate_subnets<asio::ip::address_v4>(network.network_v4[0], new_prefix[0]);

    std::size_t vsize = out_network_v4.size();
    out_network_v6.resize(vsize);
    out_is_ipv6.resize(vsize);
    out_is_na.resize(vsize);
  }

  return IpNetworkVector(out_network_v4, out_network_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_sample_network(List network_r, unsigned int size) {
  IpNetworkVector network(network_r);

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4;
  std::vector<asio::ip::address_v6> out_address_v6;
  std::vector<bool> out_is_ipv6;
  std::vector<bool> out_is_na;

  if (network.size() != 1 || network.is_na[0]) {
    // pass
  } else if (network.is_ipv6[0]) {
    out_address_v6 = sample_network<asio::ip::address_v6>(network.network_v6[0], size);
    out_address_v4.resize(size);
    out_is_ipv6.resize(size, true);
    out_is_na.resize(size, false);
  } else {
    out_address_v4 = sample_network<asio::ip::address_v4>(network.network_v4[0], size);
    out_address_v6.resize(size);
    out_is_ipv6.resize(size, false);
    out_is_na.resize(size, false);
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_smallest_common_network(List address1_r, List address2_r) {
  IpAddressVector address1(address1_r);
  IpAddressVector address2(address2_r);

  std::size_t vsize = address1.size();

  if (address2.size() != vsize) {
    stop("Addresses must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::network_v4> out_network_v4(vsize);
  std::vector<asio::ip::network_v6> out_network_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address1.is_na[i] || address2.is_na[i]) {
      out_is_na[i] = true;
    } else if (address1.is_ipv6[i] != address2.is_ipv6[i]) {
      out_is_na[i] = true;
    } else if (address1.is_ipv6[i]) {
      out_network_v6[i] = common_network<asio::ip::network_v6>(address1.address_v6[i], address2.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_network_v4[i] = common_network<asio::ip::network_v4>(address1.address_v4[i], address2.address_v4[i]);
    }
  }

  return IpNetworkVector(out_network_v4, out_network_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_summarize_address_range(List address1_r, List address2_r) {
  IpAddressVector address1(address1_r);
  IpAddressVector address2(address2_r);

  std::size_t vsize = address1.size();
  List output(vsize);

  if (address2.size() != vsize) {
    stop("Addresses must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    // initialize vectors
    std::vector<asio::ip::network_v4> out_network_v4;
    std::vector<asio::ip::network_v6> out_network_v6;
    std::vector<bool> out_is_ipv6;
    std::vector<bool> out_is_na;

    if (address1.is_na[i] || address2.is_na[i]) {
      out_network_v4.resize(1);
      out_network_v6.resize(1);
      out_is_ipv6.resize(1);
      out_is_na.resize(1, true);
    } else if (address1.is_ipv6[i] != address2.is_ipv6[i]) {
      out_network_v4.resize(1);
      out_network_v6.resize(1);
      out_is_ipv6.resize(1);
      out_is_na.resize(1, true);
    } else if (address1.is_ipv6[i]) {
      out_network_v6 = summarize_address_range<asio::ip::network_v6>(address1.address_v6[i], address2.address_v6[i]);

      std::size_t vsize = out_network_v6.size();
      out_network_v4.resize(vsize);
      out_is_ipv6.resize(vsize, true);
      out_is_na.resize(vsize);
    } else {
      out_network_v4 = summarize_address_range<asio::ip::network_v4>(address1.address_v4[i], address2.address_v4[i]);

      std::size_t vsize = out_network_v4.size();
      out_network_v6.resize(vsize);
      out_is_ipv6.resize(vsize);
      out_is_na.resize(vsize);
    }

    output[i] = IpNetworkVector(out_network_v4, out_network_v6, out_is_ipv6, out_is_na).encodeR();
  }

  return output;
}
