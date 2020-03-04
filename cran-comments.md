## Resubmission

This is a resubmission. In this version I have:

* Removed single quotes from acronyms in the DESCRIPTION file and instead write out the full version in parentheses.


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

## R CMD check results

0 errors | 0 warnings | 3 notes

Maintainer: 'David Hall <david.hall.physics@gmail.com>'

* New submission

* Possibly mis-spelled words in DESCRIPTION:
     IP (2:13, 10:39)
     IPv (12:22, 12:31)

The acronyms IP, IPv4 and IPv6 are spelled correctly.

* checking for non-standard things in the check directory ... NOTE
Found the following files/directories:
  'ipaddress-Ex_x64.Rout' 'tests_i386' 'tests_x64'
  'examples_i386' 'examples_x64' 'ipaddress-Ex_i386.Rout'
  
These seem to be specific to the RHub build environment.


## Reverse dependencies
This is a new release, so there are no reverse dependencies.
