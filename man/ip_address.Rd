% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/ip_address.R
\name{ip_address}
\alias{ip_address}
\title{Vector of IP addresses}
\usage{
ip_address(x = character())
}
\arguments{
\item{x}{A character vector of IP addresses, in dot-decimal notation (IPv4)
or hexadecimal notation (IPv6)}
}
\value{
An S3 vector of class \code{ip_address}
}
\description{
Construct a vector of IP addresses.
}
\details{
An address in IPv4 space uses 32-bits. It is usually represented
as 4 groups of 8 bits, each shown as decimal digits (e.g. \verb{192.168.0.1}).
This is known as dot-decimal notation.

An address in IPv6 space uses 128-bits. It is usually represented
as 8 groups of 16 bits, each shown as hexadecimal digits
(e.g. \verb{2001:0db8:85a3:0000:0000:8a2e:0370:7334}). This representation can
also be compressed by removing leading zeros and replacing consecutive
groups of zeros with double-colon (e.g. \verb{2001:db8:85a3::8a2e:370:7334}).
Finally, there is also the dual representation. This expresses the final
two groups as an IPv4 address (e.g. \verb{2001:db8:85a3::8a2e:3.112.115.52}).

The \code{ip_address()} constructor accepts a character vector of IP addresses
in these two formats. It checks whether each string is a valid IPv4 or IPv6
address, and converts it to an \code{ip_address} object. If the input is invalid,
a warning is emitted and \code{NA} is stored instead.

When casting an \code{ip_address} object back to a character vector using
\code{as.character()}, IPv6 addresses are reduced to their compressed representation.
A special case is IPv4-mapped IPv6 addresses (see \code{\link[=is_ipv4_mapped]{is_ipv4_mapped()}}), which
are returned in the dual representation (e.g. \verb{::ffff:192.168.0.1}).

\code{ip_address} vectors support a number of \link[=ip_operators]{operators}.
}
\examples{
# supports IPv4 and IPv6 simultaneously
ip_address(c("192.168.0.1", "2001:db8::8a2e:370:7334"))

# validates inputs and replaces with NA
ip_address(c("255.255.255.256", "192.168.0.1/32"))
}
\seealso{
\code{\link{ip_operators}}, \code{vignette("ip-data")}
}
