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
CharacterVector wrap_print_address(List x, bool exploded);
RcppExport SEXP _ipaddress_wrap_print_address(SEXP xSEXP, SEXP explodedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type exploded(explodedSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_print_address(x, exploded));
    return rcpp_result_gen;
END_RCPP
}
// wrap_compare_address
DataFrame wrap_compare_address(List address_r);
RcppExport SEXP _ipaddress_wrap_compare_address(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_compare_address(address_r));
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
List wrap_construct_network_from_address(List address_r, IntegerVector prefix_length, bool strict);
RcppExport SEXP _ipaddress_wrap_construct_network_from_address(SEXP address_rSEXP, SEXP prefix_lengthSEXP, SEXP strictSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type prefix_length(prefix_lengthSEXP);
    Rcpp::traits::input_parameter< bool >::type strict(strictSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_construct_network_from_address(address_r, prefix_length, strict));
    return rcpp_result_gen;
END_RCPP
}
// wrap_print_network
CharacterVector wrap_print_network(List x, bool exploded);
RcppExport SEXP _ipaddress_wrap_print_network(SEXP xSEXP, SEXP explodedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type exploded(explodedSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_print_network(x, exploded));
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
// wrap_netmask
List wrap_netmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6);
RcppExport SEXP _ipaddress_wrap_netmask(SEXP in_prefix_lengthSEXP, SEXP in_is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type in_prefix_length(in_prefix_lengthSEXP);
    Rcpp::traits::input_parameter< LogicalVector >::type in_is_ipv6(in_is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_netmask(in_prefix_length, in_is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// wrap_hostmask
List wrap_hostmask(IntegerVector in_prefix_length, LogicalVector in_is_ipv6);
RcppExport SEXP _ipaddress_wrap_hostmask(SEXP in_prefix_lengthSEXP, SEXP in_is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerVector >::type in_prefix_length(in_prefix_lengthSEXP);
    Rcpp::traits::input_parameter< LogicalVector >::type in_is_ipv6(in_is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_hostmask(in_prefix_length, in_is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// wrap_prefix_from_mask
IntegerVector wrap_prefix_from_mask(List address_r);
RcppExport SEXP _ipaddress_wrap_prefix_from_mask(SEXP address_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address_r(address_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_prefix_from_mask(address_r));
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
// wrap_subnets
List wrap_subnets(List network_r, IntegerVector new_prefix);
RcppExport SEXP _ipaddress_wrap_subnets(SEXP network_rSEXP, SEXP new_prefixSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type new_prefix(new_prefixSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_subnets(network_r, new_prefix));
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
// wrap_smallest_common_network
List wrap_smallest_common_network(List address1_r, List address2_r);
RcppExport SEXP _ipaddress_wrap_smallest_common_network(SEXP address1_rSEXP, SEXP address2_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address1_r(address1_rSEXP);
    Rcpp::traits::input_parameter< List >::type address2_r(address2_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_smallest_common_network(address1_r, address2_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_summarize_address_range
List wrap_summarize_address_range(List address1_r, List address2_r);
RcppExport SEXP _ipaddress_wrap_summarize_address_range(SEXP address1_rSEXP, SEXP address2_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type address1_r(address1_rSEXP);
    Rcpp::traits::input_parameter< List >::type address2_r(address2_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_summarize_address_range(address1_r, address2_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_collapse_networks
List wrap_collapse_networks(List network_r);
RcppExport SEXP _ipaddress_wrap_collapse_networks(SEXP network_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type network_r(network_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_collapse_networks(network_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_not
List wrap_bitwise_not(List lhs_r);
RcppExport SEXP _ipaddress_wrap_bitwise_not(SEXP lhs_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs_r(lhs_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_not(lhs_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_and
List wrap_bitwise_and(List lhs_r, List rhs_r);
RcppExport SEXP _ipaddress_wrap_bitwise_and(SEXP lhs_rSEXP, SEXP rhs_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs_r(lhs_rSEXP);
    Rcpp::traits::input_parameter< List >::type rhs_r(rhs_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_and(lhs_r, rhs_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_or
List wrap_bitwise_or(List lhs_r, List rhs_r);
RcppExport SEXP _ipaddress_wrap_bitwise_or(SEXP lhs_rSEXP, SEXP rhs_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs_r(lhs_rSEXP);
    Rcpp::traits::input_parameter< List >::type rhs_r(rhs_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_or(lhs_r, rhs_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_xor
List wrap_bitwise_xor(List lhs_r, List rhs_r);
RcppExport SEXP _ipaddress_wrap_bitwise_xor(SEXP lhs_rSEXP, SEXP rhs_rSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs_r(lhs_rSEXP);
    Rcpp::traits::input_parameter< List >::type rhs_r(rhs_rSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_xor(lhs_r, rhs_r));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_shift_left
List wrap_bitwise_shift_left(List lhs_r, IntegerVector rhs);
RcppExport SEXP _ipaddress_wrap_bitwise_shift_left(SEXP lhs_rSEXP, SEXP rhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs_r(lhs_rSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type rhs(rhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_shift_left(lhs_r, rhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_bitwise_shift_right
List wrap_bitwise_shift_right(List lhs_r, IntegerVector rhs);
RcppExport SEXP _ipaddress_wrap_bitwise_shift_right(SEXP lhs_rSEXP, SEXP rhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs_r(lhs_rSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type rhs(rhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_bitwise_shift_right(lhs_r, rhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_add_integer
List wrap_add_integer(List lhs_r, IntegerVector rhs);
RcppExport SEXP _ipaddress_wrap_add_integer(SEXP lhs_rSEXP, SEXP rhsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lhs_r(lhs_rSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type rhs(rhsSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_add_integer(lhs_r, rhs));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_bytes
List wrap_decode_bytes(List input);
RcppExport SEXP _ipaddress_wrap_decode_bytes(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_bytes(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_bytes
List wrap_encode_bytes(List input);
RcppExport SEXP _ipaddress_wrap_encode_bytes(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_bytes(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_integer
List wrap_decode_integer(CharacterVector input, Nullable<LogicalVector> in_is_ipv6);
RcppExport SEXP _ipaddress_wrap_decode_integer(SEXP inputSEXP, SEXP in_is_ipv6SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type input(inputSEXP);
    Rcpp::traits::input_parameter< Nullable<LogicalVector> >::type in_is_ipv6(in_is_ipv6SEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_integer(input, in_is_ipv6));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_integer
CharacterVector wrap_encode_integer(List input, bool hex);
RcppExport SEXP _ipaddress_wrap_encode_integer(SEXP inputSEXP, SEXP hexSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    Rcpp::traits::input_parameter< bool >::type hex(hexSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_integer(input, hex));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_binary
List wrap_decode_binary(CharacterVector input);
RcppExport SEXP _ipaddress_wrap_decode_binary(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_binary(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_binary
CharacterVector wrap_encode_binary(List input);
RcppExport SEXP _ipaddress_wrap_encode_binary(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_binary(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_decode_hostname
List wrap_decode_hostname(CharacterVector input);
RcppExport SEXP _ipaddress_wrap_decode_hostname(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_decode_hostname(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_encode_hostname
List wrap_encode_hostname(List input);
RcppExport SEXP _ipaddress_wrap_encode_hostname(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_encode_hostname(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_multicast
LogicalVector wrap_is_multicast(List input);
RcppExport SEXP _ipaddress_wrap_is_multicast(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_multicast(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_unspecified
LogicalVector wrap_is_unspecified(List input);
RcppExport SEXP _ipaddress_wrap_is_unspecified(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_unspecified(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_loopback
LogicalVector wrap_is_loopback(List input);
RcppExport SEXP _ipaddress_wrap_is_loopback(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_loopback(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_link_local
LogicalVector wrap_is_link_local(List input);
RcppExport SEXP _ipaddress_wrap_is_link_local(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_link_local(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_site_local
LogicalVector wrap_is_site_local(List input);
RcppExport SEXP _ipaddress_wrap_is_site_local(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_site_local(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_ipv4_mapped
LogicalVector wrap_is_ipv4_mapped(List input);
RcppExport SEXP _ipaddress_wrap_is_ipv4_mapped(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_ipv4_mapped(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_ipv4_mapped
List wrap_extract_ipv4_mapped(List input);
RcppExport SEXP _ipaddress_wrap_extract_ipv4_mapped(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_ipv4_mapped(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_6to4
LogicalVector wrap_is_6to4(List input);
RcppExport SEXP _ipaddress_wrap_is_6to4(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_6to4(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_6to4
List wrap_extract_6to4(List input);
RcppExport SEXP _ipaddress_wrap_extract_6to4(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_6to4(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_is_teredo
LogicalVector wrap_is_teredo(List input);
RcppExport SEXP _ipaddress_wrap_is_teredo(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_is_teredo(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_teredo_server
List wrap_extract_teredo_server(List input);
RcppExport SEXP _ipaddress_wrap_extract_teredo_server(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_teredo_server(input));
    return rcpp_result_gen;
END_RCPP
}
// wrap_extract_teredo_client
List wrap_extract_teredo_client(List input);
RcppExport SEXP _ipaddress_wrap_extract_teredo_client(SEXP inputSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type input(inputSEXP);
    rcpp_result_gen = Rcpp::wrap(wrap_extract_teredo_client(input));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ipaddress_wrap_parse_address", (DL_FUNC) &_ipaddress_wrap_parse_address, 1},
    {"_ipaddress_wrap_print_address", (DL_FUNC) &_ipaddress_wrap_print_address, 2},
    {"_ipaddress_wrap_compare_address", (DL_FUNC) &_ipaddress_wrap_compare_address, 1},
    {"_ipaddress_wrap_parse_network", (DL_FUNC) &_ipaddress_wrap_parse_network, 2},
    {"_ipaddress_wrap_construct_network_from_address", (DL_FUNC) &_ipaddress_wrap_construct_network_from_address, 3},
    {"_ipaddress_wrap_print_network", (DL_FUNC) &_ipaddress_wrap_print_network, 2},
    {"_ipaddress_wrap_parse_interface", (DL_FUNC) &_ipaddress_wrap_parse_interface, 1},
    {"_ipaddress_wrap_construct_interface_from_address", (DL_FUNC) &_ipaddress_wrap_construct_interface_from_address, 2},
    {"_ipaddress_wrap_broadcast_address", (DL_FUNC) &_ipaddress_wrap_broadcast_address, 1},
    {"_ipaddress_wrap_netmask", (DL_FUNC) &_ipaddress_wrap_netmask, 2},
    {"_ipaddress_wrap_hostmask", (DL_FUNC) &_ipaddress_wrap_hostmask, 2},
    {"_ipaddress_wrap_prefix_from_mask", (DL_FUNC) &_ipaddress_wrap_prefix_from_mask, 1},
    {"_ipaddress_wrap_is_within", (DL_FUNC) &_ipaddress_wrap_is_within, 2},
    {"_ipaddress_wrap_is_within_any", (DL_FUNC) &_ipaddress_wrap_is_within_any, 2},
    {"_ipaddress_wrap_network_hosts", (DL_FUNC) &_ipaddress_wrap_network_hosts, 2},
    {"_ipaddress_wrap_subnets", (DL_FUNC) &_ipaddress_wrap_subnets, 2},
    {"_ipaddress_wrap_sample_network", (DL_FUNC) &_ipaddress_wrap_sample_network, 2},
    {"_ipaddress_wrap_smallest_common_network", (DL_FUNC) &_ipaddress_wrap_smallest_common_network, 2},
    {"_ipaddress_wrap_summarize_address_range", (DL_FUNC) &_ipaddress_wrap_summarize_address_range, 2},
    {"_ipaddress_wrap_collapse_networks", (DL_FUNC) &_ipaddress_wrap_collapse_networks, 1},
    {"_ipaddress_wrap_bitwise_not", (DL_FUNC) &_ipaddress_wrap_bitwise_not, 1},
    {"_ipaddress_wrap_bitwise_and", (DL_FUNC) &_ipaddress_wrap_bitwise_and, 2},
    {"_ipaddress_wrap_bitwise_or", (DL_FUNC) &_ipaddress_wrap_bitwise_or, 2},
    {"_ipaddress_wrap_bitwise_xor", (DL_FUNC) &_ipaddress_wrap_bitwise_xor, 2},
    {"_ipaddress_wrap_bitwise_shift_left", (DL_FUNC) &_ipaddress_wrap_bitwise_shift_left, 2},
    {"_ipaddress_wrap_bitwise_shift_right", (DL_FUNC) &_ipaddress_wrap_bitwise_shift_right, 2},
    {"_ipaddress_wrap_add_integer", (DL_FUNC) &_ipaddress_wrap_add_integer, 2},
    {"_ipaddress_wrap_decode_bytes", (DL_FUNC) &_ipaddress_wrap_decode_bytes, 1},
    {"_ipaddress_wrap_encode_bytes", (DL_FUNC) &_ipaddress_wrap_encode_bytes, 1},
    {"_ipaddress_wrap_decode_integer", (DL_FUNC) &_ipaddress_wrap_decode_integer, 2},
    {"_ipaddress_wrap_encode_integer", (DL_FUNC) &_ipaddress_wrap_encode_integer, 2},
    {"_ipaddress_wrap_decode_binary", (DL_FUNC) &_ipaddress_wrap_decode_binary, 1},
    {"_ipaddress_wrap_encode_binary", (DL_FUNC) &_ipaddress_wrap_encode_binary, 1},
    {"_ipaddress_wrap_decode_hostname", (DL_FUNC) &_ipaddress_wrap_decode_hostname, 1},
    {"_ipaddress_wrap_encode_hostname", (DL_FUNC) &_ipaddress_wrap_encode_hostname, 1},
    {"_ipaddress_wrap_is_multicast", (DL_FUNC) &_ipaddress_wrap_is_multicast, 1},
    {"_ipaddress_wrap_is_unspecified", (DL_FUNC) &_ipaddress_wrap_is_unspecified, 1},
    {"_ipaddress_wrap_is_loopback", (DL_FUNC) &_ipaddress_wrap_is_loopback, 1},
    {"_ipaddress_wrap_is_link_local", (DL_FUNC) &_ipaddress_wrap_is_link_local, 1},
    {"_ipaddress_wrap_is_site_local", (DL_FUNC) &_ipaddress_wrap_is_site_local, 1},
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
