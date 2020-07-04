# kDS3231w1
This is an alternate version of kDS3231 library, modified to work with Wire1 interface on chips like ATmega328PB.
For installation and usage instructions, have a look at README.md in master branch.
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
