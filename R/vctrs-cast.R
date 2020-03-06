#' Casting
#'
#' Double dispatch methods to support [vctrs::vec_cast()].
#'
#' @inherit vctrs::vec_cast return params
#' @keywords internal
#' @method vec_cast ip_address
#' @export
#' @export vec_cast.ip_address
vec_cast.ip_address <- function(x, to, ...) UseMethod("vec_cast.ip_address")

#' @method vec_cast.ip_address default
#' @export
vec_cast.ip_address.default <- function(x, to, ...) vec_default_cast(x, to)

#' @method vec_cast.ip_address ip_address
#' @export
vec_cast.ip_address.ip_address <- function(x, to, ...) x

#' @method vec_cast.ip_address character
#' @export
vec_cast.ip_address.character <- function(x, to, ...) ip_address(x)

#' @method vec_cast.character ip_address
#' @export
vec_cast.character.ip_address <- function(x, to, ...) print_address_wrapper(x)

#' @importFrom blob vec_cast.blob
#' @method vec_cast.blob ip_address
#' @export
vec_cast.blob.ip_address <- function(x, to, ...) packed_address_wrapper(x)


#' Casting
#'
#' Double dispatch methods to support [vctrs::vec_cast()].
#'
#' @inherit vctrs::vec_cast return params
#' @keywords internal
#' @method vec_cast ip_network
#' @export
#' @export vec_cast.ip_network
vec_cast.ip_network <- function(x, to, ...) UseMethod("vec_cast.ip_network")

#' @method vec_cast.ip_network default
#' @export
vec_cast.ip_network.default <- function(x, to, ...) vec_default_cast(x, to)

#' @method vec_cast.ip_network ip_network
#' @export
vec_cast.ip_network.ip_network <- function(x, to, ...) x

#' @method vec_cast.ip_network character
#' @export
vec_cast.ip_network.character <- function(x, to, ...) ip_network(x)

#' @method vec_cast.character ip_network
#' @export
vec_cast.character.ip_network <- function(x, to, ...) print_network_wrapper(x)
