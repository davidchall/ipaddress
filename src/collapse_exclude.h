#ifndef __IPADDRESS_COLLAPSE_EXCLUDE__
#define __IPADDRESS_COLLAPSE_EXCLUDE__

#include <vector>
#include <Rcpp.h>
#include <ipaddress/masking.h>
#include "iterative.h"


namespace ipaddress {

template<class Address, class Network>
std::vector<std::pair<Address, Address> > collapse_ranges(std::vector<Network> &input) {
  std::vector<std::pair<Address, Address> > output;

  std::sort(input.begin(), input.end(), [](Network a, Network b) { return a.address() < b.address(); });

  if (input.size() > 0) {
    auto cur_start = input[0].address();
    auto cur_end = broadcast_address<Address>(input[0]);

    // sweep line algorithm
    for (std::size_t i=1; i<input.size(); ++i) {
      if (i % 10000 == 1) {
        Rcpp::checkUserInterrupt();
      }

      if (input[i].address() <= advance_ip(cur_end, 1)) {
        auto next_end = broadcast_address<Address>(input[i]);
        if (next_end >= cur_end) {
          cur_end = next_end;
        }
      } else {
        output.push_back(std::pair<Address, Address>(cur_start, cur_end));

        cur_start = input[i].address();
        cur_end = broadcast_address<Address>(input[i]);
      }
    }

    output.push_back(std::pair<Address, Address>(cur_start, cur_end));
  }

  return output;
}

template<class Network>
std::vector<Network> collapse_networks(std::vector<Network> &input) {
  if (input.size() == 0) {
    return std::vector<Network>();
  }

  typedef decltype(input[0].address()) Address;
  typedef std::pair<Address, Address> AddressRange;
  std::vector<AddressRange> ranges = collapse_ranges<Address>(input);

  std::vector<Network> output;
  for (std::size_t i=0; i<ranges.size(); ++i) {
    if (i % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    auto networks = summarize_address_range<Network>(ranges[i].first, ranges[i].second);
    std::copy(networks.begin(), networks.end(), std::back_inserter(output));
  }

  return output;
}


template<class Network>
std::vector<Network> exclude_networks(std::vector<Network> &include, std::vector<Network> &exclude) {
  if (include.size() == 0) {
    return std::vector<Network>();
  }
  if (exclude.size() == 0) {
    return collapse_networks(include);
  }

  typedef decltype(include[0].address()) Address;
  typedef std::pair<Address, Address> AddressRange;
  typedef std::pair<Address, int> RangeBoundary;

  std::vector<AddressRange > include_ranges = collapse_ranges<Address>(include);
  std::vector<AddressRange > exclude_ranges = collapse_ranges<Address>(exclude);

  // fill annotated range boundaries
  // (1,2,3,4) -> (start include, end include, start exclude, end exclude)
  std::vector<RangeBoundary > boundaries;
  std::transform(include_ranges.begin(), include_ranges.end(), std::back_inserter(boundaries),
                 [](AddressRange range) { return RangeBoundary(range.first, 1); });
  std::transform(include_ranges.begin(), include_ranges.end(), std::back_inserter(boundaries),
                 [](AddressRange range) { return RangeBoundary(range.second, 2); });
  std::transform(exclude_ranges.begin(), exclude_ranges.end(), std::back_inserter(boundaries),
                 [](AddressRange range) { return RangeBoundary(range.first, 3); });
  std::transform(exclude_ranges.begin(), exclude_ranges.end(), std::back_inserter(boundaries),
                 [](AddressRange range) { return RangeBoundary(range.second, 4); });

  // sort boundaries with ties keeping annotation order
  std::stable_sort(boundaries.begin(), boundaries.end(),
                   [](RangeBoundary a, RangeBoundary b) { return a.first < b.first; });

  // sweep line algorithm
  bool is_include = false;
  bool is_exclude = false;
  Address output_range_start;
  std::vector<Network> output;

  for (std::size_t i=0; i<boundaries.size(); ++i) {
    if (i % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    switch (boundaries[i].second) {
    case 1: // start include
      if (!is_exclude) {
        output_range_start = boundaries[i].first;
      }
      is_include = true;
      break;
    case 2: // end include
      if (!is_exclude) {
        // check this doesn't align with an exclude boundary
        if ((i == boundaries.size()-1) || (boundaries[i].first != boundaries[i+1].first)) {
          auto networks = summarize_address_range<Network>(output_range_start, boundaries[i].first);
          std::copy(networks.begin(), networks.end(), std::back_inserter(output));
        } else if (boundaries[i].first != output_range_start) {
          auto networks = summarize_address_range<Network>(output_range_start, advance_ip(boundaries[i].first, -1));
          std::copy(networks.begin(), networks.end(), std::back_inserter(output));
        }
      }
      is_include = false;
      break;
    case 3: // start exclude
      if (is_include) {
        auto networks = summarize_address_range<Network>(output_range_start, advance_ip(boundaries[i].first, -1));
        std::copy(networks.begin(), networks.end(), std::back_inserter(output));
      }
      is_exclude = true;
      break;
    case 4: // end exclude
      if (is_include) {
        output_range_start = advance_ip(boundaries[i].first, 1);
      }
      is_exclude = false;
      break;
    }
  }

  return output;
}

}

#endif
