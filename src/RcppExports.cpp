// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// wrap_parse_address
List wrap_parse_address(CharacterVector x);
RcppExport SEXP _ipaddress_wrap_parse_address(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_parse_address(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_print_address
CharacterVector wrap_print_address(List x);
RcppExport SEXP _ipaddress_wrap_print_address(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_print_address(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_packed
List wrap_encode_packed(List x);
RcppExport SEXP _ipaddress_wrap_encode_packed(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_packed(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_packed
List wrap_decode_packed(List x);
RcppExport SEXP _ipaddress_wrap_decode_packed(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_packed(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_integer
CharacterVector wrap_encode_integer(List x);
RcppExport SEXP _ipaddress_wrap_encode_integer(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_integer(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_integer
List wrap_decode_integer(CharacterVector x, Nullable<LogicalVector> is_ipv6);
RcppExport SEXP _ipaddress_wrap_decode_integer(SEXP xSEXP, SEXP is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< Nullable<LogicalVector> >::type is_ipv6(is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_integer(x, is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_binary
CharacterVector wrap_encode_binary(List x);
RcppExport SEXP _ipaddress_wrap_encode_binary(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_binary(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_binary
List wrap_decode_binary(CharacterVector x);
RcppExport SEXP _ipaddress_wrap_decode_binary(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_binary(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_hostname
List wrap_encode_hostname(List x);
RcppExport SEXP _ipaddress_wrap_encode_hostname(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_hostname(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_hostname
List wrap_decode_hostname(CharacterVector x);
RcppExport SEXP _ipaddress_wrap_decode_hostname(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_hostname(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_parse_network
List wrap_parse_network(CharacterVector x, bool strict);
RcppExport SEXP _ipaddress_wrap_parse_network(SEXP xSEXP, SEXP strictSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type strict(strictSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_parse_network(x, strict));
    return rcpp_result_gen;
END_RCPP
}
// wrap_construct_network_from_address
List wrap_construct_network_from_address(List address, IntegerVector prefix_length, bool strict);
RcppExport SEXP _ipaddress_wrap_construct_network_from_address(SEXP addressSEXP, SEXP prefix_lengthSEXP, SEXP strictSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address(addressSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    Rcpp::traits::input_parameter< bool >::type strict(strictSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_construct_network_from_address(address, prefix_length, strict));
    return rcpp_result_gen;
END_RCPP
}
// wrap_print_network
CharacterVector wrap_print_network(List x);
RcppExport SEXP _ipaddress_wrap_print_network(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_print_network(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_parse_interface
List wrap_parse_interface(CharacterVector x);
RcppExport SEXP _ipaddress_wrap_parse_interface(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_parse_interface(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_construct_interface_from_address
List wrap_construct_interface_from_address(List address, IntegerVector prefix_length);
RcppExport SEXP _ipaddress_wrap_construct_interface_from_address(SEXP addressSEXP, SEXP prefix_lengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address(addressSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_construct_interface_from_address(address, prefix_length));
    return rcpp_result_gen;
END_RCPP
}
// wrap_compare_address
DataFrame wrap_compare_address(List x);
RcppExport SEXP _ipaddress_wrap_compare_address(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_compare_address(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_network_hosts
List wrap_network_hosts(List network_r, bool exclude_unusable);
RcppExport SEXP _ipaddress_wrap_network_hosts(SEXP network_rSEXP, SEXP exclude_unusableSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    Rcpp::traits::input_parameter< bool >::type exclude_unusable(exclude_unusableSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_network_hosts(network_r, exclude_unusable));
    return rcpp_result_gen;
END_RCPP
}
// wrap_sample_network
List wrap_sample_network(List network_r, unsigned int size);
RcppExport SEXP _ipaddress_wrap_sample_network(SEXP network_rSEXP, SEXP sizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type size(sizeSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_sample_network(network_r, size));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_not
List wrap_bitwise_not(List lhs);
RcppExport SEXP _ipaddress_wrap_bitwise_not(SEXP lhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs(lhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_not(lhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_and
List wrap_bitwise_and(List lhs, List rhs);
RcppExport SEXP _ipaddress_wrap_bitwise_and(SEXP lhsSEXP, SEXP rhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs(lhsSEXP);
    Rcpp::traits::input_parameter< List >::type rhs(rhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_and(lhs, rhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_or
List wrap_bitwise_or(List lhs, List rhs);
RcppExport SEXP _ipaddress_wrap_bitwise_or(SEXP lhsSEXP, SEXP rhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs(lhsSEXP);
    Rcpp::traits::input_parameter< List >::type rhs(rhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_or(lhs, rhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_xor
List wrap_bitwise_xor(List lhs, List rhs);
RcppExport SEXP _ipaddress_wrap_bitwise_xor(SEXP lhsSEXP, SEXP rhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs(lhsSEXP);
    Rcpp::traits::input_parameter< List >::type rhs(rhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_xor(lhs, rhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_add_integer
List wrap_add_integer(List lhs, IntegerVector rhs);
RcppExport SEXP _ipaddress_wrap_add_integer(SEXP lhsSEXP, SEXP rhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs(lhsSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type rhs(rhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_add_integer(lhs, rhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_netmask
List wrap_netmask(IntegerVector prefix_length, LogicalVector is_ipv6);
RcppExport SEXP _ipaddress_wrap_netmask(SEXP prefix_lengthSEXP, SEXP is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    Rcpp::traits::input_parameter< LogicalVector >::type is_ipv6(is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_netmask(prefix_length, is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// wrap_hostmask
List wrap_hostmask(IntegerVector prefix_length, LogicalVector is_ipv6);
RcppExport SEXP _ipaddress_wrap_hostmask(SEXP prefix_lengthSEXP, SEXP is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    Rcpp::traits::input_parameter< LogicalVector >::type is_ipv6(is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_hostmask(prefix_length, is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// wrap_broadcast_address
List wrap_broadcast_address(List network_r);
RcppExport SEXP _ipaddress_wrap_broadcast_address(SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_broadcast_address(network_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_within
LogicalVector wrap_is_within(List address_r, List network_r);
RcppExport SEXP _ipaddress_wrap_is_within(SEXP address_rSEXP, SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_within(address_r, network_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_within_any
LogicalVector wrap_is_within_any(List address_r, List network_r);
RcppExport SEXP _ipaddress_wrap_is_within_any(SEXP address_rSEXP, SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_within_any(address_r, network_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_multicast
LogicalVector wrap_is_multicast(List x);
RcppExport SEXP _ipaddress_wrap_is_multicast(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_multicast(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_unspecified
LogicalVector wrap_is_unspecified(List x);
RcppExport SEXP _ipaddress_wrap_is_unspecified(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_unspecified(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_loopback
LogicalVector wrap_is_loopback(List x);
RcppExport SEXP _ipaddress_wrap_is_loopback(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_loopback(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_link_local
LogicalVector wrap_is_link_local(List x);
RcppExport SEXP _ipaddress_wrap_is_link_local(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_link_local(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_ipv4_mapped
LogicalVector wrap_is_ipv4_mapped(List x);
RcppExport SEXP _ipaddress_wrap_is_ipv4_mapped(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_ipv4_mapped(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_ipv4_mapped
List wrap_extract_ipv4_mapped(List address_r);
RcppExport SEXP _ipaddress_wrap_extract_ipv4_mapped(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_ipv4_mapped(address_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_6to4
LogicalVector wrap_is_6to4(List x);
RcppExport SEXP _ipaddress_wrap_is_6to4(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_6to4(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_6to4
List wrap_extract_6to4(List address_r);
RcppExport SEXP _ipaddress_wrap_extract_6to4(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_6to4(address_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_teredo
LogicalVector wrap_is_teredo(List x);
RcppExport SEXP _ipaddress_wrap_is_teredo(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_teredo(x));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_teredo_server
List wrap_extract_teredo_server(List address_r);
RcppExport SEXP _ipaddress_wrap_extract_teredo_server(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_teredo_server(address_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_teredo_client
List wrap_extract_teredo_client(List address_r);
RcppExport SEXP _ipaddress_wrap_extract_teredo_client(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_teredo_client(address_r));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ipaddress_wrap_parse_address", (DL_FUNC) &_ipaddress_wrap_parse_address, 1},
    {"_ipaddress_wrap_print_address", (DL_FUNC) &_ipaddress_wrap_print_address, 1},
    {"_ipaddress_wrap_encode_packed", (DL_FUNC) &_ipaddress_wrap_encode_packed, 1},
    {"_ipaddress_wrap_decode_packed", (DL_FUNC) &_ipaddress_wrap_decode_packed, 1},
    {"_ipaddress_wrap_encode_integer", (DL_FUNC) &_ipaddress_wrap_encode_integer, 1},
    {"_ipaddress_wrap_decode_integer", (DL_FUNC) &_ipaddress_wrap_decode_integer, 2},
    {"_ipaddress_wrap_encode_binary", (DL_FUNC) &_ipaddress_wrap_encode_binary, 1},
    {"_ipaddress_wrap_decode_binary", (DL_FUNC) &_ipaddress_wrap_decode_binary, 1},
    {"_ipaddress_wrap_encode_hostname", (DL_FUNC) &_ipaddress_wrap_encode_hostname, 1},
    {"_ipaddress_wrap_decode_hostname", (DL_FUNC) &_ipaddress_wrap_decode_hostname, 1},
    {"_ipaddress_wrap_parse_network", (DL_FUNC) &_ipaddress_wrap_parse_network, 2},
    {"_ipaddress_wrap_construct_network_from_address", (DL_FUNC) &_ipaddress_wrap_construct_network_from_address, 3},
    {"_ipaddress_wrap_print_network", (DL_FUNC) &_ipaddress_wrap_print_network, 1},
    {"_ipaddress_wrap_parse_interface", (DL_FUNC) &_ipaddress_wrap_parse_interface, 1},
    {"_ipaddress_wrap_construct_interface_from_address", (DL_FUNC) &_ipaddress_wrap_construct_interface_from_address, 2},
    {"_ipaddress_wrap_compare_address", (DL_FUNC) &_ipaddress_wrap_compare_address, 1},
    {"_ipaddress_wrap_network_hosts", (DL_FUNC) &_ipaddress_wrap_network_hosts, 2},
    {"_ipaddress_wrap_sample_network", (DL_FUNC) &_ipaddress_wrap_sample_network, 2},
    {"_ipaddress_wrap_bitwise_not", (DL_FUNC) &_ipaddress_wrap_bitwise_not, 1},
    {"_ipaddress_wrap_bitwise_and", (DL_FUNC) &_ipaddress_wrap_bitwise_and, 2},
    {"_ipaddress_wrap_bitwise_or", (DL_FUNC) &_ipaddress_wrap_bitwise_or, 2},
    {"_ipaddress_wrap_bitwise_xor", (DL_FUNC) &_ipaddress_wrap_bitwise_xor, 2},
    {"_ipaddress_wrap_add_integer", (DL_FUNC) &_ipaddress_wrap_add_integer, 2},
    {"_ipaddress_wrap_netmask", (DL_FUNC) &_ipaddress_wrap_netmask, 2},
    {"_ipaddress_wrap_hostmask", (DL_FUNC) &_ipaddress_wrap_hostmask, 2},
    {"_ipaddress_wrap_broadcast_address", (DL_FUNC) &_ipaddress_wrap_broadcast_address, 1},
    {"_ipaddress_wrap_is_within", (DL_FUNC) &_ipaddress_wrap_is_within, 2},
    {"_ipaddress_wrap_is_within_any", (DL_FUNC) &_ipaddress_wrap_is_within_any, 2},
    {"_ipaddress_wrap_is_multicast", (DL_FUNC) &_ipaddress_wrap_is_multicast, 1},
    {"_ipaddress_wrap_is_unspecified", (DL_FUNC) &_ipaddress_wrap_is_unspecified, 1},
    {"_ipaddress_wrap_is_loopback", (DL_FUNC) &_ipaddress_wrap_is_loopback, 1},
    {"_ipaddress_wrap_is_link_local", (DL_FUNC) &_ipaddress_wrap_is_link_local, 1},
    {"_ipaddress_wrap_is_ipv4_mapped", (DL_FUNC) &_ipaddress_wrap_is_ipv4_mapped, 1},
    {"_ipaddress_wrap_extract_ipv4_mapped", (DL_FUNC) &_ipaddress_wrap_extract_ipv4_mapped, 1},
    {"_ipaddress_wrap_is_6to4", (DL_FUNC) &_ipaddress_wrap_is_6to4, 1},
    {"_ipaddress_wrap_extract_6to4", (DL_FUNC) &_ipaddress_wrap_extract_6to4, 1},
    {"_ipaddress_wrap_is_teredo", (DL_FUNC) &_ipaddress_wrap_is_teredo, 1},
    {"_ipaddress_wrap_extract_teredo_server", (DL_FUNC) &_ipaddress_wrap_extract_teredo_server, 1},
    {"_ipaddress_wrap_extract_teredo_client", (DL_FUNC) &_ipaddress_wrap_extract_teredo_client, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_ipaddress(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
