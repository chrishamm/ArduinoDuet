# Arduino Duet board files
Arduino board files for RepRap Duet, Duet WiFi, Duet Ethernet and RADDS electronics

These files are based on dc42's CoreNG project, which was originally based on my own previous Arduino Duet board package. However, this fork is mainly designed to be easily included by the Arduino IDE which shall allow users to build their own independent sketches via Arduino and to compile RepRapFirmware on multiple platforms (Windows, Linux and OS X).

In contrast to the previous Duet board package this package is based on ASF 3.31 and supports more recent ATSAM processors including the one used in the next-generation Duet platforms.

Thanks to dc42, support for PWM outputs via TCs and the use of on-chip hardware ADC schedulers has been added. Besides, the USB interface is now fully interrupt and DMA-driven instead of polled.

# Installation

To download and install this package via Arduino IDE, perform the following steps:

1. Start Arduino IDE
2. Go to "File" -> "Preferences"
3. Add http://reprapfirmware.org/chrishamm/package_reprap_index.json to "Additional Baords Manager URLs"
4. Go to "Tools" -> "Board" -> "Boards Manager"
5. Install the Arduino SAM boards package
6. Scroll down to the last item. You should see "Duet platform" there
7. Click on it and press "Install"
8. Once finished, you should be able to compile your own Arduino sketches per Arduino IDE. For RepRapFirmware use the supplied Makefile (ch fork)

License: GPLv3, see http://www.gnu.org/licenses/gpl-3.0.en.html.
