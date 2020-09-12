#include <Rcpp.h>
#include <ipaddress.h>
#include <ipaddress/to_string.h>
#include "warn.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_bitwise_not(List lhs_r) {
  std::vector<IpAddress> lhs = decode_addresses(lhs_r);

  // initialize vectors
  std::size_t vsize = lhs.size();
  std::vector<IpAddress> result(vsize);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    result[i] = bitwise_not(lhs[i]);
  }

  return encode_addresses(result);
}

// [[Rcpp::export]]
List wrap_bitwise_and(List lhs_r, List rhs_r) {
  std::vector<IpAddress> lhs = decode_addresses(lhs_r);
  std::vector<IpAddress> rhs = decode_addresses(rhs_r);

  // initialize vectors
  std::size_t vsize = lhs.size();
  std::vector<IpAddress> result(vsize);

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    result[i] = bitwise_and(lhs[i], rhs[i]);
  }

  return encode_addresses(result);
}

// [[Rcpp::export]]
List wrap_bitwise_or(List lhs_r, List rhs_r) {
  std::vector<IpAddress> lhs = decode_addresses(lhs_r);
  std::vector<IpAddress> rhs = decode_addresses(rhs_r);

  // initialize vectors
  std::size_t vsize = lhs.size();
  std::vector<IpAddress> result(vsize);

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    result[i] = bitwise_or(lhs[i], rhs[i]);
  }

  return encode_addresses(result);
}

// [[Rcpp::export]]
List wrap_bitwise_xor(List lhs_r, List rhs_r) {
  std::vector<IpAddress> lhs = decode_addresses(lhs_r);
  std::vector<IpAddress> rhs = decode_addresses(rhs_r);

  // initialize vectors
  std::size_t vsize = lhs.size();
  std::vector<IpAddress> result(vsize);

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    result[i] = bitwise_xor(lhs[i], rhs[i]);
  }

  return encode_addresses(result);
}

// [[Rcpp::export]]
List wrap_bitwise_shift_left(List lhs_r, IntegerVector rhs) {
  std::vector<IpAddress> lhs = decode_addresses(lhs_r);

  // initialize vectors
  std::size_t vsize = lhs.size();
  std::vector<IpAddress> result(vsize);

  if (static_cast<std::size_t>(rhs.size()) != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (rhs[i] == NA_INTEGER) {
      result[i] = IpAddress::make_na();
    } else {
      result[i] = bitwise_shift_left(lhs[i], rhs[i]);
    }
  }

  return encode_addresses(result);
}

// [[Rcpp::export]]
List wrap_bitwise_shift_right(List lhs_r, IntegerVector rhs) {
  std::vector<IpAddress> lhs = decode_addresses(lhs_r);

  // initialize vectors
  std::size_t vsize = lhs.size();
  std::vector<IpAddress> result(vsize);

  if (static_cast<std::size_t>(rhs.size()) != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (rhs[i] == NA_INTEGER) {
      result[i] = IpAddress::make_na();
    } else {
      result[i] = bitwise_shift_right(lhs[i], rhs[i]);
    }
  }

  return encode_addresses(result);
}

// [[Rcpp::export]]
List wrap_add_integer(List lhs_r, IntegerVector rhs) {
  std::vector<IpAddress> lhs = decode_addresses(lhs_r);

  // initialize vectors
  std::size_t vsize = lhs.size();
  std::vector<IpAddress> output(vsize);

  if (static_cast<std::size_t>(rhs.size()) != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs[i].is_na() || rhs[i] == NA_INTEGER) {
      output[i] = IpAddress::make_na();
    } else {
      output[i] = lhs[i] + rhs[i];

      if (output[i].is_na() && rhs[i] > 0) {
        warnOnRow(i, to_string(lhs[i]) + " + " + std::to_string(rhs[i]), "out-of-range");
      } else if (output[i].is_na() && rhs[i] < 0) {
        warnOnRow(i, to_string(lhs[i]) + " - " + std::to_string(-rhs[i]), "out-of-range");
      }
    }
  }

  return encode_addresses(output);
}
