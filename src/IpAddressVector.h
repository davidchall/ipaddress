#ifndef __IPADDRESS_ADDRESS__
#define __IPADDRESS_ADDRESS__

#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>

using namespace Rcpp;

class IpNetworkVector;

class IpAddressVector {
  friend class IpNetworkVector;

private:
  std::vector<asio::ip::address_v4> address_v4;
  std::vector<asio::ip::address_v6> address_v6;
  std::vector<bool> is_ipv6;
  std::vector<bool> is_na;

  IpAddressVector(
    std::vector<asio::ip::address_v4> &in_address_v4,
    std::vector<asio::ip::address_v6> &in_address_v6,
    std::vector<bool> &in_is_ipv6,
    std::vector<bool> &in_is_na
  ) : address_v4(in_address_v4), address_v6(in_address_v6), is_ipv6(in_is_ipv6), is_na(in_is_na) { };

  LogicalVector isTrue(
      const std::function<bool(const asio::ip::address_v4&)>& decide_fn_v4,
      const std::function<bool(const asio::ip::address_v6&)>& decide_fn_v6
  ) const;

  IpAddressVector map6to4(
      const std::function<bool(const asio::ip::address_v6&)>& filter_fn,
      const std::function<asio::ip::address_v4(const asio::ip::address_v6&)>& map_fn
  ) const;

public:
  /*----------------*
   *  Constructors  *
   *----------------*/
  // Parse strings (dotted-decimal or dotted-hexidecimal format)
  IpAddressVector(CharacterVector input);

  // Decode from R class
  IpAddressVector(List input);

  // Decode from R blob (list of raw vectors)
  static IpAddressVector decodePacked(List input);

  // Decode from binary string
  static IpAddressVector decodeBinary(CharacterVector input);

  // Construct netmask from prefix length
  static IpAddressVector createNetmask(IntegerVector prefix_length, LogicalVector is_ipv6);

  // Construct hostmask from prefix length
  static IpAddressVector createHostmask(IntegerVector prefix_length, LogicalVector is_ipv6);

  // Warn about invalid input
  static void warnInvalidInput(unsigned int index, const std::string &input, const std::string &reason = "");


  /*----------*
   *  Output  *
   *----------*/
  // Encode to strings
  CharacterVector encodeStrings() const;

  // Encode to R class
  List encodeR() const;

  // Encode to R blob (list of raw vectors)
  List encodePacked() const;

  // Encode to binary string
  CharacterVector encodeBinary() const;

  // Encode to R dataframe for direct comparisons
  DataFrame encodeComparable() const;


  /*-------------*
   *  Operators  *
   *-------------*/
  IpAddressVector operator~() const;
  IpAddressVector operator&(const IpAddressVector &rhs) const;
  IpAddressVector operator|(const IpAddressVector &rhs) const;
  IpAddressVector operator^(const IpAddressVector &rhs) const;
  IpAddressVector operator+(const IntegerVector &rhs) const;
  IpAddressVector operator-(const IntegerVector &rhs) const;


  /*-----------------------*
   *  Other functionality  *
   *-----------------------*/
  LogicalVector isWithin(const IpNetworkVector &network) const;
  LogicalVector isWithinAny(const IpNetworkVector &network) const;


  /*----------------------*
   *  Reserved addresses  *
   * ---------------------*/
  LogicalVector isMulticast() const;
  LogicalVector isUnspecified() const;
  LogicalVector isLoopback() const;
  LogicalVector isLinkLocal() const;


  /*------------------------------*
   *  IPv6 transition mechanisms  *
   * -----------------------------*/
  LogicalVector isIPv4Mapped() const;
  IpAddressVector extractIPv4Mapped() const;
  LogicalVector is6to4() const;
  IpAddressVector extract6to4() const;
  LogicalVector isTeredo() const;
  IpAddressVector extractTeredoServer() const;
  IpAddressVector extractTeredoClient() const;
};

#endif
