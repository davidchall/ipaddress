library(tidyverse)
library(ipaddress)


# address space --------------------------------------------------

space_file <- "https://www.iana.org/assignments/ipv6-address-space/ipv6-address-space-1.csv"
space_cols <- cols(
  prefix = col_character(),
  designation = col_character(),
  reference = col_skip(),
  note = col_skip()
)

space <- space_file %>%
  read_csv(col_names = names(space_cols$cols), col_types = space_cols, skip = 1) %>%
  filter(designation != "Global Unicast") %>%
  transmute(
    network = ip_network(prefix),
    allocation = "Reserved",
    label = case_when(
      str_detect(designation, "IETF") ~ "IETF",
      TRUE ~ designation
    )
  )


# unicast --------------------------------------------------------

unicast_file <- "https://www.iana.org/assignments/ipv6-unicast-address-assignments/ipv6-unicast-address-assignments.csv"
unicast_cols <- cols(
  prefix = col_character(),
  designation = col_character(),
  date = col_skip(),
  whois = col_skip(),
  rdap = col_skip(),
  status = col_character(),
  note = col_skip()
)

unicast <- unicast_file %>%
  read_csv(col_names = names(unicast_cols$cols), col_types = unicast_cols, skip = 1) %>%
  mutate(
    network = ip_network(prefix),
    allocation = if_else(status == "RESERVED", "Reserved", "Managed"),
    label = designation
  )


# merge datasets -------------------------------------------------

iana_ipv6 <- bind_rows(space, unicast) %>%
  group_by(allocation, label) %>%
  summarize(network = collapse_networks(network), .groups = "drop") %>%
  arrange(network) %>%
  mutate(allocation = factor(allocation)) %>%
  select(network, allocation, label)

usethis::use_data(iana_ipv6, overwrite = TRUE)
