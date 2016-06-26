# Arduino Duet board files
Arduino board files for RepRap Duet and Duet WiFi electronics

These files are based on dc42's CoreNG project, which was originally based on my own previous Arduino Duet board package, however this fork is designed to be easily included by the Arduino IDE. This shall allow users to build their own sketches via Arduino and to compile RepRapFirmware independently from ASF on multiple platforms (Windows, Linux and OS X).

In contrast to the previous Duet board package this package is based on ASF 3.31 and supports more recent ATSAM processors including the one used in the next-generation Duet platform.

Thanks to dc42, support for PWM outputs via TCs and the use of on-chip hardware ADC schedulers has been added. Besides, the USB interface is now fully interrupt and DMA-driven instead of polled.

License: GPLv3, see http://www.gnu.org/licenses/gpl-3.0.en.html.
