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

public:
  /*----------------*
   *  Constructors  *
   *----------------*/
  // Parse strings (dotted-decimal or dotted-hexidecimal format)
  IpAddressVector(CharacterVector input);

  // Decode from R class
  IpAddressVector(List input);

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

  // Encode to R dataframe for direct comparisons
  DataFrame encodeComparable() const;

  List asBlob() const;


  /*---------------------*
   *  Bitwise operators  *
   *---------------------*/
  IpAddressVector operator&(const IpAddressVector &rhs) const;
  IpAddressVector operator|(const IpAddressVector &rhs) const;
  IpAddressVector operator~() const;


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
};

#endif
