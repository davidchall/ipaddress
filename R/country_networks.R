#' Country-level IP networks
#'
#' Retrieve list of IP networks registered to specific countries.
#'
#' @details
#' This function requires an internet connection to download network lists.
#'
#' @param country Character vector of two-letter country codes (ISO 3166-1 alpha-2)
#' @return A data frame with 2 variables:
#'  * `country`: A character vector
#'  * `network`: A list of [`ip_network`] vectors
#'
#' @examples
#' country_networks(c("BR", "FR", "IN", "NA", "US"))
#'
#' @source \url{https://www.iwik.org/ipcountry} (updated daily)
#' @export
country_networks <- function(country) {
  check_installed("tibble")

  country <- toupper(country)
  networks <- lapply(country, download_iwik)
  networks <- as_list_of(networks, .ptype = ip_network())

  if (all(vapply(networks, length, 0) == 0)) {
    cli::cli_abort(c(
      "Can't download networks for {.emph any} country",
      "i" = "Is your internet connection working?"
    ), arg = "country")
  }

  tibble::tibble(country, networks)
}

download_iwik <- function(country) {
  url_base <- "https://www.iwik.org/ipcountry/"
  url_ipv4 <- paste0(url_base, country, ".cidr")
  url_ipv6 <- paste0(url_base, country, ".ipv6")

  networks <- vctrs::vec_c(
    download_networks(url_ipv4, strict = FALSE),
    download_networks(url_ipv6, strict = TRUE)
  )

  if (length(networks) == 0) {
    cli::cli_warn(c(
      "Can't download networks for country {.val {country}}.",
      "i" = "Is this a valid two-letter country code?",
      "x" = "Not found: {.url {url_ipv4}} and {.url {url_ipv6}}"
    ))
  }

  networks
}

download_networks <- function(url, strict = TRUE, comment = "#") {
  lines <- try_fetch(
    suppressWarnings(readLines(url, warn = FALSE)),
    error = function(cnd) {
      ip_network()
    }
  )

  # exclude commented lines
  if (nzchar(comment)) {
    regex_comment <- paste0("^", comment)
    lines <- grep(regex_comment, lines, invert = TRUE, value = TRUE)
  }

  ip_network(lines, strict = strict)
}
