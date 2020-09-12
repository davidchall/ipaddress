#include <Rcpp.h>
#include <ipaddress.h>

using namespace Rcpp;
using namespace ipaddress;


std::vector<IpAddress> sample_bits(bool is_ipv6, unsigned int bits_to_sample, unsigned int n_sample) {
  IpAddress blank_address = is_ipv6 ? IpAddress::make_ipv6() : IpAddress::make_ipv4();
  std::vector<IpAddress> result(n_sample, blank_address);

  for (unsigned int i_byte=blank_address.n_bytes()-1; i_byte>=0; --i_byte) {

    unsigned int sample_max = 0;
    if (bits_to_sample == 0) {
      break;
    } else if (bits_to_sample >= CHAR_BIT) {
      sample_max = 1 << CHAR_BIT;
      bits_to_sample -= CHAR_BIT;
    } else {
      sample_max = 1 << bits_to_sample;
      bits_to_sample = 0;
    }

    IntegerVector byte_vector = sample(sample_max, n_sample, true, R_NilValue, false);

    for (std::size_t i_addr=0; i_addr<n_sample; ++i_addr) {
      result[i_addr].bytes[i_byte] = byte_vector[i_addr];
    }
  }

  return result;
}


std::vector<IpAddress> sample_network(const IpNetwork &network, unsigned int size) {
  unsigned int n_bits_sampled = network.max_prefix_length() - network.prefix_length();

  std::vector<IpAddress> result = sample_bits(network.is_ipv6(), n_bits_sampled, size);

  // shift addresses into network
  if (network.prefix_length() > 0) {
    std::transform(result.begin(), result.end(), result.begin(),
                   [&](IpAddress addr) { return bitwise_or(addr, network.address()); });
  }

  return result;
}


// [[Rcpp::export]]
List wrap_sample_network(List network_r, unsigned int size) {
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::vector<IpAddress> output;

  if (network.size() == 1 && !network[0].is_na()) {
    output = sample_network(network[0], size);
  }

  return encode_addresses(output);
}
