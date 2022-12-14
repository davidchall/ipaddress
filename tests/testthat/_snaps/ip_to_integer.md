# integer encoding/decoding works

    Code
      ip_to_integer("hello")
    Condition
      Error in `ip_to_hex()`:
      ! `x` must be an <ip_address> vector

---

    Code
      integer_to_ip(1, is_ipv6 = "true")
    Condition
      Error in `hex_to_ip()`:
      ! `is_ipv6` must be a logical vector or NULL

