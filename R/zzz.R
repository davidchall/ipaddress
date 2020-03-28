# nocov start
.onLoad <- function(...) {
  s3_register("pillar::pillar_shaft", "ip_network")

  invisible()
}
# nocov end
