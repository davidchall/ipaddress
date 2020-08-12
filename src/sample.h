#ifndef __IPADDRESS_SAMPLE__
#define __IPADDRESS_SAMPLE__

#include <algorithm>
#include <Rcpp.h>
#include <ipaddress/masking.h>


namespace ipaddress {

template<class Address>
std::vector<Address> sample_bits(unsigned int n_bits_to_sample, unsigned int n_sample) {
  typedef typename Address::bytes_type Bytes;
  std::vector<Bytes> result_bytes(n_sample);
  unsigned int n_bits_in_byte = 8;

  // fill bytes right to left
  for (std::size_t i=0; i<sizeof(Bytes); ++i) {
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

  std::vector<Address> result;
  result.reserve(n_sample);
  std::transform(result_bytes.begin(), result_bytes.end(), std::back_inserter(result),
                 [](const Bytes &b) { return Address(b); });

  return result;
}

template<class Address, class Network>
std::vector<Address> sample_network(const Network &network, unsigned int size) {
  unsigned int n_bytes = sizeof(network.address().to_bytes());
  unsigned int max_prefix_length = 8 * n_bytes;
  unsigned int n_bits_to_sample = max_prefix_length - network.prefix_length();

  std::vector<Address> result = sample_bits<Address>(n_bits_to_sample, size);

  // shift addresses into network
  std::transform(result.begin(), result.end(), result.begin(),
                 [&](Address addr) { return bitwise_or(addr, network.address()); });

  return result;
}

}

#endif
