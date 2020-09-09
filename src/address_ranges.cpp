#include <Rcpp.h>
#include <ipaddress.h>

using namespace Rcpp;
using namespace ipaddress;


std::vector<IpNetwork> summarize_address_range(const IpAddress &addr1, const IpAddress &addr2) {
  std::vector<IpNetwork> result;

  if (addr1.is_na() || addr2.is_na() || (addr1.is_ipv6() != addr2.is_ipv6())) {
    result.push_back(IpNetwork::make_na());
    return result;
  }

  // range is covered by 1+ blocks
  IpAddress range_start = addr1 < addr2 ? addr1 : addr2;
  IpAddress range_end = addr1 > addr2 ? addr1 : addr2;
  IpAddress block_start = range_start;

  int max_prefix = addr1.n_bits();
  unsigned int i = 0;
  while (block_start <= range_end) {
    if (i++ % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    int prefix = max_prefix;
    if (block_start != range_end) {
      IpAddress diff_bits = bitwise_xor(block_start, range_end);

      prefix = max_prefix - std::min(
        count_trailing_zero_bits(block_start),
        std::max(
          max_prefix - count_leading_zero_bits(diff_bits) - 1,
          count_trailing_zero_bits(bitwise_not(diff_bits))
        )
      );
    }

    IpNetwork network(block_start, prefix);
    result.push_back(network);

    // advance to next block
    block_start = broadcast_address(network);
    block_start++;

    // if block ends on all-ones, then increment operator wraps around to all-zeros
    if (block_start <= range_start) break;
  }

  return result;
}


std::vector<std::pair<IpAddress, IpAddress> > collapse_ranges(std::vector<IpNetwork> &input) {
  std::vector<std::pair<IpAddress, IpAddress> > output;

  std::sort(input.begin(), input.end(), [](IpNetwork a, IpNetwork b) { return a.address() < b.address(); });

  if (input.size() > 0) {
    auto cur_start = input[0].address();
    auto cur_end = broadcast_address(input[0]);

    // sweep line algorithm
    for (std::size_t i=1; i<input.size(); ++i) {
      if (i % 10000 == 1) {
        Rcpp::checkUserInterrupt();
      }

      if (input[i].address() <= cur_end + 1) {
        auto next_end = broadcast_address(input[i]);
        if (next_end >= cur_end) {
          cur_end = next_end;
        }
      } else {
        output.push_back(std::pair<IpAddress, IpAddress>(cur_start, cur_end));

        cur_start = input[i].address();
        cur_end = broadcast_address(input[i]);
      }
    }

    output.push_back(std::pair<IpAddress, IpAddress>(cur_start, cur_end));
  }

  return output;
}


std::vector<IpNetwork> collapse_networks(std::vector<IpNetwork> &input) {
  if (input.size() == 0) {
    return std::vector<IpNetwork>();
  }
  if (input.size() == 1) {
    return input;
  }

  typedef std::pair<IpAddress, IpAddress> AddressRange;
  std::vector<AddressRange> ranges = collapse_ranges(input);

  std::vector<IpNetwork> output;
  for (std::size_t i=0; i<ranges.size(); ++i) {
    if (i % 10000 == 0) {
      Rcpp::checkUserInterrupt();
    }

    auto networks = summarize_address_range(ranges[i].first, ranges[i].second);
    std::copy(networks.begin(), networks.end(), std::back_inserter(output));
  }

  return output;
}


std::vector<IpNetwork> exclude_networks(std::vector<IpNetwork> &include, std::vector<IpNetwork> &exclude) {
  if (include.size() == 0) {
    return std::vector<IpNetwork>();
  }
  if (exclude.size() == 0) {
    return collapse_networks(include);
  }

  typedef std::pair<IpAddress, IpAddress> AddressRange;
  typedef std::pair<IpAddress, int> RangeBoundary;

  std::vector<AddressRange> include_ranges = collapse_ranges(include);
  std::vector<AddressRange> exclude_ranges = collapse_ranges(exclude);

  // fill annotated range boundaries
  // (1,2,3,4) -> (start include, end include, start exclude, end exclude)
  std::vector<RangeBoundary> boundaries;
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
  IpAddress output_range_start;
  std::vector<IpNetwork> output;

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
        // doesn't align with next exclude boundary
        if ((i == boundaries.size()-1) || (boundaries[i].first != boundaries[i+1].first)) {
          auto networks = summarize_address_range(output_range_start, boundaries[i].first);
          std::copy(networks.begin(), networks.end(), std::back_inserter(output));
        }
        // aligns with next exclude boundary
        else if (boundaries[i].first != output_range_start) {
          auto networks = summarize_address_range(output_range_start, boundaries[i].first - 1);
          std::copy(networks.begin(), networks.end(), std::back_inserter(output));
        }
      }
      is_include = false;
      break;
    case 3: // start exclude
      if (is_include) {
        // doesn't align with include boundary
        if (boundaries[i].first != output_range_start) {
          auto networks = summarize_address_range(output_range_start, boundaries[i].first - 1);
          std::copy(networks.begin(), networks.end(), std::back_inserter(output));
        }
      }
      is_exclude = true;
      break;
    case 4: // end exclude
      if (is_include) {
        output_range_start = (boundaries[i].first + 1);
      }
      is_exclude = false;
      break;
    }
  }

  return output;
}


// [[Rcpp::export]]
List wrap_summarize_address_range(List address1_r, List address2_r) {
  std::vector<IpAddress> address1 = decode_addresses(address1_r);
  std::vector<IpAddress> address2 = decode_addresses(address2_r);

  std::size_t vsize = address1.size();
  List outputs(vsize);

  if (address2.size() != vsize) {
    stop("Addresses must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    outputs[i] = encode_networks(summarize_address_range(address1[i], address2[i]));
  }

  return outputs;
}


// [[Rcpp::export]]
List wrap_collapse_networks(List input_r) {
  std::vector<IpNetwork> input = decode_networks(input_r);

  // extract networks (IPv4 & IPv6 handled independently)
  std::vector<IpNetwork> pre_collapse_v4;
  std::vector<IpNetwork> pre_collapse_v6;
  for (std::size_t i=0; i<input.size(); ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (input[i].is_na()) {
      // pass
    } else if (input[i].is_ipv6()) {
      pre_collapse_v6.push_back(input[i]);
    } else {
      pre_collapse_v4.push_back(input[i]);
    }
  }

  // collapse networks
  std::vector<IpNetwork> post_collapse_v4 = collapse_networks(pre_collapse_v4);
  std::vector<IpNetwork> post_collapse_v6 = collapse_networks(pre_collapse_v6);

  // fill output
  std::vector<IpNetwork> result;
  std::copy(post_collapse_v4.begin(), post_collapse_v4.end(), std::back_inserter(result));
  std::copy(post_collapse_v6.begin(), post_collapse_v6.end(), std::back_inserter(result));

  return encode_networks(result);
}


// [[Rcpp::export]]
List wrap_exclude_networks(List include_r, List exclude_r) {
  std::vector<IpNetwork> include = decode_networks(include_r);
  std::vector<IpNetwork> exclude = decode_networks(exclude_r);

  // extract include networks (IPv4 & IPv6 handled independently)
  std::vector<IpNetwork> include_v4;
  std::vector<IpNetwork> include_v6;
  for (std::size_t i=0; i<include.size(); ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (include[i].is_na()) {
      // pass
    } else if (include[i].is_ipv6()) {
      include_v6.push_back(include[i]);
    } else {
      include_v4.push_back(include[i]);
    }
  }

  // extract exclude networks (IPv4 & IPv6 handled independently)
  std::vector<IpNetwork> exclude_v4;
  std::vector<IpNetwork> exclude_v6;
  for (std::size_t i=0; i<exclude.size(); ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (exclude[i].is_na()) {
      // pass
    } else if (exclude[i].is_ipv6()) {
      exclude_v6.push_back(exclude[i]);
    } else {
      exclude_v4.push_back(exclude[i]);
    }
  }

  // exclude networks
  std::vector<IpNetwork> post_exclusion_v4 = exclude_networks(include_v4, exclude_v4);
  std::vector<IpNetwork> post_exclusion_v6 = exclude_networks(include_v6, exclude_v6);

  // fill output vectors
  std::vector<IpNetwork> result;
  std::copy(post_exclusion_v4.begin(), post_exclusion_v4.end(), std::back_inserter(result));
  std::copy(post_exclusion_v6.begin(), post_exclusion_v6.end(), std::back_inserter(result));

  return encode_networks(result);
}
