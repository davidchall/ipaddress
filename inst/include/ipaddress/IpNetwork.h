#ifndef __IPADDRESS_NETWORK__
#define __IPADDRESS_NETWORK__

#include <ipaddress/IpAddress.h>


namespace ipaddress {

class IpNetwork {
private:
  IpAddress address_;
  unsigned int prefix_;

public:
  /* -------------- *
   *  Constructors  *
   * -------------- */
  // default constructor
  IpNetwork() : address_(), prefix_(0) {}

  // construct from IpAddress
  IpNetwork(const IpAddress &address, unsigned int prefix)
    : address_(address), prefix_(prefix) {}

  static IpNetwork make_ipv6(const IpAddress::bytes_type_v6 &bytes, unsigned int prefix) {
    return IpNetwork(IpAddress::make_ipv6(bytes), prefix);
  }

  static IpNetwork make_ipv4(const IpAddress::bytes_type_v4 &bytes, unsigned int prefix) {
    return IpNetwork(IpAddress::make_ipv4(bytes), prefix);
  }

  static IpNetwork make_na() {
    return IpNetwork(IpAddress::make_na(), 0);
  }


  /* ----------- *
   *  Accessors  *
   * ----------- */
  IpAddress address() const {
    return address_;
  }

  unsigned int prefix_length() const {
    return prefix_;
  }

  unsigned int max_prefix_length() const {
    return address_.n_bits();
  }

  bool is_ipv4() const {
    return address_.is_ipv4();
  }

  bool is_ipv6() const {
    return address_.is_ipv6();
  }

  bool is_na() const {
    return address_.is_na();
  }
};

}

#endif
