# kDS3231
The DS3231 is a low-cost, extremely accurate I²C real-time clock (RTC) with an integrated temperature-compensated crystal oscillator (TCXO) and crystal. It's made by Maxim Integrated.

kDS3231 is an Arduino library for that chip. It *should* support all its functionalities, although I'm still not sure if I included everything.
#### If you find any bugs please report them immediately.

## Wire1 interface
I'm happy to tell you that now you can use this library with the second I²C interface on boards such as Arduino Mega or Due, as well as on ATmega328PB.
You can download the modified version [here](https://github.com/K4ktus123/kDS3231/tree/w1).

## Installation
1. Download the repository,
2. Extract the ZIP file,
3. Rename the extracted folder to "kDS3231" or "kDS3231w1", depending on the version you downloaded,
4. Place the extracted folder in libraries folder inside your Arduino folder,
5. Enjoy!

## TODO
- Check for bugs
- Add more example sketches
- Add to Arduino IDE library mnager

## Commands description

#### Read functions

clockClear - clears configuration registers 0x0E and 0x0F. Recommended on startup, not required though.

readSeconds - returns seconds value read from the RTC.

readMinutes - returns minutes value read from the RTC.

readHours - returns hours value read from the RTC. Only 24 hour mode supported, but it's easy to convert that value to 12 hour format.

readDay - returns days value read from the RTC.

readMonth - returns months value read from the RTC.

readYear - returns years value read from the RTC.

readEOSC - returns inverted value of EOSC bit in control register. Tells if the oscillator is enabled.

readBBSQW - returns value of BBSQW in control register. Tells if batery-backed square wave is enabled.

readSQWFreq - returns frequency of square wave output. Possible values are 1, 1024, 4096 and 8192.

readINTCN - returns value of INTCN bit in control register. Tells if SQW/INT output is set to output square wave with set frequency or an alarm interrupt trigger signal.

readA1Enable - returns A1E bit in control register. Tells if alarm 1 is enabled.

readA2Enable - returns A2E bit in control register. Tells if alarm 2 is enabled.

readControl - returns value of control register.

readOSF - returns value of OSF bit in status register. Tells if oscillator was stopped because of for example low battery voltage. Have a look in the datasheet for further reference.

read32KEnable - returns value of EN32kHz bit in status register. Tells if 32K output is enabled.

readBSY - returns value of BSY bit in ststus register. Tells if the IC is currently executing TCXO functions.

readA1Trigger - returns value of A1F bit in control register. Tells if alarm 1 was triggered.

readA2Trigger - returns value of A2F bit in control register. Tells if alarm 2 was triggered.

readStatus - returns value of status register.

readOffset - returns value of offset register.

readTemp - returns temperature measured by the IC in degrees C.

readA1Mode - returns alarm 1 mode. Possible values are:
D - when date, minutes, hours and seconds match.
d - when day, minutes, hours and seconds match.
h - when minutes, hours and seconds match.
m - when when minutes and seconds match.
s - when seconds match.
S - every second.

readA2Mode - returns alarm 2 mode. Possible values are:
D - when date, minutes and hours match.
d - when day, minutes and hours match.
h - when minutes and hours match.
m - when minutes match.
M - every minute. (at 0 second)

readA1Seconds - returns value of seconds for alarm 1.

readA1Minutes - returns value of minutes for alarm 1.

readA1Hours - returns value of hours for alarm 1.

readA1Day - returns value of days for alarm 1.

readA2Minutes - returns value of minutes for alarm 2.

readA2Hours - returns value of hours for alarm 2.

readA2Day - returns value of days for alarm 2.

#### Set functions

setSeconds - sets seconds.

setMinutes - sets minutes.

setHours - sets hours.

setDay - sets day of week.

setDate - sets day of month.

setMonth - sets month.

setYear - sets year. Possible values are 0-99.

setOffset - sets value of offset register.

setControl - sets value of control register.

setStatus - sets value of status register.

setEOSC - sets inverted EOSC bit value in control register. When set to 0, DS3231 stops the oscilltor when powered by battery.

setBBSQW - sets BBSQW bit in control register. Enables or disables battery-backed square wave output.

setINTCN - sets INTCN bit in control register. When set to 0, a square wave is output on SQW/INT pin. When set to 1, outputs alarm interrupts.

setSQWFreq - sets frequency of SQW output. Possible values are 1, 1024, 4096 and 8192.

forceTempConv - sets CONV bit in control register and forces the RTC to update the temperature reading and execute TCXO algorithm.

setA1Enable - sets A1E bit in control registers. Set to 1 to enable alarm 1, 0 to disable it.

setA2Enable - sets A2E bit in control registers. Set to 1 to enable alarm 2, 0 to disable it.

clearA1Trigger - clears A1F bit in status register.

clearA2Trigger - clears A2F bit in status register.

set32KEnable - sets EN32kHz bit in status register. Setting to 1 enables 32K output.

clearOSF - clears OSF bit in status register.

setA1Mode - sets alarm 1 mode. Possible values are:
D - when date, minutes, hours and seconds match.
d - when day, minutes, hours and seconds match.
h - when minutes, hours and seconds match.
m - when when minutes and seconds match.
s - when seconds match.
S - every second.

setA1Seconds - sets seconds for alarm 1.

setA1Minutes - sets minutes for alarm 1.

setA1Hours - sets hours for alarm 1.

setA1Day - sets day for alarm 1.

setA2Mode - sets alarm 2 mode. Possible values are:
D - when date, minutes and hours match.
d - when day, minutes and hours match.
h - when minutes and hours match.
m - when minutes match.
M - every minute. (at 0 second)

setA2Minutes - sets minutes for alarm 2.

setA2Hours - sets hours for alarm 2.

setA2Day - sets day for alarm 2.

When setting up an alarm, make sure to clear its trigger. When setting the mode, put the letter in single quotes, like this
```
setA1Mode('S')
```
Don't forget to enable it, as well as set the INTCN bit to one.

Have a look at DS3231 datasheet (included in extras folder) for further reference.
