# IPv4-mapped IPv6 addresses work

    Code
      is_ipv4_mapped("hello")
    Condition
      Error in `is_ipv4_mapped()`:
      ! `x` must be an <ip_address> or <ip_network> vector

---

    Code
      extract_ipv4_mapped("hello")
    Condition
      Error in `extract_ipv4_mapped()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_ipv4_mapped(ip_network())
    Condition
      Error in `extract_ipv4_mapped()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_ipv4_mapped(NA)
    Condition
      Error in `extract_ipv4_mapped()`:
      ! `x` must be an <ip_address> vector

# 6to4 IPv6 addresses work

    Code
      is_6to4("hello")
    Condition
      Error in `is_6to4()`:
      ! `x` must be an <ip_address> or <ip_network> vector

---

    Code
      extract_6to4("hello")
    Condition
      Error in `extract_6to4()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_6to4(ip_network())
    Condition
      Error in `extract_6to4()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_6to4(NA)
    Condition
      Error in `extract_6to4()`:
      ! `x` must be an <ip_address> vector

# Teredo IPv6 addresses work

    Code
      is_teredo("hello")
    Condition
      Error in `is_teredo()`:
      ! `x` must be an <ip_address> or <ip_network> vector

---

    Code
      extract_teredo_server("hello")
    Condition
      Error in `extract_teredo_server()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_teredo_server(ip_network())
    Condition
      Error in `extract_teredo_server()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_teredo_server(NA)
    Condition
      Error in `extract_teredo_server()`:
      ! `x` must be an <ip_address> vector

---

    Code
      extract_teredo_client("hello")
    Condition
      Error in `extract_teredo_client()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_teredo_client(ip_network())
    Condition
      Error in `extract_teredo_client()`:
      ! `x` must be an <ip_address> vector
    Code
      extract_teredo_client(NA)
    Condition
      Error in `extract_teredo_client()`:
      ! `x` must be an <ip_address> vector

