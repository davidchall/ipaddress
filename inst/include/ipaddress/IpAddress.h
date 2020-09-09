#ifndef __IPADDRESS_ADDRESS__
#define __IPADDRESS_ADDRESS__

#include <array>
#include <cstring>

#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif


namespace ipaddress {

class IpAddress {
public:
  typedef std::array<unsigned char, 4> bytes_type_v4;
  typedef std::array<unsigned char, 16> bytes_type_v6;
  typedef bytes_type_v6 bytes_type_both;

  // Bytes data are public for easy editing
  bytes_type_both bytes;

private:
  bool is_ipv6_;
  bool is_na_;

public:
  /* -------------- *
   *  Constructors  *
   * -------------- */
  // default constructor
  IpAddress() : bytes({}), is_ipv6_(false), is_na_(false) {}

  IpAddress(const bytes_type_both &bytes, bool is_ipv6, bool is_na) :
    bytes(bytes), is_ipv6_(is_ipv6), is_na_(is_na) {}

  static IpAddress make_ipv6(const bytes_type_v6 &bytes = {}) {
    return IpAddress(bytes, true, false);
  }

  static IpAddress make_ipv4(const bytes_type_v4 &bytes = {}) {
    bytes_type_both more_bytes{};
    std::copy(bytes.begin(), bytes.end(), more_bytes.begin());
    return IpAddress(more_bytes, false, false);
  }

  static IpAddress make_na() {
    bytes_type_both empty_bytes{};
    return IpAddress(empty_bytes, false, true);
  }


  /* ----------- *
   *  Accessors  *
   * ----------- */
  bool is_ipv6() const { return is_ipv6_; }
  bool is_na() const { return is_na_; }
  int n_bytes() const { return is_ipv6_ ? 16 : 4; }
  int n_bits() const { return is_ipv6_ ? 128 : 32; }

  bytes_type_v6 bytes_v6() const { return bytes; }
  bytes_type_v4 bytes_v4() const {
    bytes_type_v4 less_bytes;
    std::copy(bytes.begin(), bytes.begin() + 4, less_bytes.begin());
    return less_bytes;
  }

  // Iterators for bytes data (IPv4/IPv6 friendly)
  bytes_type_both::iterator begin() { return bytes.begin(); }
  bytes_type_both::const_iterator cbegin() const { return bytes.cbegin(); }
  bytes_type_both::iterator end() {
    return is_ipv6_ ? bytes.end() : bytes.begin() + 4;
  }
  bytes_type_both::const_iterator cend() const {
    return is_ipv6_ ? bytes.cend() : bytes.cbegin() + 4;
  }


  /* ---------------------- *
   *  Comparison operators  *
   * ---------------------- */
  friend bool operator==(const IpAddress &lhs, const IpAddress &rhs) {
    return (lhs.is_ipv6_ == rhs.is_ipv6_)
      && (lhs.is_na_ == rhs.is_na_)
      && (lhs.bytes == rhs.bytes);
  }
  friend bool operator!=(const IpAddress &lhs, const IpAddress &rhs) {
    return !(lhs == rhs);
  }
  friend bool operator<(const IpAddress &lhs, const IpAddress &rhs) {
    // Missing data ranked high
    if (lhs.is_na_ && rhs.is_na_) return false;
    if (lhs.is_na_) return false;
    if (rhs.is_na_) return true;

    // IPv4 lower than IPv6
    if (lhs.is_ipv6_ == rhs.is_ipv6_) {
      return std::memcmp(&lhs.bytes, &rhs.bytes, lhs.n_bytes()) < 0;
    } else if (lhs.is_ipv6_) {
      return false;
    } else {
      return true;
    }
  }
  friend bool operator>(const IpAddress &lhs, const IpAddress &rhs) {
    return rhs < lhs;
  }
  friend bool operator<=(const IpAddress &lhs, const IpAddress &rhs) {
    return !(rhs < lhs);
  }
  friend bool operator>=(const IpAddress &lhs, const IpAddress &rhs) {
    return !(lhs < rhs);
  }


  /* ---------------------- *
   *  Arithmetic operators  *
   * ---------------------- */
  // pre-increment
  IpAddress& operator++() {
    bool overflow = true;
    for (int i=n_bytes()-1; i>=0; --i) {
      if (bytes[i] == 0xff) {
        bytes[i] = 0;
      } else {
        ++bytes[i];
        overflow = false;
        break;
      }
    }

    if (overflow) {
      *this = make_na();
    }

    return *this;
  }

  // post-increment
  IpAddress operator++(int) {
    IpAddress tmp(*this);
    ++*this;
    return tmp;
  }

  // pre-decrement
  IpAddress& operator--() {
    bool overflow = true;
    for (int i=n_bytes()-1; i>=0; --i) {
      if (bytes[i] == 0) {
        bytes[i] = 0xff;
      } else {
        --bytes[i];
        overflow = false;
        break;
      }
    }

    if (overflow) {
      *this = make_na();
    }

    return *this;
  }

  // post-decrement
  IpAddress operator--(int) {
    IpAddress tmp(*this);
    --*this;
    return tmp;
  }

  // addition
  friend IpAddress operator+(const IpAddress &lhs, int32_t n) {
    IpAddress result = lhs;

    if (n == 0 || lhs.is_na()) {
      return lhs;
    } else if (n == 1) {
      return ++result;
    } else if (n == -1) {
      return --result;
    }

    // consider 32 bits at a time, moving right to left
    uint32_t ingest = n;
    uint32_t old_int, new_int, new_bytes;

    for (int i=lhs.n_bytes()-4; i>=0; i-=4) {
      std::memcpy(&old_int, &lhs.bytes[i], 4);
      old_int = ntohl(old_int);
      new_int = old_int + ingest;
      new_bytes = htonl(new_int);
      std::memcpy(&result.bytes[i], &new_bytes, 4);

      if ((n > 0 && new_int < old_int) || (n < 0 && new_int > old_int)) {
        ingest = n > 0 ? 1 : -1;
      } else {
        break;
      }
    }

    // catch overflow
    if ((n > 0 && result < lhs) || (n < 0 && result > lhs)) {
      return IpAddress::make_na();
    } else {
      return result;
    }
  }

  // subtraction
  friend IpAddress operator-(const IpAddress &lhs, int32_t n) {
    return lhs + (-n);
  }
};

}

#endif
