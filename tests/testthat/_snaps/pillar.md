# without truncation

    Code
      pillar::pillar_shaft(x)
    Output
      <pillar_ornament>
                                29.71.126.113/6  
                                               NA
                                           ::/0  
      9401:b71a:4193:9b47:4d74:f55b:fdd9:b2ba/101
                        2642:2f46:2d65:b800::/55 
    Code
      pillar::pillar_shaft(as_ip_network(x))
    Output
      <pillar_ornament>
                                  28.0.0.0/6  
                                            NA
                                        ::/0  
      9401:b71a:4193:9b47:4d74:f55b:f800:0/101
                     2642:2f46:2d65:b800::/55 
    Code
      pillar::pillar_shaft(as_ip_address(x))
    Output
      <pillar_ornament>
                                29.71.126.113
                                           NA
                                           ::
      9401:b71a:4193:9b47:4d74:f55b:fdd9:b2ba
                        2642:2f46:2d65:b800::

# with truncation

    Code
      print(pillar::pillar_shaft(x), width = 20)
    Output
      <pillar_ornament>
         29.71.126.113/6  
                        NA
                    ::/0  
      9401:b7...9:b2ba/101
      2642:2f...b800::/55 
    Code
      print(pillar::pillar_shaft(as_ip_network(x)), width = 20)
    Output
      <pillar_ornament>
              28.0.0.0/6  
                        NA
                    ::/0  
      9401:b7...f800:0/101
      2642:2f...b800::/55 
    Code
      print(pillar::pillar_shaft(as_ip_address(x)), width = 20)
    Output
      <pillar_ornament>
             29.71.126.113
                        NA
                        ::
      9401:b71a...dd9:b2ba
      2642:2f46...5:b800::

