#ifndef __IPADDRESS_COUNT_ZEROS__
#define __IPADDRESS_COUNT_ZEROS__

#include <ipaddress/IpAddress.h>


namespace ipaddress {

inline int count_trailing_zero_bits(const IpAddress &address) {
  bool is_empty = std::all_of(address.cbegin(), address.cend(),
                              [](unsigned char b){ return b == 0; });
  if (is_empty) {
    return address.n_bits();
  }

  int zeros = 0;
  for (std::size_t i=0; i<address.n_bytes(); ++i) {
    uint32_t ingest = address.bytes[address.n_bytes()-1-i];

    if (ingest == 0) {
      zeros += 8;
    } else {
      zeros += __builtin_ctz(ingest);
      break;
    }
  }

  return zeros;
}

inline int count_leading_zero_bits(const IpAddress &address) {
  bool is_empty = std::all_of(address.cbegin(), address.cend(),
                              [](unsigned char b){ return b == 0; });
  if (is_empty) {
    return address.n_bits();
  }

  int zeros = 0;
  for (std::size_t i=0; i<address.n_bytes(); ++i) {
    uint32_t ingest = address.bytes[i];

    if (ingest == 0) {
      zeros += 8;
    } else {
      // ingest is 32-bits but only uses final 8-bits
      zeros += __builtin_clz(ingest) - 24;
      break;
    }
  }

  return zeros;
}

}

#endif
