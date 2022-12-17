# input validation

    Code
      country_networks(1L)
    Condition
      Error in `country_networks()`:
      ! `country` must be a character vector
    Code
      country_networks("hello")
    Condition
      Error in `country_networks()`:
      ! `country` must contain exactly 2 letters
    Code
      country_networks("A1")
    Condition
      Error in `country_networks()`:
      ! `country` must contain letters only

