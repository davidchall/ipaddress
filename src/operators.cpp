#include <Rcpp.h>
#include <ipaddress.h>
#include "iterative.h"

using namespace Rcpp;
using namespace ipaddress;


// [[Rcpp::export]]
List wrap_bitwise_not(List lhs_r) {
  IpAddressVector lhs(lhs_r);
  std::size_t vsize = lhs.size();

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs.is_na[i]) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i]) {
      out_address_v6[i] = bitwise_not(lhs.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_not(lhs.address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_and(List lhs_r, List rhs_r) {
  IpAddressVector lhs(lhs_r);
  IpAddressVector rhs(rhs_r);

  std::size_t vsize = lhs.size();

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs.is_na[i] || rhs.is_na[i]) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i] != rhs.is_ipv6[i]) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i]) {
      out_address_v6[i] = bitwise_and(lhs.address_v6[i], rhs.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_and(lhs.address_v4[i], rhs.address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_or(List lhs_r, List rhs_r) {
  IpAddressVector lhs(lhs_r);
  IpAddressVector rhs(rhs_r);

  std::size_t vsize = lhs.size();

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs.is_na[i] || rhs.is_na[i]) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i] != rhs.is_ipv6[i]) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i]) {
      out_address_v6[i] = bitwise_or(lhs.address_v6[i], rhs.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_or(lhs.address_v4[i], rhs.address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_xor(List lhs_r, List rhs_r) {
  IpAddressVector lhs(lhs_r);
  IpAddressVector rhs(rhs_r);

  std::size_t vsize = lhs.size();

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs.is_na[i] || rhs.is_na[i]) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i] != rhs.is_ipv6[i]) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i]) {
      out_address_v6[i] = bitwise_xor(lhs.address_v6[i], rhs.address_v6[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_xor(lhs.address_v4[i], rhs.address_v4[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_shift_left(List lhs_r, IntegerVector rhs) {
  IpAddressVector lhs(lhs_r);

  std::size_t vsize = lhs.size();

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs.is_na[i] || rhs[i] == NA_INTEGER) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i]) {
      out_address_v6[i] = bitwise_shift_left(lhs.address_v6[i], rhs[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_shift_left(lhs.address_v4[i], rhs[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_bitwise_shift_right(List lhs_r, IntegerVector rhs) {
  IpAddressVector lhs(lhs_r);

  std::size_t vsize = lhs.size();

  if (rhs.size() != vsize) {
    stop("Inputs must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs.is_na[i] || rhs[i] == NA_INTEGER) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i]) {
      out_address_v6[i] = bitwise_shift_right(lhs.address_v6[i], rhs[i]);
      out_is_ipv6[i] = true;
    } else {
      out_address_v4[i] = bitwise_shift_right(lhs.address_v4[i], rhs[i]);
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}

// [[Rcpp::export]]
List wrap_add_integer(List lhs_r, IntegerVector rhs) {
  IpAddressVector lhs(lhs_r);

  std::size_t vsize = lhs.size();

  if (rhs.size() != static_cast<R_xlen_t>(vsize)) {
    stop("Inputs must have same length"); // # nocov
  }

  // initialize vectors
  std::vector<asio::ip::address_v4> out_address_v4(vsize);
  std::vector<asio::ip::address_v6> out_address_v6(vsize);
  std::vector<bool> out_is_ipv6(vsize, false);
  std::vector<bool> out_is_na(vsize, false);

  for (std::size_t i=0; i<vsize; ++i) {
    if (i % 10000 == 0) {
      checkUserInterrupt();
    }

    if (lhs.is_na[i] || rhs[i] == NA_INTEGER) {
      out_is_na[i] = true;
    } else if (lhs.is_ipv6[i]) {
      asio::ip::address_v6 tmp_addr = advance_ip(lhs.address_v6[i], rhs[i]);

      if (rhs[i] > 0 && tmp_addr < lhs.address_v6[i]) {
        out_is_na[i] = true;
        warnOnRow(i, lhs.address_v6[i].to_string() + " + " + std::to_string(rhs[i]), "out-of-range");
      } else if (rhs[i] < 0 && tmp_addr > lhs.address_v6[i]) {
        out_is_na[i] = true;
        warnOnRow(i, lhs.address_v6[i].to_string() + " - " + std::to_string(-rhs[i]), "out-of-range");
      } else {
        out_address_v6[i] = tmp_addr;
        out_is_ipv6[i] = true;
      }
    } else {
      asio::ip::address_v4 tmp_addr = advance_ip(lhs.address_v4[i], rhs[i]);

      if (rhs[i] > 0 && tmp_addr < lhs.address_v4[i]) {
        out_is_na[i] = true;
        warnOnRow(i, lhs.address_v4[i].to_string() + " + " + std::to_string(rhs[i]), "out-of-range");
      } else if (rhs[i] < 0 && tmp_addr > lhs.address_v4[i]) {
        out_is_na[i] = true;
        warnOnRow(i, lhs.address_v4[i].to_string() + " - " + std::to_string(-rhs[i]), "out-of-range");
      } else {
        out_address_v4[i] = tmp_addr;
      }
    }
  }

  return IpAddressVector(out_address_v4, out_address_v6, out_is_ipv6, out_is_na).encodeR();
}
