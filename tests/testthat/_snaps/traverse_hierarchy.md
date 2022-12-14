# supernet() works

    Code
      supernet(ip_network("0.0.0.0/0"))
    Condition
      Error in `supernet()`:
      ! `x` must have a supernetwork
    Code
      supernet(ip_network("::/0"))
    Condition
      Error in `supernet()`:
      ! `x` must have a supernetwork

# subnets() works

    Code
      subnets(ip_network("0.0.0.0/32"))
    Condition
      Error in `subnets()`:
      ! `x` must have a subnetwork
    Code
      subnets(ip_network("::/128"))
    Condition
      Error in `subnets()`:
      ! `x` must have a subnetwork

# missing values work

    Code
      supernet(ip_network("192.168.0.0/24"), new_prefix = NA)
    Condition
      Error in `supernet()`:
      ! `new_prefix` must be a integer vector

---

    Code
      subnets(ip_network("192.168.0.0/24"), new_prefix = NA)
    Condition
      Error in `subnets()`:
      ! `new_prefix` must be a integer vector

# input validation

    Code
      supernet(ip_address("1.2.3.4"))
    Condition
      Error in `supernet()`:
      ! `x` must be an <ip_network> vector
    Code
      supernet(ip_network("192.168.0.0/20"), new_prefix = "yes")
    Condition
      Error in `supernet()`:
      ! `new_prefix` must be a integer vector
    Code
      supernet(ip_network("192.168.0.0/20"), new_prefix = -1L)
    Condition
      Error in `supernet()`:
      ! `new_prefix` must be positive
    Code
      supernet(ip_network("192.168.0.0/20"), new_prefix = 21L)
    Condition
      Error in `supernet()`:
      ! `new_prefix` must be less than `prefix_length(x)`

---

    Code
      subnets(ip_address("1.2.3.4"))
    Condition
      Error in `subnets()`:
      ! `x` must be an <ip_network> vector
    Code
      subnets(ip_network("192.168.0.0/20"), new_prefix = "yes")
    Condition
      Error in `subnets()`:
      ! `new_prefix` must be a integer vector
    Code
      subnets(ip_network("192.168.0.0/20"), new_prefix = -1L)
    Condition
      Error in `subnets()`:
      ! `new_prefix` must be positive
    Code
      subnets(ip_network("192.168.0.0/20"), new_prefix = 33L)
    Condition
      Error in `subnets()`:
      ! `new_prefix` must be less than `max_prefix_length(x)`
    Code
      subnets(ip_network("192.168.0.0/20"), new_prefix = 19L)
    Condition
      Error in `subnets()`:
      ! `new_prefix` must be greater than `prefix_length(x)`

