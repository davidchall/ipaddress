#include <Rcpp.h>
#include <ipaddress.h>

using namespace Rcpp;
using namespace ipaddress;


std::vector<IpAddress> sample_bits(bool is_ipv6, unsigned int n_bits_to_sample, unsigned int n_sample) {
  typedef typename IpAddress::bytes_type_both Bytes;
  std::vector<Bytes> result_bytes(n_sample, Bytes{});
  unsigned int n_bits_in_byte = 8;

  // fill bytes right to left
  unsigned int start_bit = is_ipv6 ? 0 : 12;
  for (std::size_t i=start_bit; i<sizeof(Bytes); ++i) {
    unsigned int ingest_bits = std::min(n_bits_to_sample, n_bits_in_byte);
    n_bits_to_sample -= ingest_bits;
    if (ingest_bits == 0) {
      break;
    }

    Rcpp::IntegerVector byte_vector = Rcpp::sample(1 << ingest_bits, n_sample, true, R_NilValue, false);

    for (std::size_t j=0; j<n_sample; ++j) {
      result_bytes[j][sizeof(Bytes)-1-i] = byte_vector[j];
    }
  }

  std::vector<IpAddress> result;
  result.reserve(n_sample);
  std::transform(result_bytes.begin(), result_bytes.end(), std::back_inserter(result),
                 [&](const Bytes &b) { return IpAddress(b, is_ipv6, false); });

  return result;
}


std::vector<IpAddress> sample_network(const IpNetwork &network, unsigned int size) {
  unsigned int max_prefix_length = network.address().n_bits();
  unsigned int n_bits_to_sample = max_prefix_length - network.prefix_length();

  std::vector<IpAddress> result = sample_bits(network.is_ipv6(), n_bits_to_sample, size);

  // shift addresses into network
  std::transform(result.begin(), result.end(), result.begin(),
                 [&](IpAddress addr) { return bitwise_or(addr, network.address()); });

  return result;
}


// [[Rcpp::export]]
List wrap_sample_network(List network_r, unsigned int size) {
  std::vector<IpNetwork> network = decode_networks(network_r);

  // initialize vectors
  std::vector<IpAddress> output;

  if (network.size() != 1 || network[0].is_na()) {
    // pass
  } else {
    output = sample_network(network[0], size);
  }

  return encode_addresses(output);
}
