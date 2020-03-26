/*kDS3231
 * 
 * Arduino library for DS3231 RTC
 * Copyright 2019, 2020 Bartosz Kozieł
 * 
 * version 1.0 - initial release
 * 
 * This file is part of kDS3231 library.

    kDS3231 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    kDS3231 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with kDS3231.  If not, see <http://www.gnu.org/licenses/>.
 *
 *This example shows how to utilize square wave output functionality.
 *It works just like a blink sketch, but it uses DS3231 to achieve very precise blinking frequency.
 *Make sure to connect the SQW/INT output to interrupt 0 input on Arduino board. On Uno it's on pin 2.
 */

#include <kDS3231.h>
#include <Wire.h>

kDS3231 clock;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(2, INPUT_PULLUP);
  clock.setINTCN(0);
  clock.setSQWfreq(1);
  attachInterrupt(0, interrupt, CHANGE);
}

void interrupt() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void loop() {
  
}
