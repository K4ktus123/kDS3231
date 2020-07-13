# kDS3231w1
This is an alternate version of kDS3231 library, modified to work with Wire1 interface on boards like Arduino Mega or Due, as well as ATmega328PB.
For installation and usage instructions, have a look at [README.md in master branch](https://github.com/K4ktus123/kDS3231/blob/master/README.md).
Both versions are compatible, so in order to make your code use this version, simply replace
```
#include <kDS3231.h>
```
with
```
#include <kDS3231w1.h>
```
and
```
kDS3231 clock;
```
with
```
kDS3231w1 clock;
```
