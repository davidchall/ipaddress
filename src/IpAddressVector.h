#ifndef __IPADDRESS_ADDRESS__
#define __IPADDRESS_ADDRESS__

#include <Rcpp.h>
#include <asio/ip/address_v4.hpp>
#include <asio/ip/address_v6.hpp>


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

  Rcpp::LogicalVector isTrue(
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
  IpAddressVector(Rcpp::CharacterVector input);

  // Decode from R class
  IpAddressVector(Rcpp::List input);

  // Decode from R blob (list of raw vectors)
  static IpAddressVector decodeBytes(Rcpp::List input);

  // Decode from integer string
  static IpAddressVector decodeInteger(Rcpp::CharacterVector input, Rcpp::Nullable<Rcpp::LogicalVector> is_ipv6);

  // Decode from binary string
  static IpAddressVector decodeBinary(Rcpp::CharacterVector input);

  // Decode from hostname
  static Rcpp::List decodeHostname(Rcpp::CharacterVector input);

  // Construct netmask from prefix length
  static IpAddressVector createNetmask(Rcpp::IntegerVector prefix_length, Rcpp::LogicalVector is_ipv6);

  // Construct hostmask from prefix length
  static IpAddressVector createHostmask(Rcpp::IntegerVector prefix_length, Rcpp::LogicalVector is_ipv6);

  // Warn about invalid input
  static void warnInvalidInput(unsigned int index, const std::string &input, const std::string &reason = "");


  /*----------*
   *  Output  *
   *----------*/
  // Encode to strings
  Rcpp::CharacterVector encodeStrings() const;

  // Encode to R class
  Rcpp::List encodeR() const;

  // Encode to R blob (list of raw vectors)
  Rcpp::List encodeBytes() const;

  // Encode to integer string
  Rcpp::CharacterVector encodeInteger() const;

  // Encode to binary string
  Rcpp::CharacterVector encodeBinary() const;

  // Encode to hostnames
  Rcpp::List encodeHostnames() const;

  // Encode to R dataframe for direct comparisons
  Rcpp::DataFrame encodeComparable() const;


  /*-------------*
   *  Operators  *
   *-------------*/
  IpAddressVector operator~() const;
  IpAddressVector operator&(const IpAddressVector &rhs) const;
  IpAddressVector operator|(const IpAddressVector &rhs) const;
  IpAddressVector operator^(const IpAddressVector &rhs) const;
  IpAddressVector operator+(const Rcpp::IntegerVector &rhs) const;
  IpAddressVector operator-(const Rcpp::IntegerVector &rhs) const;


  /*-----------------------*
   *  Other functionality  *
   *-----------------------*/
  Rcpp::LogicalVector isWithin(const IpNetworkVector &network) const;
  Rcpp::LogicalVector isWithinAny(const IpNetworkVector &network) const;


  /*----------------------*
   *  Reserved addresses  *
   * ---------------------*/
  Rcpp::LogicalVector isMulticast() const;
  Rcpp::LogicalVector isUnspecified() const;
  Rcpp::LogicalVector isLoopback() const;
  Rcpp::LogicalVector isLinkLocal() const;


  /*------------------------------*
   *  IPv6 transition mechanisms  *
   * -----------------------------*/
  Rcpp::LogicalVector isIPv4Mapped() const;
  IpAddressVector extractIPv4Mapped() const;
  Rcpp::LogicalVector is6to4() const;
  IpAddressVector extract6to4() const;
  Rcpp::LogicalVector isTeredo() const;
  IpAddressVector extractTeredoServer() const;
  IpAddressVector extractTeredoClient() const;
};

#endif
