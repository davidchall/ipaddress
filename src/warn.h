#ifndef __IPADDRESS_WARN__
#define __IPADDRESS_WARN__

#include <Rcpp.h>


namespace ipaddress {

inline void warnOnRow(unsigned int index, const std::string &input, const std::string &reason = "") {
  // Indexes are 1-based in R
  std::string msg = "Problem on row " + std::to_string(index + 1) + ": " + input;
  if (!reason.empty()) {
    msg += " (" + reason + ")";
  }

  Rf_warningcall(R_NilValue, msg.c_str());
}

}

#endif
