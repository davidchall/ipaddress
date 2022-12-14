# encoding works

    Code
      ip_to_bytes("hello")
    Condition
      Error in `ip_to_bytes()`:
      ! `x` must be an <ip_address> vector

# decoding works

    Code
      bytes_to_ip("hello")
    Condition
      Error in `bytes_to_ip()`:
      ! `x` must be a list of raw vectors
    Code
      bytes_to_ip(address)
    Condition
      Error in `bytes_to_ip()`:
      ! `x` must be a list of raw vectors
    Code
      bytes_to_ip(c(bytes, "a"))
    Condition
      Error in `bytes_to_ip()`:
      ! `x` must be a list of raw vectors

