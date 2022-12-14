# input validation works

    Code
      is_within(ip_network(), ip_network())
    Condition
      Error in `is_within()`:
      ! `address` must be an <ip_address> vector
    Code
      is_within(ip_address(), ip_address())
    Condition
      Error in `is_within()`:
      ! `network` must be an <ip_network> vector

---

    Code
      is_within_any(ip_network(), ip_network())
    Condition
      Error in `is_within_any()`:
      ! `address` must be an <ip_address> vector
    Code
      is_within_any(ip_address(), ip_address())
    Condition
      Error in `is_within_any()`:
      ! `network` must be an <ip_network> vector

---

    Code
      overlaps(ip_address(), ip_network())
    Condition
      Error in `overlaps()`:
      ! `network` must be an <ip_network> vector
    Code
      overlaps(ip_network(), ip_address())
    Condition
      Error in `overlaps()`:
      ! `other` must be an <ip_network> vector

---

    Code
      is_subnet(ip_address(), ip_network())
    Condition
      Error in `is_subnet()`:
      ! `network` must be an <ip_network> vector
    Code
      is_subnet(ip_network(), ip_address())
    Condition
      Error in `is_subnet()`:
      ! `other` must be an <ip_network> vector

---

    Code
      is_supernet(ip_address(), ip_network())
    Condition
      Error in `is_supernet()`:
      ! `network` must be an <ip_network> vector
    Code
      is_supernet(ip_network(), ip_address())
    Condition
      Error in `is_supernet()`:
      ! `other` must be an <ip_network> vector

