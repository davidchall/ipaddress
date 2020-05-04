# nocov start
.onLoad <- function(...) {
  s3_register("pillar::pillar_shaft", "ip_address")
  s3_register("pillar::pillar_shaft", "ip_network")
  s3_register("pillar::pillar_shaft", "ip_interface")

  invisible()
}
# nocov end
