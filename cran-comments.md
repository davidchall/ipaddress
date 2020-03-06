## Release summary

This is a patch release to fix CRAN errors on Solaris.
I've checked that the errors were resolved by building on RHub.


## Test environments
* macOS 10.15 (local), R 3.6.2
* macOS 10.15 (GitHub Actions), R 3.6.2
* macOS 10.15 (GitHub Actions), R-devel
* Ubuntu 16.04 (GitHub Actions), R 3.2.5, 3.3.3, 3.4.4, 3.5.3, 3.6.2
* Ubuntu 16.04 (RHub), R 3.6.2
* Fedora Linux (RHub), R-devel
* Debian Linux (RHub), R-devel
* Windows Server 2019 (GitHub Actions), R 3.6.2
* Windows Server 2008 R2 SP1 32/64 bit (RHub), R-devel
* Oracle Solaris 10, x86, 32-bit (RHub), R-patched

## R CMD check results

0 errors | 0 warnings | 1 note

Possibly mis-spelled words in DESCRIPTION:
  IP (2:13, 10:53)
  IPv (12:43, 12:52)

The acronyms IP, IPv4 and IPv6 are spelled correctly.


## Reverse dependencies
There are currently no reverse dependencies for this package.
