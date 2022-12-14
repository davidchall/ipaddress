# hex encoding/decoding works

    Code
      ip_to_hex("hello")
    Condition
      Error in `ip_to_hex()`:
      ! `x` must be an <ip_address> vector

---

    Code
      hex_to_ip(x)
    Condition
      Error in `hex_to_ip()`:
      ! `x` must be a character vector
    Code
      hex_to_ip("0xff", is_ipv6 = "true")
    Condition
      Error in `hex_to_ip()`:
      ! `is_ipv6` must be a logical vector or NULL

---

    Code
      hex_to_ip("0x12GH")
    Condition
      Error in `hex_to_ip()`:
      ! `x` must be a hexadecimal string
    Code
      hex_to_ip(c("12ab", "hello"))
    Condition
      Error in `hex_to_ip()`:
      ! Each value in `x` must be a hexadecimal string
      x Violations found at 2 locations: 1 and 2

