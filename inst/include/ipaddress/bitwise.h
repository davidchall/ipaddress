#ifndef __IPADDRESS_BITWISE__
#define __IPADDRESS_BITWISE__

#include <ipaddress/IpAddress.h>
#include <algorithm>


namespace ipaddress {

inline IpAddress bitwise_not(const IpAddress &addr1) {
  if (addr1.is_na()) {
    return IpAddress::make_na();
  }

  IpAddress result = addr1;
  std::transform(addr1.begin(), addr1.end(), result.begin(),
                 [](unsigned char b1) { return ~b1; });

  return result;
}

inline IpAddress bitwise_and(const IpAddress &addr1, const IpAddress &addr2) {
  if (addr1.is_na() || addr2.is_na() || addr1.is_ipv6() != addr2.is_ipv6()) {
    return IpAddress::make_na();
  }

  IpAddress result = addr1;
  std::transform(addr1.begin(), addr1.end(), addr2.begin(), result.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 & b2; });

  return result;
}

inline IpAddress bitwise_or(const IpAddress &addr1, const IpAddress &addr2) {
  if (addr1.is_na() || addr2.is_na() || addr1.is_ipv6() != addr2.is_ipv6()) {
    return IpAddress::make_na();
  }

  IpAddress result = addr1;
  std::transform(addr1.begin(), addr1.end(), addr2.begin(), result.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 | b2; });

  return result;
}

inline IpAddress bitwise_xor(const IpAddress &addr1, const IpAddress &addr2) {
  if (addr1.is_na() || addr2.is_na() || addr1.is_ipv6() != addr2.is_ipv6()) {
    return IpAddress::make_na();
  }

  IpAddress result = addr1;
  std::transform(addr1.begin(), addr1.end(), addr2.begin(), result.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 ^ b2; });

  return result;
}

inline IpAddress bitwise_shift_left(const IpAddress &input, unsigned int n_bit_shifts) {
  if (n_bit_shifts == 0 || input.is_na()) {
    return input;
  }

  IpAddress result = input;

  const int n_bytes = input.n_bytes();
  const int n_bits_per_byte = 8;
  const int n_bit_shifts_inside_byte = n_bit_shifts % n_bits_per_byte;
  const int n_bit_shifts_outside_byte = n_bits_per_byte - n_bit_shifts_inside_byte;
  const int n_byte_shifts = n_bit_shifts / n_bits_per_byte;
  const int i_final_byte = n_bytes - n_byte_shifts - 1;

  for (int i=0; i<n_bytes; ++i) {
    if (i <= i_final_byte) {
      result.bytes[i] = input.bytes[i + n_byte_shifts] << n_bit_shifts_inside_byte;
      if (i != i_final_byte) {
        result.bytes[i] |= input.bytes[i + n_byte_shifts + 1] >> n_bit_shifts_outside_byte;
      }
    } else {
      result.bytes[i] = 0;
    }
  }

  return result;
}

inline IpAddress bitwise_shift_right(const IpAddress &input, unsigned int n_bit_shifts) {
  if (n_bit_shifts == 0 || input.is_na()) {
    return input;
  }

  IpAddress result = input;

  const int n_bytes = input.n_bytes();
  const int n_bits_per_byte = 8;
  const int n_bit_shifts_inside_byte = n_bit_shifts % n_bits_per_byte;
  const int n_bit_shifts_outside_byte = n_bits_per_byte - n_bit_shifts_inside_byte;
  const int n_byte_shifts = n_bit_shifts / n_bits_per_byte;
  const int i_first_byte = n_byte_shifts;

  for (int i=0; i<n_bytes; ++i) {
    if (i >= i_first_byte) {
      result.bytes[i] = input.bytes[i - n_byte_shifts] >> n_bit_shifts_inside_byte;
      if (i != i_first_byte) {
        result.bytes[i] |= input.bytes[i - n_byte_shifts - 1] << n_bit_shifts_outside_byte;
      }
    } else {
      result.bytes[i] = 0;
    }
  }

  return result;
}

}

#endif
