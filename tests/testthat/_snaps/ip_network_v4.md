# invalid inputs are caught

    Code
      ip_network(ip_address("1.2.3.4"), 24.5)
    Condition
      Error in `ip_network()`:
      ! `prefix_length` must be a integer vector

# strict argument works

    Code
      ip_network("1.2.3.4/32", strict = "yes")
    Condition
      Error in `ip_network()`:
      ! `strict` must be TRUE or FALSE
    Code
      ip_network("1.2.3.4/32", strict = NA)
    Condition
      Error in `ip_network()`:
      ! `strict` must be TRUE or FALSE

---

    Code
      ip_network(ip_address("1.2.3.4"), prefix_length = 32L, strict = "yes")
    Condition
      Error in `ip_network()`:
      ! `strict` must be TRUE or FALSE
    Code
      ip_network(ip_address("1.2.3.4"), prefix_length = 32L, strict = NA)
    Condition
      Error in `ip_network()`:
      ! `strict` must be TRUE or FALSE

