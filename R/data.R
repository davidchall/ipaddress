#' IPv4 address space allocation
#'
#' A dataset containing the registry of allocated blocks in IPv4 address space.
#'
#' @format A data frame with 122 rows and 3 variables:
#' \describe{
#'   \item{network}{Address block (an [`ip_network`] vector)}
#'   \item{allocation}{There are three types of allocation:
#'     \itemize{
#'       \item reserved
#'       \item managed by regional Internet registry (RIR)
#'       \item assigned to organization
#'     }
#'   }
#'   \item{label}{The RIR, organization or purpose for reservation}
#' }
#' @source \url{https://www.iana.org/assignments/ipv4-address-space}
#' @note Last updated 2020-08-18
#' @examples
#' iana_ipv4
#' @seealso [is_reserved()]
"iana_ipv4"


#' IPv6 address space allocation
#'
#' A dataset containing the registry of allocated blocks in IPv6 address space.
#'
#' @format A data frame with 47 rows and 3 variables:
#' \describe{
#'   \item{network}{Address block (an [`ip_network`] vector)}
#'   \item{allocation}{There are two types of allocation:
#'     \itemize{
#'       \item reserved
#'       \item managed by regional Internet registry (RIR)
#'     }
#'   }
#'   \item{label}{The RIR or purpose for reservation}
#' }
#' @source
#' \url{https://www.iana.org/assignments/ipv6-address-space}
#'
#' \url{https://www.iana.org/assignments/ipv6-unicast-address-assignments}
#' @note Last updated 2020-08-18
#' @examples
#' iana_ipv6
#' @seealso [is_reserved()]
"iana_ipv6"
