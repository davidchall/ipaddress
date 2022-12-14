# invalid inputs are caught

    Code
      ip_network(ip_address("2001:db8::"), 24.5)
    Condition
      Error in `ip_network()`:
      ! `prefix_length` must be a integer vector

# strict argument works

    Code
      ip_network("2001:db8::/36", strict = "yes")
    Condition
      Error in `ip_network()`:
      ! `strict` must be TRUE or FALSE
    Code
      ip_network("2001:db8::/36", strict = NA)
    Condition
      Error in `ip_network()`:
      ! `strict` must be TRUE or FALSE

