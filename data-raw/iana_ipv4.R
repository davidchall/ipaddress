library(tidyverse)
library(ipaddress)

csv_file <- "https://www.iana.org/assignments/ipv4-address-space/ipv4-address-space.csv"
csv_cols <- cols(
  prefix = col_character(),
  designation = col_character(),
  date = col_date("%Y-%m"),
  whois = col_skip(),
  rdap = col_skip(),
  status = col_character(),
  note = col_skip()
)


iana_ipv4 <- csv_file %>%
  read_csv(col_names = names(csv_cols$cols), col_types = csv_cols, skip = 1) %>%
  transmute(
    network = ip_network(str_replace(prefix, "^(\\d+)\\/(\\d+)$", "\\1\\.0\\.0\\.0\\/\\2")),
    organization = case_when(
      designation == "Multicast" ~ designation,
      status == "RESERVED" ~ str_to_title(status),
      status == "UNALLOCATED" ~ str_to_title(status),
      status == "LEGACY" & str_detect(designation, "^Administered by") ~ "Various registries",
      designation == "RIPE NCC" ~ "RIPE",

      # specific organizations
      str_detect(designation, "Army") ~ "US DoD",
      str_detect(designation, "DoD") ~ "US DoD",
      designation == "US-DOD" ~ "US DoD",
      designation == "DLA Systems Automation Center" ~ "US DoD",
      designation == "Defense Information Systems Agency" ~ "US DoD",
      designation == "DSI-North" ~ "US DoD",
      designation == "DDN-RVN" ~ "US DoD",
      str_detect(designation, "AT&T") ~ "AT&T",
      str_detect(designation, "Apple") ~ "Apple",
      str_detect(designation, "Daimler") ~ "Daimler",
      str_detect(designation, "Ford") ~ "Ford",
      str_detect(designation, "Prudential") ~ "Prudential",
      str_detect(designation, "PSINet") ~ "Cogent",
      designation == "US Postal Service" ~ "USPS",

      TRUE ~ designation
    ),
    allocation = factor(case_when(
      organization %in% c("Reserved", "Multicast") ~ "Reserved",
      organization %in% c("AFRINIC", "APNIC", "ARIN", "LACNIC", "RIPE", "Various registries") ~ "Managed",
      TRUE ~ "Assigned"
    ))
  ) %>%
  group_by(allocation, organization) %>%
  summarize(network = collapse_networks(network), .groups = "drop") %>%
  arrange(network) %>%
  select(network, allocation, organization)

usethis::use_data(iana_ipv4, overwrite = TRUE)
