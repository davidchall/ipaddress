ipv4_aton <- function(x) {
  octets <- strsplit(x, ".", fixed = TRUE)
  shift_bits <- function(x, y) bitwOr(bitwShiftL(x, 8L), y)
  vapply(octets, function(x) Reduce(shift_bits, as.integer(x)), 0L)
}

ipv4_ntoa <- function(x) {
  paste(
    bitwAnd(bitwShiftR(x, 24L), 255L),
    bitwAnd(bitwShiftR(x, 16L), 255L),
    bitwAnd(bitwShiftR(x, 8L), 255L),
    bitwAnd(bitwShiftR(x, 0L), 255L),
    sep = "."
  )
}

split_cidr <- function(x) {
  parts <- strsplit(x, "/", fixed = TRUE)
  setNames(do.call(Map, c(f = c, parts)), c("address", "prefix"))
}

paste_cidr <- function(address, prefix) {
  paste(address, prefix, sep = "/")
}
