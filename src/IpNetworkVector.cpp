#include "IpNetworkVector.hpp"

IpNetworkVector::IpNetworkVector(CharacterVector x)
{
  network.assign(x.size(), asio::ip::network_v4());
  is_na.assign(x.size(), 0);

  CharacterVector::iterator it_input;
  std::vector<asio::ip::network_v4>::iterator it_netw;
  std::vector<bool>::iterator it_na;

  asio::error_code ec;

  for (it_input = x.begin(), it_netw = network.begin(), it_na = is_na.begin();
       it_input != x.end();
       ++it_input, ++it_netw, ++it_na) {
    if (*it_input == NA_STRING) {
      *it_na = true;
    } else {
      *it_netw = asio::ip::make_network_v4(*it_input, ec);
      if (ec) {
        *it_na = true;
        warning(ec.message() + ": " + *it_input);
      }
    }
  }
}

IpNetworkVector::IpNetworkVector(IntegerVector address, IntegerVector prefix)
{
  network.assign(address.size(), asio::ip::network_v4());
  is_na.assign(address.size(), 0);

  IntegerVector::iterator it_addr;
  IntegerVector::iterator it_pfx;
  std::vector<asio::ip::network_v4>::iterator it_netw;
  std::vector<bool>::iterator it_na;

  for (it_addr = address.begin(), it_pfx = prefix.begin(), it_netw = network.begin(), it_na = is_na.begin();
       it_addr != address.end();
       ++it_addr, ++it_pfx, ++it_netw, ++it_na) {
    if (*it_addr == NA_INTEGER || *it_pfx == NA_INTEGER) {
      *it_na = true;
    } else {
      asio::ip::address_v4 address = asio::ip::make_address_v4((unsigned int)*it_addr);
      *it_netw = asio::ip::network_v4(address, *it_pfx);
    }
  }
}

List IpNetworkVector::toList() const
{
  IntegerVector address(network.size());
  IntegerVector prefix(network.size());

  IntegerVector::iterator it_addr;
  IntegerVector::iterator it_pfx;
  std::vector<asio::ip::network_v4>::const_iterator it_netw;
  std::vector<bool>::const_iterator it_na;

  for (it_addr = address.begin(), it_pfx = prefix.begin(), it_netw = network.begin(), it_na = is_na.begin();
       it_addr != address.end();
       ++it_addr, ++it_pfx, ++it_netw, ++it_na) {
    if (*it_na) {
      *it_addr = NA_INTEGER;
      *it_pfx = NA_INTEGER;
    } else {
      *it_addr = (signed int)it_netw->network().to_uint();
      *it_pfx = it_netw->prefix_length();
    }
  }

  return List::create(
    _["address"] = address,
    _["prefix"] = prefix
  );
}

CharacterVector IpNetworkVector::toCharacterVector() const
{
  CharacterVector output(network.size());

  CharacterVector::iterator it_output;
  std::vector<asio::ip::network_v4>::const_iterator it_netw;
  std::vector<bool>::const_iterator it_na;

  for (it_output = output.begin(), it_netw = network.begin(), it_na = is_na.begin();
       it_output != output.end();
       ++it_output, ++it_netw, ++it_na) {
    if (*it_na) {
      *it_output = NA_STRING;
    } else {
      *it_output = it_netw->to_string();
    }
  }

  return output;
}
