# hostname encoding/decoding works

    Code
      ip_to_hostname(ip_network("192.168.0.0/24"))
    Condition
      Error in `ip_to_hostname_all()`:
      ! `x` must be an <ip_address> vector
    Code
      ip_to_hostname("127.0.0.1")
    Condition
      Error in `ip_to_hostname_all()`:
      ! `x` must be an <ip_address> vector

---

    Code
      hostname_to_ip(123)
    Condition
      Error in `hostname_to_ip_all()`:
      ! `x` must be a character vector
    Code
      hostname_to_ip(ip_address("127.0.0.1"))
    Condition
      Error in `hostname_to_ip_all()`:
      ! `x` must be a character vector

