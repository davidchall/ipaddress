# input validation works

    Code
      sample_network(rep(ipv4, 2), 1)
    Condition
      Error in `sample_network()`:
      ! `x` must have length 1, not length 2
    Code
      sample_network(ip_network(), 1)
    Condition
      Error in `sample_network()`:
      ! `x` must have length 1, not length 0
    Code
      sample_network(ip_address("192.168.0.0"), 1)
    Condition
      Error in `sample_network()`:
      ! `x` must be an <ip_network> vector
    Code
      sample_network(ip_network(NA), 1)
    Condition
      Error in `sample_network()`:
      ! `x` must not be NA

---

    Code
      sample_network(ip_network("0.0.0.0/32"), -1)
    Condition
      Error in `sample_network()`:
      ! `size` must be positive non-zero integer
    Code
      sample_network(ip_network("0.0.0.0/32"), 2^31, replace = TRUE)
    Condition
      Error in `sample_network()`:
      ! `size` must be less than 2^31
      x Requested size: 2147483648
      i Maximum size: 2147483648
    Code
      sample_network(ip_network("0.0.0.0/32"), NA)
    Condition
      Error in `sample_network()`:
      ! `size` must be a integer vector

---

    Code
      sample_network(ip_network("0.0.0.0/32"), 1, replace = NA)
    Condition
      Error in `sample_network()`:
      ! `replace` must be TRUE or FALSE
    Code
      sample_network(ip_network("0.0.0.0/32"), 1, replace = 1)
    Condition
      Error in `sample_network()`:
      ! `replace` must be TRUE or FALSE

---

    Code
      sample_network(ipv4, num_addresses(ipv4) + 1, replace = FALSE)
    Condition
      Error in `sample_network()`:
      ! `size` must not be greater than the network size when `replace = FALSE`
      x Requested size: 1048577
      i Network size: 1048576

