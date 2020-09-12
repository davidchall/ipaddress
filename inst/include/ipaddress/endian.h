#ifndef __IPADDRESS_ENDIAN__
#define __IPADDRESS_ENDIAN__

#if !defined(_WIN32)
#include <arpa/inet.h>
#endif


namespace ipaddress {

inline uint32_t host_to_network_long(uint32_t input) {
#if defined(_WIN32)
  // Windows is always little-endian
  uint32_t output;
  unsigned char* output_bytes = reinterpret_cast<unsigned char*>(&output);
  output_bytes[0] = static_cast<unsigned char>((input >> 24) & 0xFF);
  output_bytes[1] = static_cast<unsigned char>((input >> 16) & 0xFF);
  output_bytes[2] = static_cast<unsigned char>((input >>  8) & 0xFF);
  output_bytes[3] = static_cast<unsigned char>(input & 0xFF);
  return output;
#else
  return htonl(input);
#endif
}

inline uint32_t network_to_host_long(uint32_t input) {
#if defined(_WIN32)
  // Windows is always little-endian
  unsigned char* input_bytes = reinterpret_cast<unsigned char*>(&input);
  uint32_t output = (static_cast<uint32_t>(input_bytes[0]) << 24)
    | (static_cast<uint32_t>(input_bytes[1]) << 16)
    | (static_cast<uint32_t>(input_bytes[2]) << 8)
    | static_cast<uint32_t>(input_bytes[3]);
  return output;
#else
  return ntohl(input);
#endif
}

}

#endif
