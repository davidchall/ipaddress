#ifndef __IPADDRESS_ADDRESS__
#define __IPADDRESS_ADDRESS__

#include <array>
#include <cstring>
#include <ipaddress/endian.h>


namespace ipaddress {

class IpAddress {
public:
  typedef std::array<unsigned char, 4> bytes_type_v4;
  typedef std::array<unsigned char, 16> bytes_type_v6;
  typedef bytes_type_v6 bytes_type_both;

  // Bytes data are public for easy editing (but iterators are recommended)
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

  IpAddress(const bytes_type_both &bytes, bool is_ipv6, bool is_na)
    : bytes(bytes), is_ipv6_(is_ipv6), is_na_(is_na) {}

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
  bool is_ipv4() const {
    return !is_na_ && !is_ipv6_;
  }

  bool is_ipv6() const {
    return !is_na_ && is_ipv6_;
  }

  bool is_na() const {
    return is_na_;
  }

  unsigned int n_bytes() const {
    return is_ipv6_ ? 16 : 4;
  }

  unsigned int n_bits() const {
    return is_ipv6_ ? 128 : 32;
  }

  bytes_type_v6 bytes_v6() const {
    return bytes;
  }

  bytes_type_v4 bytes_v4() const {
    bytes_type_v4 less_bytes;
    std::copy(bytes.begin(), bytes.begin() + 4, less_bytes.begin());
    return less_bytes;
  }


  /* --------------------------- *
   *  Iterators for bytes array  *
   * --------------------------- */
  bytes_type_both::iterator begin() {
    return bytes.begin();
  }

  bytes_type_both::const_iterator begin() const {
    return bytes.begin();
  }

  bytes_type_both::iterator end() {
    return is_ipv6_ ? bytes.end() : bytes.begin() + 4;
  }

  bytes_type_both::const_iterator end() const {
    return is_ipv6_ ? bytes.end() : bytes.begin() + 4;
  }

  bytes_type_both::reverse_iterator rbegin() {
    return is_ipv6_ ? bytes.rbegin() : bytes.rend() - 4;
  }

  bytes_type_both::const_reverse_iterator rbegin() const {
    return is_ipv6_ ? bytes.rbegin() : bytes.rend() - 4;
  }

  bytes_type_both::reverse_iterator rend() {
    return bytes.rend();
  }

  bytes_type_both::const_reverse_iterator rend() const {
    return bytes.rend();
  }


  /* ---------------------- *
   *  Comparison operators  *
   * ---------------------- */
  friend bool operator==(const IpAddress &lhs, const IpAddress &rhs) {
    if (lhs.is_na_ || rhs.is_na_) {
      return lhs.is_na_ == rhs.is_na_;
    } else {
      return (lhs.is_ipv6_ == rhs.is_ipv6_) && (lhs.bytes == rhs.bytes);
    }
  }

  friend bool operator!=(const IpAddress &lhs, const IpAddress &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const IpAddress &lhs, const IpAddress &rhs) {
    // Missing data ranked high
    if (lhs.is_na_) return false;
    if (rhs.is_na_) return true;

    // IPv4 lower than IPv6
    if (lhs.is_ipv6_ == rhs.is_ipv6_) {
      return std::memcmp(&lhs.bytes, &rhs.bytes, lhs.n_bytes()) < 0;
    } else {
      return rhs.is_ipv6_;
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


  /* --------------------- *
   *  Increment operators  *
   * --------------------- */
  // pre-increment
  IpAddress& operator++() {
    if (is_na_) {
      return *this;
    }

    bool overflow = true;
    for (auto it = rbegin(); it != rend(); ++it) {
      if (*it == 0xFF) {
        *it = 0;
      } else {
        ++*it;
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
    if (is_na_) {
      return *this;
    }

    bool overflow = true;
    for (auto it = rbegin(); it != rend(); ++it) {
      if (*it == 0) {
        *it = 0xFF;
      } else {
        --*it;
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


  /* ---------------------- *
   *  Arithmetic operators  *
   * ---------------------- */
  friend IpAddress operator+(const IpAddress &lhs, int32_t n) {
    IpAddress result = lhs;

    if (n == 0 || lhs.is_na()) {
      return lhs;
    } else if (n == 1) {
      return ++result;
    } else if (n == -1) {
      return --result;
    }

    // cast signed to unsigned: negative n becomes (2^32 - n)
    uint32_t ingest = n;
    uint32_t old_bytes, old_int, new_int, new_bytes;

    // consider 32 bits at a time, moving right to left
    auto it_in = lhs.rbegin() + 3;
    auto it_out = result.rbegin() + 3;
    for (; it_in != lhs.rend(); it_in += 4, it_out += 4) {
      std::memcpy(&old_bytes, &*it_in, 4);
      old_int = network_to_host_long(old_bytes);
      new_int = old_int + ingest;
      new_bytes = host_to_network_long(new_int);
      std::memcpy(&*it_out, &new_bytes, 4);

      // catch overflow
      if ((n > 0) == (new_int < old_int)) {
        ingest = n > 0 ? 1 : -1;
      } else {
        break;
      }
    }

    // catch overflow
    if ((n > 0) == (result < lhs)) {
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
