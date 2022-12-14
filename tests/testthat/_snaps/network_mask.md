# input validation works

    Code
      prefix_length(1L)
    Condition
      Error in `prefix_length()`:
      ! `x` must be an <ip_network>, <ip_interface> or <ip_address> vector

---

    Code
      netmask(ip_address("1.2.3.4"))
    Condition
      Error in `netmask()`:
      ! `x` must be an <ip_network>, <ip_interface> or integer vector
    Code
      netmask(1.5, FALSE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must be a integer vector
    Code
      netmask(1L, "yes")
    Condition
      Error in `subnet_mask()`:
      ! `is_ipv6` must be a logical vector or NULL
    Code
      netmask(-1L, FALSE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must be positive
    Code
      netmask(33L, FALSE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must not be greater than 32 for IPv4
    Code
      netmask(129L, TRUE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must not be greater than 128 for IPv6

---

    Code
      hostmask(ip_address("1.2.3.4"))
    Condition
      Error in `hostmask()`:
      ! `x` must be an <ip_network>, <ip_interface> or integer vector
    Code
      hostmask(1.5, FALSE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must be a integer vector
    Code
      hostmask(1L, "yes")
    Condition
      Error in `subnet_mask()`:
      ! `is_ipv6` must be a logical vector or NULL
    Code
      hostmask(-1L, FALSE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must be positive
    Code
      hostmask(33L, FALSE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must not be greater than 32 for IPv4
    Code
      hostmask(129L, TRUE)
    Condition
      Error in `subnet_mask()`:
      ! `prefix_length` must not be greater than 128 for IPv6

