#ifndef __IPADDRESS_NETWORK__
#define __IPADDRESS_NETWORK__

#include <Rcpp.h>
#include <asio/ip/network_v4.hpp>
#include <asio/ip/network_v6.hpp>


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

  Rcpp::LogicalVector isTrue(
      const std::function<bool(const asio::ip::address_v4&)>& decide_fn_v4,
      const std::function<bool(const asio::ip::address_v6&)>& decide_fn_v6
  ) const;

public:
  /*----------------*
   *  Constructors  *
   *----------------*/
  // Parse strings (CIDR format)
  IpNetworkVector(Rcpp::CharacterVector input,
                  bool strict, bool is_interface = false);

  // Decode from R class
  IpNetworkVector(Rcpp::List input);

  // Construct from address + prefix length
  IpNetworkVector(IpAddressVector address, Rcpp::IntegerVector prefix_length,
                  bool strict, bool is_interface = false);

  // Construct from two addresses (single network)
  static IpNetworkVector smallestCommonNetwork(const IpAddressVector &address1, const IpAddressVector &address2);

  // Construct from two addresses (multiple networks)
  static Rcpp::List summarizeAddressRange(const IpAddressVector &address1, const IpAddressVector &address2);

  // Warn about invalid input
  static void warnInvalidInput(unsigned int index, const std::string &input, const std::string &reason = "");


  /*----------*
   *  Output  *
   *----------*/
  // Encode to strings
  Rcpp::CharacterVector encodeStrings() const;

  // Encode to R class
  Rcpp::List encodeR() const;


  /*-----------------------*
   *  Other functionality  *
   *-----------------------*/
  // Return last address in network
  IpAddressVector broadcastAddress() const;

  // List subnetworks in network
  IpNetworkVector subnets(Rcpp::IntegerVector new_prefix) const;

  // List all addresses in network
  IpAddressVector hosts(bool exclude_unusable) const;

  // Sample random addresses in network
  IpAddressVector sample(unsigned int size) const;


  /*----------------------*
   *  Reserved addresses  *
   * ---------------------*/
  Rcpp::LogicalVector isMulticast() const;
  Rcpp::LogicalVector isUnspecified() const;
  Rcpp::LogicalVector isLoopback() const;
  Rcpp::LogicalVector isLinkLocal() const;
  Rcpp::LogicalVector isIPv4Mapped() const;
  Rcpp::LogicalVector is6to4() const;
  Rcpp::LogicalVector isTeredo() const;
};

#endif
