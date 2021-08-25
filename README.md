# ATTiny TMP36 Smart Pixel

This simple device drives the color value displayed by a single NeoPixel
using the readinga from a TMP36 temperature sensor using an ATTiny85.

This code is build on [Arduino](https://arduino.cc), and uses [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore).

## Dependencies

- [Arduno IDE 1.18.5](https://www.arduino.cc/en/software) or [Arduino CLI](https://arduino.github.io/arduino-cli/)
- [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore)

## Building and uploading

Using the Arduino CLI to compile and upload using a USBTinyISP-compatible programmer, such
as the [Sparkfun Tiny AVR Programmer](https://www.sparkfun.com/products/11801):

```
arduino-cli compile -b ATTinyCore:avr:attinyx5 -u -t -P usbtinyisp
```

You can also invoke `build.sh`, which just executes this command.

If you just want to build the firmware, without uploading, try:

```
arduino-cli compile -b ATTinyCore:avr:attinyx5
```

If using the Ardunio ID, select `ATTinyCore > ATTiny25/45/85 (No bootloader)` in
Board Manager. The other board settings should be:

- Chip 'ATTiny85'
- Clock Source: '8 MHz (internal)'

Eveything else should be the defaults. 
