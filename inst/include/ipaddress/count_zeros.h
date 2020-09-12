#ifndef __IPADDRESS_COUNT_ZEROS__
#define __IPADDRESS_COUNT_ZEROS__

#include <ipaddress/IpAddress.h>


namespace ipaddress {

inline unsigned int count_trailing_zero_bits(const IpAddress &address) {
  if (address.is_na()) {
    return 0;
  }

  unsigned int zeros = 0;
  unsigned int ingest;

  for (auto it = address.rbegin(); it != address.rend(); ++it) {
    ingest = *it;

    if (ingest == 0) {
      zeros += CHAR_BIT;
    } else {
      zeros += __builtin_ctz(ingest);
      break;
    }
  }

  return zeros;
}

inline unsigned int count_leading_zero_bits(const IpAddress &address) {
  if (address.is_na()) {
    return 0;
  }

  unsigned int zeros = 0;
  unsigned int ingest;
  unsigned int unused_bits = (sizeof(ingest) - 1) * CHAR_BIT;

  for (auto it = address.begin(); it != address.end(); ++it) {
    ingest = *it;

    if (ingest == 0) {
      zeros += CHAR_BIT;
    } else {
      zeros += __builtin_clz(ingest) - unused_bits;
      break;
    }
  }

  return zeros;
}

}

#endif
