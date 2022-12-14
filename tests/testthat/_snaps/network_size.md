# num_addresses works

    Code
      num_addresses(ip_address("192.168.0.1"))
    Condition
      Error in `num_addresses()`:
      ! `x` must be an <ip_network> vector

# network_address works

    Code
      network_address(ip_address("192.168.0.1"))
    Condition
      Error in `network_address()`:
      ! `x` must be an <ip_network> vector

# broadcast_address works

    Code
      broadcast_address(ip_address("192.168.0.1"))
    Condition
      Error in `broadcast_address()`:
      ! `x` must be an <ip_network> vector

