truncate_address <- function(x, max_width, ellipsis) {
  width_ellipsis <- pillar::get_extent(ellipsis)
  width_x <- pillar::get_extent(x)
  width_shown <- max_width - width_ellipsis

  too_wide <- which(!is.na(x) & width_x > max_width)

  x[too_wide] <- paste0(
    substr(x[too_wide], 1, ceiling(width_shown / 2)),
    ellipsis,
    substr(x[too_wide], width_x[too_wide] - floor(width_shown / 2) + 1, width_x[too_wide])
  )

  x
}

pretty_address <- function(addr) {
  addr <- gsub(".", pillar::style_subtle("."), addr, fixed = TRUE)
  addr <- gsub(":", pillar::style_subtle(":"), addr, fixed = TRUE)
  addr
}

pretty_cidr <- function(addr, pfx) {
  out <- paste0(
    pillar::align(pretty_address(addr), align = "right"),
    crayon::green(paste0(
      "/",
      pillar::align(pfx, align = "left")
    ))
  )

  out[is.na(addr)] <- NA
  out
}

pillar_shaft_ipaddress <- function(addr, pfx) {
  is_cidr <- !is.null(pfx)

  addr <- as.character(addr)
  pfx <- as.character(pfx)

  # require longest IPv4 address/network can be shown
  min_address_width <- 15

  if (is_cidr) {
    width <- pillar::get_max_extent(paste0(addr, "/", pfx))
    min_width <- min_address_width + 3
  } else {
    width <- pillar::get_max_extent(addr)
    min_width <- min_address_width
  }

  pillar::new_pillar_shaft(
    list(addr = addr, pfx = pfx),
    is_cidr = is_cidr,
    width = width,
    min_width = pmin(min_width, width),
    class = "pillar_shaft_ipaddress"
  )
}

#' @export
format.pillar_shaft_ipaddress <- function(x, width, ...) {
  min_width <- attr(x, "min_width")
  if (width < min_width) {
    abort(message = paste0("Need at least width ", min_width, ", requested ", width, "."))
  }

  is_cidr <- attr(x, "is_cidr")
  desired_width <- attr(x, "width")
  if (width < desired_width) {
    width_address <- if (is_cidr) {
      width - pillar::get_max_extent(x$pfx) - 1
    } else {
      width
    }
    x$addr <- truncate_address(x$addr, width_address, ellipsis = "...")
  }

  ornament <- if (is_cidr) {
    pretty_cidr(x$addr, x$pfx)
  } else {
    pretty_address(x$addr)
  }

  ornament[is.na(ornament)] <- pillar::style_na("NA")

  pillar::new_ornament(ornament, align = "right")
}


# Dynamically exported, see zzz.R
pillar_shaft.ip_address <- function(x, ...) {
  pillar_shaft_ipaddress(
    addr = x,
    pfx = NULL
  )
}

pillar_shaft.ip_network <- function(x, ...) {
  pillar_shaft_ipaddress(
    addr = network_address(x),
    pfx = prefix_length(x)
  )
}

pillar_shaft.ip_interface <- function(x, ...) {
  pillar_shaft_ipaddress(
    addr = as_ip_address(x),
    pfx = prefix_length(x)
  )
}
