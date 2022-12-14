# invalid inputs are caught

    Code
      ip_interface(ip_address("192.168.0.1"), 24.5)
    Condition
      Error in `ip_interface()`:
      ! `prefix_length` must be a integer vector

