# ggip

<details>

* Version: 0.3.0
* GitHub: https://github.com/davidchall/ggip
* Source code: https://github.com/cran/ggip
* Date/Publication: 2022-11-10 00:50:02 UTC
* Number of recursive dependencies: 73

Run `revdep_details(, "ggip")` for more info

</details>

## Newly broken

*   checking examples ... ERROR
    ```
    Running examples in ‘ggip-Ex.R’ failed
    The error most likely occurred in:
    
    > ### Name: geom_hilbert_outline
    > ### Title: Hilbert curve outline
    > ### Aliases: geom_hilbert_outline
    > 
    > ### ** Examples
    > 
    > p <- ggplot() + coord_ip() + theme_ip_light()
    ...
     37. ├─dplyr::select(., "x", "y", "xend", "yend")
     38. ├─dplyr::mutate(...)
     39. ├─ggip:::squares_to_sides(., closed)
     40. │ └─... %>% dplyr::select(-"xmid", -"ymid")
     41. ├─dplyr::select(., -"xmid", -"ymid")
     42. ├─dplyr::mutate(...)
     43. └─ggip::network_to_cartesian(...)
     44.   └─cli::cli_abort("{.arg network} must be an {.cls ip_network} vector.")
     45.     └─rlang::abort(...)
    Execution halted
    ```

*   checking tests ...
    ```
      Running ‘testthat.R’
     ERROR
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      Error in `dplyr::summarize(., generate_curve_outline(ip, curve_order, coord, 
          closed))`: Problem while computing `..1 = generate_curve_outline(ip, curve_order, coord, closed)`.
      i The error occurred in row 1.
      Caused by error in `network_to_cartesian()`:
      ! `network` must be an <ip_network> vector.
      ── Error ('test-geom-hilbert-outline.R:84'): networks outside 2D grid raise warning ──
      Error in `dplyr::summarize(., generate_curve_outline(ip, curve_order, coord, 
          closed))`: Problem while computing `..1 = generate_curve_outline(ip, curve_order, coord, closed)`.
      i The error occurred in row 1.
      Caused by error in `network_to_cartesian()`:
      ! `network` must be an <ip_network> vector.
      
      [ FAIL 4 | WARN 0 | SKIP 5 | PASS 63 ]
      Error: Test failures
      Execution halted
    ```

## In both

*   checking whether package ‘ggip’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      /Users/davidhall/code/ipaddress/revdep/library.noindex/ggip/Rcpp/include/Rcpp/internal/r_coerce.h:255:7: warning: 'sprintf' is deprecated: This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of sprintf(3), it is highly recommended that you use snprintf(3) instead. [-Wdeprecated-declarations]
    See ‘/Users/davidhall/code/ipaddress/revdep/checks.noindex/ggip/new/ggip.Rcheck/00install.out’ for details.
    ```

