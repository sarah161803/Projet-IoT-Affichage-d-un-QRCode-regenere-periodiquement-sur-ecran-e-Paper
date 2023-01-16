# IdoSens Base LoRaWAN :: QR Code Display

Display a QR Code on the e-paper screen.

The QR Code contains a URL which is the concatenation of 
* a base URL,
* a identification number for the case,
* a 32-bit long timestamp (seconds since the GPS epoch ie 6/1/1980).
* a signature number (generated with a secret key sent with a LoraWan liaison to sign the identification number and the timestamp)

The QR Code can be changed periodically.

The base URL, the secret key, the period of change can be configured and updated using a downlink.

## Build

```bash
export RIOTBASE=~/github/RIOT-OS/RIOT
make DEVEUI=1234567890ABCDEF APPEUI=0000000000000000 APPKEY=1234567890ABCDEF1234567890ABCDEF
```


## References
* https://github.com/RIOT-OS/RIOT/tree/master/tests/pkg_qr-code-generator
* https://github.com/nayuki/QR-Code-generator
* https://github.com/CampusIoT/orbimote/blob/master/field_test_device/app_clock.c
