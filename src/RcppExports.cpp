// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// parse_address_wrapper
List parse_address_wrapper(CharacterVector x);
RcppExport SEXP _ipaddress_parse_address_wrapper(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(parse_address_wrapper(x));
    return rcpp_result_gen;
END_RCPP
}
// print_address_wrapper
CharacterVector print_address_wrapper(List x);
RcppExport SEXP _ipaddress_print_address_wrapper(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(print_address_wrapper(x));
    return rcpp_result_gen;
END_RCPP
}
// blob_address_wrapper
List blob_address_wrapper(List x);
RcppExport SEXP _ipaddress_blob_address_wrapper(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(blob_address_wrapper(x));
    return rcpp_result_gen;
END_RCPP
}
// parse_network_wrapper
List parse_network_wrapper(CharacterVector x, bool strict);
RcppExport SEXP _ipaddress_parse_network_wrapper(SEXP xSEXP, SEXP strictSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type strict(strictSEXP);
    rcpp_result_gen = Rcpp::wrap(parse_network_wrapper(x, strict));
    return rcpp_result_gen;
END_RCPP
}
// construct_network_wrapper
List construct_network_wrapper(List address, IntegerVector prefix_length, bool strict);
RcppExport SEXP _ipaddress_construct_network_wrapper(SEXP addressSEXP, SEXP prefix_lengthSEXP, SEXP strictSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address(addressSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    Rcpp::traits::input_parameter< bool >::type strict(strictSEXP);
    rcpp_result_gen = Rcpp::wrap(construct_network_wrapper(address, prefix_length, strict));
    return rcpp_result_gen;
END_RCPP
}
// print_network_wrapper
CharacterVector print_network_wrapper(List x);
RcppExport SEXP _ipaddress_print_network_wrapper(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(print_network_wrapper(x));
    return rcpp_result_gen;
END_RCPP
}
// compare_address_wrapper
DataFrame compare_address_wrapper(List x);
RcppExport SEXP _ipaddress_compare_address_wrapper(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(compare_address_wrapper(x));
    return rcpp_result_gen;
END_RCPP
}
// bitwise_and_wrapper
List bitwise_and_wrapper(List addr1, List addr2);
RcppExport SEXP _ipaddress_bitwise_and_wrapper(SEXP addr1SEXP, SEXP addr2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type addr1(addr1SEXP);
    Rcpp::traits::input_parameter< List >::type addr2(addr2SEXP);
    rcpp_result_gen = Rcpp::wrap(bitwise_and_wrapper(addr1, addr2));
    return rcpp_result_gen;
END_RCPP
}
// bitwise_or_wrapper
List bitwise_or_wrapper(List addr1, List addr2);
RcppExport SEXP _ipaddress_bitwise_or_wrapper(SEXP addr1SEXP, SEXP addr2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type addr1(addr1SEXP);
    Rcpp::traits::input_parameter< List >::type addr2(addr2SEXP);
    rcpp_result_gen = Rcpp::wrap(bitwise_or_wrapper(addr1, addr2));
    return rcpp_result_gen;
END_RCPP
}
// bitwise_not_wrapper
List bitwise_not_wrapper(List addr1);
RcppExport SEXP _ipaddress_bitwise_not_wrapper(SEXP addr1SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type addr1(addr1SEXP);
    rcpp_result_gen = Rcpp::wrap(bitwise_not_wrapper(addr1));
    return rcpp_result_gen;
END_RCPP
}
// netmask_wrapper
List netmask_wrapper(IntegerVector prefix_length, LogicalVector is_ipv6);
RcppExport SEXP _ipaddress_netmask_wrapper(SEXP prefix_lengthSEXP, SEXP is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    Rcpp::traits::input_parameter< LogicalVector >::type is_ipv6(is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(netmask_wrapper(prefix_length, is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// hostmask_wrapper
List hostmask_wrapper(IntegerVector prefix_length, LogicalVector is_ipv6);
RcppExport SEXP _ipaddress_hostmask_wrapper(SEXP prefix_lengthSEXP, SEXP is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    Rcpp::traits::input_parameter< LogicalVector >::type is_ipv6(is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(hostmask_wrapper(prefix_length, is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// broadcast_address_wrapper
List broadcast_address_wrapper(List network_r);
RcppExport SEXP _ipaddress_broadcast_address_wrapper(SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(broadcast_address_wrapper(network_r));
    return rcpp_result_gen;
END_RCPP
}
// hosts_wrapper
List hosts_wrapper(List network_r, bool exclude_unusable);
RcppExport SEXP _ipaddress_hosts_wrapper(SEXP network_rSEXP, SEXP exclude_unusableSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    Rcpp::traits::input_parameter< bool >::type exclude_unusable(exclude_unusableSEXP);
    rcpp_result_gen = Rcpp::wrap(hosts_wrapper(network_r, exclude_unusable));
    return rcpp_result_gen;
END_RCPP
}
// is_within_wrapper
LogicalVector is_within_wrapper(List address_r, List network_r);
RcppExport SEXP _ipaddress_is_within_wrapper(SEXP address_rSEXP, SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_within_wrapper(address_r, network_r));
    return rcpp_result_gen;
END_RCPP
}
// is_within_any_wrapper
LogicalVector is_within_any_wrapper(List address_r, List network_r);
RcppExport SEXP _ipaddress_is_within_any_wrapper(SEXP address_rSEXP, SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_within_any_wrapper(address_r, network_r));
    return rcpp_result_gen;
END_RCPP
}
// is_multicast_address_wrapper
LogicalVector is_multicast_address_wrapper(List address_r);
RcppExport SEXP _ipaddress_is_multicast_address_wrapper(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_multicast_address_wrapper(address_r));
    return rcpp_result_gen;
END_RCPP
}
// is_multicast_network_wrapper
LogicalVector is_multicast_network_wrapper(List network_r);
RcppExport SEXP _ipaddress_is_multicast_network_wrapper(SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_multicast_network_wrapper(network_r));
    return rcpp_result_gen;
END_RCPP
}
// is_unspecified_address_wrapper
LogicalVector is_unspecified_address_wrapper(List address_r);
RcppExport SEXP _ipaddress_is_unspecified_address_wrapper(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_unspecified_address_wrapper(address_r));
    return rcpp_result_gen;
END_RCPP
}
// is_unspecified_network_wrapper
LogicalVector is_unspecified_network_wrapper(List network_r);
RcppExport SEXP _ipaddress_is_unspecified_network_wrapper(SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_unspecified_network_wrapper(network_r));
    return rcpp_result_gen;
END_RCPP
}
// is_loopback_address_wrapper
LogicalVector is_loopback_address_wrapper(List address_r);
RcppExport SEXP _ipaddress_is_loopback_address_wrapper(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_loopback_address_wrapper(address_r));
    return rcpp_result_gen;
END_RCPP
}
// is_loopback_network_wrapper
LogicalVector is_loopback_network_wrapper(List network_r);
RcppExport SEXP _ipaddress_is_loopback_network_wrapper(SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_loopback_network_wrapper(network_r));
    return rcpp_result_gen;
END_RCPP
}
// is_link_local_address_wrapper
LogicalVector is_link_local_address_wrapper(List address_r);
RcppExport SEXP _ipaddress_is_link_local_address_wrapper(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_link_local_address_wrapper(address_r));
    return rcpp_result_gen;
END_RCPP
}
// is_link_local_network_wrapper
LogicalVector is_link_local_network_wrapper(List network_r);
RcppExport SEXP _ipaddress_is_link_local_network_wrapper(SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(is_link_local_network_wrapper(network_r));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ipaddress_parse_address_wrapper", (DL_FUNC) &_ipaddress_parse_address_wrapper, 1},
    {"_ipaddress_print_address_wrapper", (DL_FUNC) &_ipaddress_print_address_wrapper, 1},
    {"_ipaddress_blob_address_wrapper", (DL_FUNC) &_ipaddress_blob_address_wrapper, 1},
    {"_ipaddress_parse_network_wrapper", (DL_FUNC) &_ipaddress_parse_network_wrapper, 2},
    {"_ipaddress_construct_network_wrapper", (DL_FUNC) &_ipaddress_construct_network_wrapper, 3},
    {"_ipaddress_print_network_wrapper", (DL_FUNC) &_ipaddress_print_network_wrapper, 1},
    {"_ipaddress_compare_address_wrapper", (DL_FUNC) &_ipaddress_compare_address_wrapper, 1},
    {"_ipaddress_bitwise_and_wrapper", (DL_FUNC) &_ipaddress_bitwise_and_wrapper, 2},
    {"_ipaddress_bitwise_or_wrapper", (DL_FUNC) &_ipaddress_bitwise_or_wrapper, 2},
    {"_ipaddress_bitwise_not_wrapper", (DL_FUNC) &_ipaddress_bitwise_not_wrapper, 1},
    {"_ipaddress_netmask_wrapper", (DL_FUNC) &_ipaddress_netmask_wrapper, 2},
    {"_ipaddress_hostmask_wrapper", (DL_FUNC) &_ipaddress_hostmask_wrapper, 2},
    {"_ipaddress_broadcast_address_wrapper", (DL_FUNC) &_ipaddress_broadcast_address_wrapper, 1},
    {"_ipaddress_hosts_wrapper", (DL_FUNC) &_ipaddress_hosts_wrapper, 2},
    {"_ipaddress_is_within_wrapper", (DL_FUNC) &_ipaddress_is_within_wrapper, 2},
    {"_ipaddress_is_within_any_wrapper", (DL_FUNC) &_ipaddress_is_within_any_wrapper, 2},
    {"_ipaddress_is_multicast_address_wrapper", (DL_FUNC) &_ipaddress_is_multicast_address_wrapper, 1},
    {"_ipaddress_is_multicast_network_wrapper", (DL_FUNC) &_ipaddress_is_multicast_network_wrapper, 1},
    {"_ipaddress_is_unspecified_address_wrapper", (DL_FUNC) &_ipaddress_is_unspecified_address_wrapper, 1},
    {"_ipaddress_is_unspecified_network_wrapper", (DL_FUNC) &_ipaddress_is_unspecified_network_wrapper, 1},
    {"_ipaddress_is_loopback_address_wrapper", (DL_FUNC) &_ipaddress_is_loopback_address_wrapper, 1},
    {"_ipaddress_is_loopback_network_wrapper", (DL_FUNC) &_ipaddress_is_loopback_network_wrapper, 1},
    {"_ipaddress_is_link_local_address_wrapper", (DL_FUNC) &_ipaddress_is_link_local_address_wrapper, 1},
    {"_ipaddress_is_link_local_network_wrapper", (DL_FUNC) &_ipaddress_is_link_local_network_wrapper, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_ipaddress(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
