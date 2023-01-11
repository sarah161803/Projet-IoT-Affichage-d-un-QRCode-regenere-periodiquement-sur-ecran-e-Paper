# IdoSens Base LoRaWAN :: QR Code Display

Display a QR Code on the e-paper screen.

The QR Code contains a URL which is the concatenation of 
* a base URL which can include an endpoint ID (least significant bytes of the DevEUI for instance),
* a pseudo random number (generated for a seed and a secret key),
* a 32-bit long timestamp (seconds since the GPS epoch ie 6/1/1980).

The pseudo random number and the timestamp are encoded in `base64`.

The QR Code can be changed periodically.

The base URL, the seed, the secret key, the period of change can be configured and updated using a downlink.

The RTC of the MCU is synchronized using the App Clock Sync specification.

If a GNSS module is connected to the board (UART,I2C) and if the URL is prefied by `geo:`, the QRCode includes the lattitude and the longitude. 
(for instance, [geo:45.1941477,5.7656245?q=FabMSTIC](geo:45.1941477,5.7656245?q=FabMSTIC))

## Build

```bash
export RIOTBASE=~/github/RIOT-OS/RIOT
make DEVEUI=1234567890ABCDEF APPEUI=0000000000000000 APPKEY=1234567890ABCDEF1234567890ABCDEF
```


## References
* https://github.com/RIOT-OS/RIOT/tree/master/tests/pkg_qr-code-generator
* https://github.com/nayuki/QR-Code-generator
* https://github.com/CampusIoT/orbimote/blob/master/field_test_device/app_clock.c
