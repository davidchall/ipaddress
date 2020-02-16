#include "masking.h"

asio::ip::address_v6::bytes_type netmask_bytes_v6(int prefix_length) {
  asio::ip::address_v6::bytes_type out;

  for (unsigned int j=0; j<16; ++j) {
    int ingest = std::min(prefix_length, 8);
    uint8_t byte_mask = ingest == 0 ? 0 : (1 << 8) - (1 << (8 - ingest));

    std::memcpy(&out[j], &byte_mask, sizeof(byte_mask));

    prefix_length = std::max(prefix_length - 8, 0);
  }

  return out;
}

asio::ip::address_v6 netmask_v6(int prefix_length) {
  return asio::ip::address_v6(netmask_bytes_v6(prefix_length));
}

asio::ip::address_v6 hostmask_v6(int prefix_length) {
  asio::ip::address_v6::bytes_type hostmask_bytes = netmask_bytes_v6(prefix_length);

  for (unsigned int i=0; i<hostmask_bytes.size(); ++i) {
    hostmask_bytes[i] = ~hostmask_bytes[i];
  }

  return asio::ip::address_v6(hostmask_bytes);
}
