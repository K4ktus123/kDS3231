# kDS3231
The DS3231 is a low-cost, extremely accurate
I²C real-time clock (RTC) with an integrated
temperature-compensated crystal oscillator (TCXO)
and crystal. It's made by Maxim Integrated.

kDS3231 is an Arduino library for that chip.
It *should* support all its functionalities, although
I'm still not sure if I included everything.
If you find any bugs please report them immediately.

## Installation
1. Download the repository
2. Extract the ZIP file
3. Place the extracted folder in libraries folder inside your Arduino folder
4. Enjoy!

## TODO
- check for bugs
- add more example sketches
- create a version for Wire1 interace on chips like ATmega328PB
- Figure out how to create boards manager link for easy installation

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

readINTCN - returns value of INTCN bit in control register. Tells if SQW/INT output is set to output square wave with set frequency of trigger alarm interrupt.

readA1enable - returns A1E bit in control register. Tells if alarm 1 is enabled.

readA2enable - returns A2E bit in control register. Tells if alarm 2 is enabled.

readControl - returns value of control register.

readOSF - returns value of OSF bit in status register. Tells if oscillator was stopped because of for example low battery voltage. Have a look in the datasheet for further reference.

read32K - returns value of EN32kHz bit in status register. Tells if 32K output is enabled.

readBSY - returns value of BSY bit in ststus register. Tells if the IC is currently executing TCXO functions.

readA1trigger - returns value of A1F bit in control register. Tells if alarm 1 was triggered.

readA2trigger - returns value of A2F bit in control register. Tells if alarm 2 was triggered.

readStatus - returns value of status register.

readOffset - returns value of offset register.

readTemp - returns temperature read by the IC in degrees C.

readA1mode - returns alarm 1 mode. Possible values are:
0 - when day, minutes, hours and seconds match. Day interpreted as day of month.
1 - when day, minutes, hours and seconds match. Day interpreted as day of week.
8 - when minutes, hours and seconds match.
12 - when when minutes and seconds match.
14 - when seconds match
15 - every second

readA2mode - returns alarm 2 mode. Possible values are:
0 - when day, minutes and hours match. Day interpreted as day of month.
1 - when day, minutes and hours match. Day interpreted as day of week.
4 - when minutes and hours match.
6 - when minutes match.
7 - every minute (at 0 second)

readA1seconds - returns value of seconds for alarm 1.

readA1minutes - returns value of minutes for alarm 1.

readA1hours - returns value of hours for alarm 1.

readA1day - returns value of days for alarm 1.

readA2minutes - returns value of minutes for alarm 2.

readA2hours - returns value of hours for alarm 2.

readA2day - returns value of days for alarm 2.

#### Set functions

setSeconds - sets seconds. Takes 8-bit int value.

setMinutes - sets minutes. Takes 8-bit int value.

setHours - sets hours. Takes 8-bit int value.

setDay - sets day of week. Takes 8-bit int value.

setDate - sets day of month. Takes 8-bit int value.

setMonth - sets month. Takes 8-bit int value.

setYear - sets year. Takes int value (16-bit).

setOffset - sets value of offset register. Takes 8-bit int value.

setControl - sets value of control register. Takes 8-bit int value.

setStatus - sets value of status register. Takes 8-bit int value.

setEOSC - sets inverted EOSC bit value in control register. When set to 0, DS3231 stops the oscilltor when powered by battery. Takes bool value.

setBBSQW - sets BBSQW bit in control register. Enables or disables battery-backed square wave output. Takes bool value.

setINTCN - sets INTCN bit in control register. When set to 0, a square wave is output on SQW/INT pin. When set to 1, outputs alarm interrupts. Takes bool value.

setSQWfreq - sets frequency of SQW output. Possible values are 1, 1024, 4096 and 8192. Takes int value (16-bit).

forceTempConv - sets CONV bit in control register and forces the RTC to update the temperature reading and execute TCXO algorithm.

setA1enable - sets A1E bit in control registers. Set to 1 to enable alarm 1, 0 to disable it. Takes bool value.

setA2enable - sets A2E bit in control registers. Set to 1 to enable alarm 2, 0 to disable it. Takes bool value.

clearA1trigger - clears A1F bit in status register.

clearA2trigger - clears A2F bit in status register.

set32Kenable - sets EN32kHz bit in status register. Setting to 1 enables 32K output. Takes bool value.

clearOSF - clears OSF bit in status register.

setA1mode - sets alarm 1 mode. Possible values are:
D - when date, minutes, hours and seconds match.
d - when day, minutes, hours and seconds match.
h - when minutes, hours and seconds match.
m - when when minutes and seconds match.
s - when seconds match
S - every second

setA1seconds - sets seconds for alarm 1. Takes 8-bit int value.

setA1minutes - sets minutes for alarm 1. Takes 8-bit int value.

setA1hours - sets hours for alarm 1. Takes 8-bit int value.

setA1day - sets day for alarm 1. Takes 8-bit int value.

setA2mode - sets alarm 2 mode. Possible values are:
D - when date, minutes and hours match.
d - when day, minutes and hours match.
h - when minutes and hours match.
m - when minutes match.
M - every minute (at 0 second)

setA2minutes - sets minutes for alarm 2. Takes 8-bit int value.

setA2hours - sets hours for alarm 2. Takes 8-bit int value.

setA2day - sets day for alarm 2. Takes 8-bit int value.

When setting up an alarm, make sure to clear its trigger. When setting the mode, put the letter in single quotes, like this
```
setA1mode('S')
```
Don't forget to enable it, as well as set the INTCN bit to one.

Have a look at DS3231 datasheet for further reference.
