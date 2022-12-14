# input validation

    Code
      common_network(ip_network(), ip_address())
    Condition
      Error in `common_network()`:
      ! `address1` must be an <ip_address> vector
    Code
      common_network(ip_address(), ip_network())
    Condition
      Error in `common_network()`:
      ! `address2` must be an <ip_address> vector
    Code
      common_network(ip_address(rep("1.2.3.4", 3)), ip_address(rep("1.2.3.4", 2)))
    Condition
      Error in `common_network()`:
      ! Can't recycle `..1` (size 3) to match `..2` (size 2).

