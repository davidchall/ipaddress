#ifndef __IPADDRESS_BITWISE__
#define __IPADDRESS_BITWISE__

#include <algorithm>

namespace ipaddress {

template<class Address>
Address bitwise_not(const Address &addr1) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), result_bytes.begin(),
                 [](unsigned char b1) { return ~b1; });

  return Address(result_bytes);
}

template<class Address>
Address bitwise_and(const Address &addr1, const Address &addr2) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes addr2_bytes = addr2.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), addr2_bytes.begin(), result_bytes.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 & b2; });

  return Address(result_bytes);
}

template<class Address>
Address bitwise_or(const Address &addr1, const Address &addr2) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes addr2_bytes = addr2.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), addr2_bytes.begin(), result_bytes.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 | b2; });

  return Address(result_bytes);
}

template<class Address>
Address bitwise_xor(const Address &addr1, const Address &addr2) {
  typedef typename Address::bytes_type Bytes;
  Bytes addr1_bytes = addr1.to_bytes();
  Bytes addr2_bytes = addr2.to_bytes();
  Bytes result_bytes;

  std::transform(addr1_bytes.begin(), addr1_bytes.end(), addr2_bytes.begin(), result_bytes.begin(),
                 [](unsigned char b1, unsigned char b2) { return b1 ^ b2; });

  return Address(result_bytes);
}

template<class Address>
Address bitwise_shift_left(const Address &input, unsigned int n_bit_shifts) {
  typedef typename Address::bytes_type Bytes;
  Bytes in_bytes = input.to_bytes();
  Bytes out_bytes;

  const int n_bytes = sizeof(Bytes);
  const int n_bits_per_byte = 8;
  const int n_bit_shifts_inside_byte = n_bit_shifts % n_bits_per_byte;
  const int n_bit_shifts_outside_byte = n_bits_per_byte - n_bit_shifts_inside_byte;
  const int n_byte_shifts = n_bit_shifts / n_bits_per_byte;
  const int i_final_byte = n_bytes - n_byte_shifts - 1;

  for (int i=0; i<n_bytes; ++i) {
    if (i <= i_final_byte) {
      out_bytes[i] = in_bytes[i + n_byte_shifts] << n_bit_shifts_inside_byte;
      if (i != i_final_byte) {
        out_bytes[i] |= in_bytes[i + n_byte_shifts + 1] >> n_bit_shifts_outside_byte;
      }
    } else {
      out_bytes[i] = 0;
    }
  }

  return Address(out_bytes);
}

template<class Address>
Address bitwise_shift_right(const Address &input, unsigned int n_bit_shifts) {
  typedef typename Address::bytes_type Bytes;
  Bytes in_bytes = input.to_bytes();
  Bytes out_bytes;

  const int n_bytes = sizeof(Bytes);
  const int n_bits_per_byte = 8;
  const int n_bit_shifts_inside_byte = n_bit_shifts % n_bits_per_byte;
  const int n_bit_shifts_outside_byte = n_bits_per_byte - n_bit_shifts_inside_byte;
  const int n_byte_shifts = n_bit_shifts / n_bits_per_byte;
  const int i_first_byte = n_byte_shifts;

  for (int i=0; i<n_bytes; ++i) {
    if (i >= i_first_byte) {
      out_bytes[i] = in_bytes[i - n_byte_shifts] >> n_bit_shifts_inside_byte;
      if (i != i_first_byte) {
        out_bytes[i] |= in_bytes[i - n_byte_shifts - 1] << n_bit_shifts_outside_byte;
      }
    } else {
      out_bytes[i] = 0;
    }
  }

  return Address(out_bytes);
}

}

#endif
