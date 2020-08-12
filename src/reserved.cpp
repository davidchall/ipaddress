#include <Rcpp.h>
#include <ipaddress/IpAddressVector.h>
#include <ipaddress/IpNetworkVector.h>
#include <ipaddress/masking.h>

using namespace Rcpp;
using namespace ipaddress;


LogicalVector checkCondition(
  const IpAddressVector &address,
  const std::function<bool(const asio::ip::address_v4&)>& condition_v4,
  const std::function<bool(const asio::ip::address_v6&)>& condition_v6
) {
  std::size_t vsize = address.size();
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (address.is_ipv6[i]) {
      output[i] = condition_v6(address.address_v6[i]);
    } else {
      output[i] = condition_v4(address.address_v4[i]);
    }
  }

  return output;
}

LogicalVector checkCondition(
  const IpNetworkVector &network,
  const std::function<bool(const asio::ip::address_v4&)>& condition_v4,
  const std::function<bool(const asio::ip::address_v6&)>& condition_v6
) {
  std::size_t vsize = network.size();
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (network.is_na[i]) {
      output[i] = NA_LOGICAL;
    } else if (network.is_ipv6[i]) {
      asio::ip::address_v6 first = network.network_v6[i].address();
      asio::ip::address_v6 last = broadcast_address<asio::ip::address_v6>(network.network_v6[i]);
      output[i] = condition_v6(first) && condition_v6(last);
    } else {
      asio::ip::address_v4 first = network.network_v4[i].address();
      asio::ip::address_v4 last = broadcast_address<asio::ip::address_v4>(network.network_v4[i]);
      output[i] = condition_v4(first) && condition_v4(last);
    }
  }

  return output;
}

IpAddressVector map6to4(
  const IpAddressVector &address,
  const std::function<bool(const asio::ip::address_v6&)>& filter_fn,
  const std::function<asio::ip::address_v4(const asio::ip::address_v6&)>& map_fn
) {
  std::size_t vsize = address.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address.is_ipv6[i] && filter_fn(address.address_v6[i])) {
      out_address_v4[i] = map_fn(address.address_v6[i]);
    } else {
      out_is_na[i] = true;
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na);
}


/*----------------------*
 *  Reserved addresses  *
 * ---------------------*/
// [[Rcpp::export]]
LogicalVector wrap_is_multicast(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return x.is_multicast(); };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_multicast(); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_unspecified(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return x.is_unspecified(); };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_unspecified(); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_loopback(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return x.is_loopback(); };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_loopback(); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_link_local(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return (x.to_uint() & 0xFFFF0000) == 0xA9FE0000; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_link_local(); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_site_local(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_site_local(); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}


/*------------------------------*
 *  IPv6 transition mechanisms  *
 * -----------------------------*/
bool is_6to4(const asio::ip::address_v6 &address) {
  asio::ip::address_v6::bytes_type bytes = address.to_bytes();
  return ((bytes[0] == 0x20) && (bytes[1] == 0x02));
}

asio::ip::address_v4 extract_6to4(const asio::ip::address_v6 &address) {
  asio::ip::address_v4::bytes_type bytes_v4;
  asio::ip::address_v6::bytes_type bytes_v6 = address.to_bytes();

  std::copy(bytes_v6.begin() + 2, bytes_v6.begin() + 6, bytes_v4.begin());

  return asio::ip::make_address_v4(bytes_v4);
}

bool is_teredo(const asio::ip::address_v6 &address) {
  asio::ip::address_v6::bytes_type bytes = address.to_bytes();
  return ((bytes[0] == 0x20) && (bytes[1] == 0x01)
            && (bytes[2] == 0) && (bytes[3] == 0));
}

asio::ip::address_v4 extract_teredo_server(const asio::ip::address_v6 &address) {
  asio::ip::address_v4::bytes_type bytes_v4;
  asio::ip::address_v6::bytes_type bytes_v6 = address.to_bytes();

  std::copy(bytes_v6.begin() + 4, bytes_v6.begin() + 8, bytes_v4.begin());

  return asio::ip::make_address_v4(bytes_v4);
}

asio::ip::address_v4 extract_teredo_client(const asio::ip::address_v6 &address) {
  asio::ip::address_v4::bytes_type bytes_v4;
  asio::ip::address_v6::bytes_type bytes_v6 = address.to_bytes();

  std::copy(bytes_v6.begin() + 12, bytes_v6.end(), bytes_v4.begin());

  return bitwise_not(asio::ip::make_address_v4(bytes_v4));
}


// [[Rcpp::export]]
LogicalVector wrap_is_ipv4_mapped(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_v4_mapped(); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
List wrap_extract_ipv4_mapped(List input) {
  return map6to4(
    IpAddressVector(input),
    [](const asio::ip::address_v6 &x) { return x.is_v4_mapped(); },
    [](const asio::ip::address_v6 &x) { return asio::ip::make_address_v4(asio::ip::v4_mapped, x); }
  ).encodeR();
}

// [[Rcpp::export]]
LogicalVector wrap_is_6to4(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return is_6to4(x); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
List wrap_extract_6to4(List input) {
  return map6to4(
    IpAddressVector(input),
    [](const asio::ip::address_v6 &x) { return is_6to4(x); },
    [](const asio::ip::address_v6 &x) { return extract_6to4(x); }
  ).encodeR();
}

// [[Rcpp::export]]
LogicalVector wrap_is_teredo(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return is_teredo(x); };

  if (input.inherits("ip_address")) {
    return checkCondition(IpAddressVector(input), condition_v4, condition_v6);
  } else {
    return checkCondition(IpNetworkVector(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
List wrap_extract_teredo_server(List input) {
  return map6to4(
    IpAddressVector(input),
    [](const asio::ip::address_v6 &x) { return is_teredo(x); },
    [](const asio::ip::address_v6 &x) { return extract_teredo_server(x); }
  ).encodeR();
}

// [[Rcpp::export]]
List wrap_extract_teredo_client(List input) {
  return map6to4(
    IpAddressVector(input),
    [](const asio::ip::address_v6 &x) { return is_teredo(x); },
    [](const asio::ip::address_v6 &x) { return extract_teredo_client(x); }
  ).encodeR();
}
