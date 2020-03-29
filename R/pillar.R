# taken from pillar package
align <- function(x, width = NULL, align = c("left", "right")) {
  align <- match.arg(align)
  extent <- pillar::get_extent(x)
  if (is.null(width)) {
    width <- max(extent)
  }
  spaces <- pmax(width - extent, 0L)
  if (align == "left") {
    paste0(x, strrep(" ", spaces))
  } else {
    paste0(strrep(" ", spaces), x)
  }
}

pretty_address <- function(addr) {
  addr <- as.character(addr)

  addr <- gsub(".", pillar::style_subtle("."), addr, fixed = TRUE)
  addr <- gsub(":", pillar::style_subtle(":"), addr, fixed = TRUE)

  addr
}

pretty_cidr <- function(addr, pfx) {
  addr <- pretty_address(addr)
  pfx <- as.character(pfx)

  out <- paste0(
    align(addr, align = "right"),
    crayon::green(paste0(
      "/",
      align(pfx, align = "left")
    ))
  )

  out[is.na(addr)] <- NA
  out
}

# Dynamically exported, see zzz.R
pillar_shaft.ip_address <- function(x, ...) {
  out <- pretty_address(x)
  pillar::new_pillar_shaft_simple(out, align = "right")
}

pillar_shaft.ip_network <- function(x, ...) {
  out <- pretty_cidr(network_address(x), prefix_length(x))
  pillar::new_pillar_shaft_simple(out, align = "right")
}

pillar_shaft.ip_interface <- function(x, ...) {
  out <- pretty_cidr(as_ip_address(x), prefix_length(x))
  pillar::new_pillar_shaft_simple(out, align = "right")
}
