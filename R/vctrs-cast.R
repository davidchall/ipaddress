#' @method vec_cast ip_address
#' @export
#' @export vec_cast.ip_address
#' @rdname ipaddress-vctrs
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
vec_cast.character.ip_address <- function(x, to, ...) wrap_print_address(x)

#' @method vec_cast.ip_address blob
#' @export
vec_cast.ip_address.blob <- function(x, to, ...) wrap_decode_bytes(x)

#' @importFrom blob vec_cast.blob
#' @method vec_cast.blob ip_address
#' @export
vec_cast.blob.ip_address <- function(x, to, ...) blob::new_blob(wrap_encode_bytes(x))



#' @method vec_cast ip_network
#' @export
#' @export vec_cast.ip_network
#' @rdname ipaddress-vctrs
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
vec_cast.character.ip_network <- function(x, to, ...) wrap_print_network(x)



#' @method vec_cast ip_interface
#' @export
#' @export vec_cast.ip_interface
#' @rdname ipaddress-vctrs
vec_cast.ip_interface <- function(x, to, ...) UseMethod("vec_cast.ip_interface")

#' @method vec_cast.ip_interface default
#' @export
vec_cast.ip_interface.default <- function(x, to, ...) vec_default_cast(x, to)

#' @method vec_cast.ip_interface ip_interface
#' @export
vec_cast.ip_interface.ip_interface <- function(x, to, ...) x

#' @method vec_cast.ip_address ip_interface
#' @export
vec_cast.ip_address.ip_interface <- function(x, to, ...) {
  new_ip_address(
    field(x, "address1"),
    field(x, "address2"),
    field(x, "address3"),
    field(x, "address4"),
    field(x, "is_ipv6")
  )
}

#' @method vec_cast.ip_network ip_interface
#' @export
vec_cast.ip_network.ip_interface <- function(x, to, ...) {
  ip_network(x, field(x, "prefix"), strict = FALSE)
}

#' @method vec_cast.ip_interface character
#' @export
vec_cast.ip_interface.character <- function(x, to, ...) ip_interface(x)

#' @method vec_cast.character ip_interface
#' @export
vec_cast.character.ip_interface <- function(x, to, ...) wrap_print_network(x)
