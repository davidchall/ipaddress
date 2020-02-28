library(ipaddress)

generate_range <- function() {
  dat <- expand.grid(a = 192, b = 168:171, c = 0:255, d = 0:255)
  paste(dat$a, dat$b, dat$c, dat$d, sep = ".")
}

# use IP address range 192.168.0.0/14
addr_str <- generate_range()
netw_str <- paste0(addr_str, "/32")
addr_obj <- ip_address(addr_str)
netw_obj <- ip_network(netw_str)

single_subnet <- ip_network(rep("192.168.0.0/23", length(addr_str)))
multi_subnet <- ip_network(c("192.168.0.0/23", "192.171.0.0/27", "0.1.0.0/24"))

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
