# bitwise shift works

    Code
      ip_address("192.168.0.1") %<<% -1L
    Condition
      Error in `ip_address("192.168.0.1") %<<% -1L`:
      ! `n` must be positive

---

    Code
      ip_address("192.168.0.1") %>>% -1L
    Condition
      Error in `ip_address("192.168.0.1") %>>% -1L`:
      ! `n` must be positive

