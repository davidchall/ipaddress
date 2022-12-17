# download fails

    Code
      country_networks(c("US", "AA"))
    Condition
      Warning:
      Can't download networks for 1 country
      i Check country codes are valid: "AA"
    Output
      # A tibble: 2 x 2
        country         networks
        <chr>   <list<ip_netwk>>
      1 US              [72,168]
      2 AA                   [0]

---

    Code
      country_networks("AA")
    Condition
      Error in `country_networks()`:
      ! Can't download networks for any country
      i Is server down? <https://www.iwik.org/ipcountry/>
      i Check country codes are valid: "AA"

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

