#' Country-level IP networks
#'
#' Retrieve lists of IP networks registered to specific countries.
#'
#' @details
#' This function requires an internet connection to download network lists.
#'
#' @param country Character vector of two-letter country codes (ISO 3166-1 alpha-2)
#' @param collapse If `TRUE` (the default), contiguous networks are collapsed.
#'   See [collapse_networks()].
#' @inheritParams rlang::args_dots_empty
#' @return A data frame with 2 variables:
#'  * `country`: A character vector
#'  * `network`: A list of [`ip_network`] vectors
#'
#' Each row represents a single country associated with a vector of IP networks.
#'
#' @examples
#' \dontrun{
#' country_networks(c("GB", "US"))
#'
#' country_networks(c("GB", "US"), collapse = FALSE)
#'
#' # retrieve networks for a single country
#' country_networks("TO")$networks[[1]]
#'
#' # expand networks for multiple countries
#' tidyr::unchop(country_networks(c("GB", "US")), networks)
#' }
#' @source \url{https://www.iwik.org/ipcountry/} (updated daily)
#' @export
country_networks <- function(country, ..., collapse = TRUE) {
  check_installed("tibble")
  check_dots_empty()
  check_character(country)
  check_bool(collapse)
  check_all(nchar(country) == 2, "country", "must contain exactly 2 letters")
  check_all(!grepl("[^A-Za-z]", country), "country", "must contain letters only")

  country <- toupper(country)
  networks <- lapply(country, download_iwik, collapse)
  networks <- as_list_of(networks, .ptype = ip_network())

  empty <- vapply(networks, length, 0) == 0
  if (all(empty)) {
    msg <- "Can't download networks for {.emph any} country"
    if (is_offline()) {
      msg <- c(msg, "i" = "Is your internet connection working?")
    } else {
      msg <- c(msg, "i" = "Is server down? {.url {url_iwik()}}")
      msg <- c(msg, "i" = "Check country codes are valid: {.val {country}}")
    }
    cli::cli_abort(msg, arg = "country")
  } else if (any(empty)) {
    cli::cli_warn(c(
      "Can't download networks for {length(country[empty])} countr{?y/ies}",
      "i" = "Check country codes are valid: {.val {country[empty]}}"
    ))
  }

  tibble::tibble(country, networks)
}

url_iwik <- function() {
  "https://www.iwik.org/ipcountry/"
}

download_iwik <- function(country, collapse) {
  url_ipv4 <- paste0(url_iwik(), country, ".cidr")
  url_ipv6 <- paste0(url_iwik(), country, ".ipv6")

  networks <- vctrs::vec_c(
    download_networks(url_ipv4, strict = FALSE),
    download_networks(url_ipv6, strict = TRUE)
  )

  if (collapse) {
    networks <- collapse_networks(networks)
  }

  networks
}

download_networks <- function(url, strict = TRUE, comment = "#") {
  lines <- try_fetch(
    suppressWarnings(readLines(url, warn = FALSE)),
    error = function(cnd) character()
  )

  # exclude commented lines
  if (nzchar(comment)) {
    lines <- lines[substr(lines, 1, nchar(comment)) != comment]
  }

  ip_network(lines, strict = strict)
}
