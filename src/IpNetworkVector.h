#ifndef __IPADDRESS_NETWORK__
#define __IPADDRESS_NETWORK__

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>

using namespace Rcpp;

class IpAddressVector;

class IpNetworkVector {
  friend class IpAddressVector;

private:
  std::vector<asio::ip::network_v4> network_v4;
  std::vector<asio::ip::network_v6> network_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

  IpNetworkVector(
    std::vector<asio::ip::network_v4> in_network_v4,
    std::vector<asio::ip::network_v6> in_network_v6,
    std::vector<bool> in_is_ipv6,
    std::vector<bool> in_is_na
  ) : network_v4(in_network_v4), network_v6(in_network_v6), is_ipv6(in_is_ipv6), is_na(in_is_na) { };

public:
  /*----------------*
   *  Constructors  *
   *----------------*/
  // Parse strings (CIDR format)
  IpNetworkVector(CharacterVector input, bool strict);

  // Decode from R class
  IpNetworkVector(List input);

  // Construct from address + prefix length
  IpNetworkVector(IpAddressVector address, IntegerVector prefix_length, bool strict);


  /*----------*
   *  Output  *
   *----------*/
  // Encode to strings
  CharacterVector encodeStrings() const;

  // Encode to R class
  List encodeR() const;


  /*-----------------------*
   *  Other functionality  *
   *-----------------------*/
  // Return last address in network
  IpAddressVector broadcastAddress() const;

  // List all addresses in network
  IpAddressVector hosts(bool exclude_unusable) const;
};

#endif
