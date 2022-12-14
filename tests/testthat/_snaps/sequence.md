# input validation works

    Code
      seq(ip_network(rep("192.168.0.0/24", 2)))
    Condition
      Error in `seq()`:
      ! `x` must have length 1, not length 2
    Code
      seq(ip_network())
    Condition
      Error in `seq()`:
      ! `x` must have length 1, not length 0

---

    Code
      hosts(ip_network(rep("192.168.0.0/24", 2)))
    Condition
      Error in `hosts()`:
      ! `x` must have length 1, not length 2
    Code
      hosts(ip_network())
    Condition
      Error in `hosts()`:
      ! `x` must have length 1, not length 0
    Code
      hosts(ip_address("192.168.0.0"))
    Condition
      Error in `hosts()`:
      ! `x` must be an <ip_network> vector

