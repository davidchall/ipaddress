# input validation

    Code
      summarize_address_range(ip_network(), ip_address())
    Condition
      Error in `summarize_address_range()`:
      ! `address1` must be an <ip_address> vector
    Code
      summarize_address_range(ip_address(), ip_network())
    Condition
      Error in `summarize_address_range()`:
      ! `address2` must be an <ip_address> vector
    Code
      summarize_address_range(ip_address(rep("1.2.3.4", 3)), ip_address(rep("1.2.3.4",
        2)))
    Condition
      Error in `summarize_address_range()`:
      ! Can't recycle `..1` (size 3) to match `..2` (size 2).

---

    Code
      collapse_networks(ip_address("192.168.0.1"))
    Condition
      Error in `collapse_networks()`:
      ! `network` must be an <ip_network> vector

---

    Code
      exclude_networks(ip_address("192.168.0.1"), ip_network("192.168.0.0/24"))
    Condition
      Error in `exclude_networks()`:
      ! `include` must be an <ip_network> vector
    Code
      exclude_networks(ip_network("192.168.0.0/24"), ip_address("192.168.0.1"))
    Condition
      Error in `exclude_networks()`:
      ! `exclude` must be an <ip_network> vector

