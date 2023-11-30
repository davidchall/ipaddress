#ifndef __IPADDRESS_ASIO_CONFIG__
#define __IPADDRESS_ASIO_CONFIG__

// libc++ throws bogus warning about allocator<void> -- https://llvm.org/PR50299
#if defined(_LIBCPP_VERSION) && (_LIBCPP_VERSION < 13000) && defined(_LIBCPP_STD_VER) && (_LIBCPP_STD_VER == 17)
  #define _LIBCPP_DISABLE_DEPRECATION_WARNINGS
#endif

#endif
