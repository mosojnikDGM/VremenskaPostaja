# VremenskaPostaja
BandaVremenskaPostaja

1.  Prenesi repo
2.  Pripravi okolje. Navodila -> https://docs.heltec.cn/#/en/user_manual/how_to_install_esp32_Arduino
3.  Namesti gonilnik -> https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
4.  V CMD bodi znotraj mape Vremenska postaj
5.  git submodule init
6.  git submodule update
7.  Kopiraj mapo Heltec_ESP32 v .\Documents\Arduino\libraries
8.  Izberi WIFI_LoRa_32_V2
9.  Izberi pravi COM port
10. Programiraj
11. Pushaj na svoj branch
12. Na javnih računalnikih počisti git svojih podatkov -> git config --global --unset-all oz. brez --global samo za svojo mapo

                                |     |
                                \\_V_//
                                \/=|=\/
                                 [=v=]
                               __\___/_____
                              /..[  _____  ]
                             /_  [ [  M /] ]
                            /../.[ [ M /@] ]
                           <-->[_[ [M /@/] ]
                          /../ [.[ [ /@/ ] ]
     _________________]\ /__/  [_[ [/@/ C] ]
    <_________________>>0---]  [=\ \@/ C / /
       ___      ___   ]/000o   /__\ \ C / /
          \    /              /....\ \_/ /
       ....\||/....           [___/=\___/
      .    .  .    .          [...] [...]
     .      ..      .         [___/ \___]
     .    0 .. 0    .         <---> <--->
  /\/\.    .  .    ./\/\      [..]   [..]
 / / / .../|  |\... \ \ \    _[__]   [__]_
/ / /       \/       \ \ \  [____>   <____]