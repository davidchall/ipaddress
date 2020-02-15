#include "encoding.hpp"

int32_t encode_ipv4(asio::ip::address_v4 x) {
  return (int32_t)x.to_uint();
}

asio::ip::address_v4 decode_ipv4(int32_t x) {
  return asio::ip::make_address_v4((uint32_t)x);
}

std::array<int32_t, 4> encode_ipv6(asio::ip::address_v6 x) {
  asio::ip::address_v6::bytes_type address_bytes = x.to_bytes();

  uint32_t x1_n, x2_n, x3_n, x4_n;
  std::memcpy(&x1_n, &address_bytes[0], sizeof(x1_n));
  std::memcpy(&x2_n, &address_bytes[4], sizeof(x2_n));
  std::memcpy(&x3_n, &address_bytes[8], sizeof(x3_n));
  std::memcpy(&x4_n, &address_bytes[12], sizeof(x4_n));

  int32_t x1 = (int32_t)ntohl(x1_n);
  int32_t x2 = (int32_t)ntohl(x2_n);
  int32_t x3 = (int32_t)ntohl(x3_n);
  int32_t x4 = (int32_t)ntohl(x4_n);

  return std::array<int32_t, 4> {x1, x2, x3, x4};
}

asio::ip::address_v6 decode_ipv6(std::array<int32_t, 4> x) {
  // convert from processor order to network order
  uint32_t x1_n = htonl((uint32_t)x[0]);
  uint32_t x2_n = htonl((uint32_t)x[1]);
  uint32_t x3_n = htonl((uint32_t)x[2]);
  uint32_t x4_n = htonl((uint32_t)x[3]);

  asio::ip::address_v6::bytes_type address_bytes;
  std::memcpy(&address_bytes[0], &x1_n, sizeof(x1_n));
  std::memcpy(&address_bytes[4], &x2_n, sizeof(x2_n));
  std::memcpy(&address_bytes[8], &x3_n, sizeof(x3_n));
  std::memcpy(&address_bytes[12], &x4_n, sizeof(x4_n));

  return asio::ip::address_v6(address_bytes);
}
