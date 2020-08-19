#' IPv4 address space allocation
#'
#' A dataset containing the registry of allocated blocks in IPv4 address space.
#'
#' @format A data frame with 122 rows and 3 variables:
#' \describe{
#'   \item{network}{Address block (an [`ip_network`] vector)}
#'   \item{allocation}{There are three types of allocation:
#'     \itemize{
#'       \item reserved by protocol
#'       \item managed by regional Internet registry (RIR)
#'       \item assigned to organization
#'     }
#'   }
#'   \item{organization}{The RIR or organization}
#' }
#' @source \url{https://www.iana.org/assignments/ipv4-address-space}
#' @note Last updated 2020-08-18
#' @examples
#' iana_ipv4
#' @seealso [is_reserved()]
"iana_ipv4"
