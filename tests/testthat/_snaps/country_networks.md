# download fails

    Code
      country_networks(c("US", "AA"))
    Condition
      Warning:
      Can't download networks for country "AA".
      i Is this a valid two-letter country code?
      x Not found: <https://www.iwik.org/ipcountry/AA.cidr> and <https://www.iwik.org/ipcountry/AA.ipv6>
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
      Warning:
      Can't download networks for country "AA".
      i Is this a valid two-letter country code?
      x Not found: <https://www.iwik.org/ipcountry/AA.cidr> and <https://www.iwik.org/ipcountry/AA.ipv6>
      Error in `country_networks()`:
      ! Can't download networks for any country
      i Is your internet connection working?

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

