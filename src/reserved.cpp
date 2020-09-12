#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>
#include <ipaddress.h>

using namespace Rcpp;
using namespace ipaddress;


LogicalVector checkCondition(
  const std::vector<IpAddress> &address,
  const std::function<bool(const asio::ip::address_v4&)>& condition_v4,
  const std::function<bool(const asio::ip::address_v6&)>& condition_v6
) {
  // initialize vectors
  std::size_t vsize = address.size();
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = NA_LOGICAL;
    } else if (address[i].is_ipv6()) {
      asio::ip::address_v6 asio_address(address[i].bytes_v6());
      output[i] = condition_v6(asio_address);
    } else {
      asio::ip::address_v4 asio_address(address[i].bytes_v4());
      output[i] = condition_v4(asio_address);
    }
  }

  return output;
}

LogicalVector checkCondition(
  const std::vector<IpNetwork> &network,
  const std::function<bool(const asio::ip::address_v4&)>& condition_v4,
  const std::function<bool(const asio::ip::address_v6&)>& condition_v6
) {
  // initialize vectors
  std::size_t vsize = network.size();
  LogicalVector output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (network[i].is_na()) {
      output[i] = NA_LOGICAL;
    } else if (network[i].is_ipv6()) {
      IpAddress first = network[i].address();
      IpAddress last = broadcast_address(network[i]);

      asio::ip::address_v6 asio_first(first.bytes_v6());
      asio::ip::address_v6 asio_last(last.bytes_v6());

      output[i] = condition_v6(asio_first) && condition_v6(asio_last);
    } else {
      IpAddress first = network[i].address();
      IpAddress last = broadcast_address(network[i]);

      asio::ip::address_v4 asio_first(first.bytes_v4());
      asio::ip::address_v4 asio_last(last.bytes_v4());

      output[i] = condition_v4(asio_first) && condition_v4(asio_last);
    }
  }

  return output;
}

List map6to4(
  const std::vector<IpAddress> &address,
  const std::function<bool(const asio::ip::address_v6&)>& filter_fn,
  const std::function<asio::ip::address_v4(const asio::ip::address_v6&)>& map_fn
) {
  // initialize vectors
  std::size_t vsize = address.size();
  std::vector<IpAddress> output(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_ipv6() && !address[i].is_na()) {
      asio::ip::address_v6 asio_address(address[i].bytes_v6());
      if (filter_fn(asio_address)) {
        output[i] = IpAddress::make_ipv4(map_fn(asio_address).to_bytes());
      } else {
        output[i] = IpAddress::make_na();
      }
    } else {
      output[i] = IpAddress::make_na();
    }
  }

  return encode_addresses(output);
}


/*----------------------*
 *  Reserved addresses  *
 * ---------------------*/
// [[Rcpp::export]]
LogicalVector wrap_is_multicast(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return x.is_multicast(); };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_multicast(); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_unspecified(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return x.is_unspecified(); };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_unspecified(); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_loopback(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return x.is_loopback(); };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_loopback(); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_link_local(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return (x.to_uint() & 0xFFFF0000) == 0xA9FE0000; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_link_local(); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
LogicalVector wrap_is_site_local(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_site_local(); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}


/*------------------------------*
 *  IPv6 transition mechanisms  *
 * -----------------------------*/
// [[Rcpp::export]]
LogicalVector wrap_is_ipv4_mapped(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return x.is_v4_mapped(); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
List wrap_extract_ipv4_mapped(List input) {
  return map6to4(
    decode_addresses(input),
    [](const asio::ip::address_v6 &x) { return x.is_v4_mapped(); },
    [](const asio::ip::address_v6 &x) { return asio::ip::make_address_v4(asio::ip::v4_mapped, x); }
  );
}

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

// [[Rcpp::export]]
LogicalVector wrap_is_6to4(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return is_6to4(x); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
List wrap_extract_6to4(List input) {
  return map6to4(
    decode_addresses(input),
    [](const asio::ip::address_v6 &x) { return is_6to4(x); },
    [](const asio::ip::address_v6 &x) { return extract_6to4(x); }
  );
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
  std::transform(bytes_v4.begin(), bytes_v4.end(), bytes_v4.begin(),
                 [](unsigned char b) { return ~b; });

  return asio::ip::make_address_v4(bytes_v4);
}

// [[Rcpp::export]]
LogicalVector wrap_is_teredo(List input) {
  auto condition_v4 = [](const asio::ip::address_v4 &x) { return false; };
  auto condition_v6 = [](const asio::ip::address_v6 &x) { return is_teredo(x); };

  if (input.inherits("ip_address")) {
    return checkCondition(decode_addresses(input), condition_v4, condition_v6);
  } else {
    return checkCondition(decode_networks(input),  condition_v4, condition_v6);
  }
}

// [[Rcpp::export]]
List wrap_extract_teredo_server(List input) {
  return map6to4(
    decode_addresses(input),
    [](const asio::ip::address_v6 &x) { return is_teredo(x); },
    [](const asio::ip::address_v6 &x) { return extract_teredo_server(x); }
  );
}

// [[Rcpp::export]]
List wrap_extract_teredo_client(List input) {
  return map6to4(
    decode_addresses(input),
    [](const asio::ip::address_v6 &x) { return is_teredo(x); },
    [](const asio::ip::address_v6 &x) { return extract_teredo_client(x); }
  );
}
