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
// parse_network_wrapper
List parse_network_wrapper(CharacterVector x, LogicalVector strict);
RcppExport SEXP _ipaddress_parse_network_wrapper(SEXP xSEXP, SEXP strictSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< LogicalVector >::type strict(strictSEXP);
    rcpp_result_gen = Rcpp::wrap(parse_network_wrapper(x, strict));
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
// netmask_wrapper
List netmask_wrapper(List x);
RcppExport SEXP _ipaddress_netmask_wrapper(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(netmask_wrapper(x));
    return rcpp_result_gen;
END_RCPP
}
// hostmask_wrapper
List hostmask_wrapper(List x);
RcppExport SEXP _ipaddress_hostmask_wrapper(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(hostmask_wrapper(x));
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

static const R_CallMethodDef CallEntries[] = {
    {"_ipaddress_parse_address_wrapper", (DL_FUNC) &_ipaddress_parse_address_wrapper, 1},
    {"_ipaddress_print_address_wrapper", (DL_FUNC) &_ipaddress_print_address_wrapper, 1},
    {"_ipaddress_parse_network_wrapper", (DL_FUNC) &_ipaddress_parse_network_wrapper, 2},
    {"_ipaddress_print_network_wrapper", (DL_FUNC) &_ipaddress_print_network_wrapper, 1},
    {"_ipaddress_compare_address_wrapper", (DL_FUNC) &_ipaddress_compare_address_wrapper, 1},
    {"_ipaddress_netmask_wrapper", (DL_FUNC) &_ipaddress_netmask_wrapper, 1},
    {"_ipaddress_hostmask_wrapper", (DL_FUNC) &_ipaddress_hostmask_wrapper, 1},
    {"_ipaddress_is_within_wrapper", (DL_FUNC) &_ipaddress_is_within_wrapper, 2},
    {"_ipaddress_is_within_any_wrapper", (DL_FUNC) &_ipaddress_is_within_any_wrapper, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_ipaddress(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
