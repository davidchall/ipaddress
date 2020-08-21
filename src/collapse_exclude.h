#ifndef __IPADDRESS_COLLAPSE_EXCLUDE__
#define __IPADDRESS_COLLAPSE_EXCLUDE__

#include <vector>
#include <Rcpp.h>
#include <ipaddress/masking.h>
#include "iterative.h"


namespace ipaddress {

template<class Network>
std::vector<Network> collapse(std::vector<Network> &input) {
  std::vector<Network> output;

  std::sort(input.begin(), input.end(), [](Network a, Network b) { return a.address() < b.address(); });

  if (input.size() > 0) {
    typedef typeof(input[0].address()) Address;

    auto cur_start = input[0].address();
    auto cur_end = broadcast_address<Address>(input[0]);

    for (std::size_t i=1; i<input.size(); ++i) {
      if (i % 10000 == 0) {
        Rcpp::checkUserInterrupt();
      }

      if (input[i].address() <= advance_ip(cur_end, 1)) {
        auto next_end = broadcast_address<Address>(input[i]);
        if (next_end >= cur_end) {
          cur_end = next_end;
        }
      } else {
        auto networks = summarize_address_range<Network>(cur_start, cur_end);
        std::copy(networks.begin(), networks.end(), std::back_inserter(output));

        cur_start = input[i].address();
        cur_end = broadcast_address<Address>(input[i]);
      }
    }

    auto networks = summarize_address_range<Network>(cur_start, cur_end);
    std::copy(networks.begin(), networks.end(), std::back_inserter(output));
  }

  return output;
}


template<class Network>
std::vector<Network> exclude(std::vector<Network> &input, std::vector<Network> &exclude) {
  std::vector<Network> output;

  std::sort(input.begin(), input.end(), [](Network a, Network b) { return a.address() < b.address(); });
  std::sort(exclude.begin(), exclude.end(), [](Network a, Network b) { return a.address() < b.address(); });

  if (input.size() > 0) {
    typedef typeof(input[0].address()) Address;

    auto cur_start = input[0].address();
    auto cur_end = broadcast_address<Address>(input[0]);

    bool is_finished = false;
    bool is_processing_exclude = false;
    std::size_t i_input = 1;
    std::size_t i_exclude = 0;
  }

  return output;
}

}

#endif
