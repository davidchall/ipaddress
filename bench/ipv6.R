library(ipaddress)

generate_range <- function() {
  dat <- expand.grid(a = 0:3, b = as.character(as.hexmode(0:(2^16-1))))
  paste("2001:db8:", dat$a, dat$b, sep = ":")
}

# use IP address range 2001:db8::/110
addr_str <- generate_range()
netw_str <- paste0(addr_str, "/128")
addr_obj <- ip_address(addr_str)
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
