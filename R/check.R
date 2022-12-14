check_scalar <- function(x, arg = caller_arg(x), call = caller_env()) {
  if (length(x) != 1) {
    cli::cli_abort("{.arg {arg}} must have length 1, not length {length(x)}", arg = arg, call = call)
  }
}

check_bool <- function(x, arg = caller_arg(x), call = caller_env()) {
  if (!is_bool(x)) {
    cli::cli_abort("{.arg {arg}} must be TRUE or FALSE", arg = arg, call = call)
  }
}

check_integer <- function(x, arg = caller_arg(x), call = caller_env()) {
  if (!is_integerish(x)) {
    cli::cli_abort("{.arg {arg}} must be a integer vector", arg = arg, call = call)
  }
}

check_character <- function(x, arg = caller_arg(x), call = caller_env()) {
  if (!is_character(x)) {
    cli::cli_abort("{.arg {arg}} must be a character vector", arg = arg, call = call)
  }
}

check_address <- function(x, arg = caller_arg(x), call = caller_env()) {
  if (!is_ip_address(x)) {
    cli::cli_abort("{.arg {arg}} must be an {.cls ip_address} vector", arg = arg, call = call)
  }
}

check_network <- function(x, arg = caller_arg(x), call = caller_env()) {
  if (!is_ip_network(x)) {
    cli::cli_abort("{.arg {arg}} must be an {.cls ip_network} vector", arg = arg, call = call)
  }
}

check_ip <- function(x, arg = caller_arg(x), call = caller_env()) {
  if (!(is_ip_address(x) || is_ip_network(x))) {
    cli::cli_abort("{.arg {arg}} must be an {.cls ip_address} or {.cls ip_network} vector", arg = arg, call = call)
  }
}

check_all <- function(condition, arg, description, call = caller_env()) {
  multi <- length(condition) > 1

  if (!all(condition, na.rm = TRUE)) {
    msg <- if (multi) {
      ind <- which(!condition)
      c(
        paste0("Each value in {.arg {arg}} ", description),
        "x" = "Violations found at {length(ind)} location{?s}: {ind}"
      )
    } else {
      paste0("{.arg {arg}} ", description)
    }

    cli::cli_abort(msg, arg = arg, call = call)
  }
}
