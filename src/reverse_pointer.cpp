#include <Rcpp.h>
#include <ipaddress.h>

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
CharacterVector wrap_reverse_pointer(List address_r) {
  std::vector<IpAddress> address = decode_addresses(address_r);

  // initialize vectors
  std::size_t vsize = address.size();
  CharacterVector output(vsize);

  std::ostringstream os;
  char buffer[40];

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (address[i].is_na()) {
      output[i] = NA_STRING;
    } else if (address[i].is_ipv6()) {
      auto bytes = address[i].bytes_v6();
      sprintf(
        buffer,
        "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
        bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
        bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]
      );

      std::string str(buffer);
      std::reverse(str.begin(), str.end());
      std::copy(str.begin(), str.end(), std::ostream_iterator<char>(os, "."));

      output[i] = os.str() + "ip.arpa";
    } else {
      auto bytes = address[i].bytes_v4();
      sprintf(
        buffer,
        "%i.%i.%i.%i.in-addr.arpa",
        bytes[3], bytes[2], bytes[1], bytes[0]
      );

      output[i] = std::string(buffer);
    }
  }

  return output;
}
