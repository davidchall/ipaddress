#include "reserved.h"
#include "masking.h"

bool is_6to4(const asio::ip::address_v6 &address) {
  asio::ip::address_v6::bytes_type bytes = address.to_bytes();
  return ((bytes[0] == 0x20) && (bytes[1] == 0x02));
}

asio::ip::address_v4 extract_6to4(const asio::ip::address_v6 &address) {
  asio::ip::address_v4::bytes_type bytes_v4;
  asio::ip::address_v6::bytes_type bytes_v6 = address.to_bytes();

  std::copy(bytes_v6.begin() + 2, bytes_v6.begin() + 6, bytes_v4.begin());

  return asio::ip::make_address_v4(bytes_v4);
}

bool is_teredo(const asio::ip::address_v6 &address) {
  asio::ip::address_v6::bytes_type bytes = address.to_bytes();
  return ((bytes[0] == 0x20) && (bytes[1] == 0x01)
      && (bytes[2] == 0) && (bytes[3] == 0));
}

asio::ip::address_v4 extract_teredo_server(const asio::ip::address_v6 &address) {
  asio::ip::address_v4::bytes_type bytes_v4;
  asio::ip::address_v6::bytes_type bytes_v6 = address.to_bytes();

  std::copy(bytes_v6.begin() + 4, bytes_v6.begin() + 8, bytes_v4.begin());

  return asio::ip::make_address_v4(bytes_v4);
}

asio::ip::address_v4 extract_teredo_client(const asio::ip::address_v6 &address) {
  asio::ip::address_v4::bytes_type bytes_v4;
  asio::ip::address_v6::bytes_type bytes_v6 = address.to_bytes();

  std::copy(bytes_v6.begin() + 12, bytes_v6.end(), bytes_v4.begin());

  return bitwise_not(asio::ip::make_address_v4(bytes_v4));
}
