library(ipaddress)

addr_obj <- seq(ip_network("2001:db8::/110"))
addr_str <- as.character(addr_obj)
netw_str <- paste0(addr_str, "/128")
netw_obj <- ip_network(netw_str)

single_subnet <- ip_network(rep("2001:db8::/119", length(addr_str)))
multi_subnet <- ip_network(c("2001:db8::/119", "2001:db8::3:0/123", "::/120"))

bench::mark(
  # class input/output
  parse_address = ip_address(addr_str),
  parse_network = ip_network(netw_str),
  print_address = as.character(addr_obj),
  print_network = as.character(netw_obj),

  # network membership
  is_within = is_within(addr_obj, single_subnet),
  is_within_any = is_within_any(addr_obj, multi_subnet),
  is_subnet = is_subnet(netw_obj, single_subnet),
  is_supernet = is_supernet(single_subnet, netw_obj),
  prefix_length = prefix_length(netw_obj),
  netmask = netmask(netw_obj),
  hostmask = hostmask(netw_obj),

  # compare
  minimum = min(addr_obj),
  maximum = max(addr_obj),

  check = FALSE
)
