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

# Dynamically exported, see zzz.R
pillar_shaft.ip_network <- function(x, ...) {

  # decompose
  addr <- as.character(network_address(x))
  pfx <- as.character(prefix_length(x))

  out <- paste0(
    align(addr, align = "right"),
    crayon::green("/"),
    crayon::green(align(pfx, align = "left"))
  )

  out[is.na(x)] <- NA
  pillar::new_pillar_shaft_simple(out, align = "right")
}
