/*kDS3231w1
 * 
 * Arduino library for DS3231 RTC on Wire1 interface
 * Copyright 2020 Bartosz Kozieł
 * 
 * This file is part of kDS3231w1 library.

    kDS3231w1 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    kDS3231w1 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with kDS3231w1.  If not, see <http://www.gnu.org/licenses/>.

 *This example will print time and date into the serial monitor. Make sure to set it to 9600 baud.
 */

#include <kDS3231w1.h>

kDS3231w1 clock;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(clock.readHours() < 10) { Serial.print("0"); }
  Serial.print(clock.readHours());
  Serial.print(":");
  if(clock.readMinutes() < 10) { Serial.print("0"); }
  Serial.print(clock.readMinutes());
  Serial.print(":");
  if(clock.readSeconds() < 10) { Serial.print("0"); }
  Serial.println(clock.readSeconds());
  switch(clock.readDay()) {
    case 1:
    Serial.print("Monday, ");
    break;
    case 2:
    Serial.print("Tuesday, ");
    break;
    case 3:
    Serial.print("Wednesday, ");
    break;
    case 4:
    Serial.print("Thursday, ");
    break;
    case 5:
    Serial.print("Friday, ");
    break;
    case 6:
    Serial.print("Saturday, ");
    break;
    case 7:
    Serial.print("Sunday, ");
    break;
  }
  Serial.print(clock.readDate());
  Serial.print(".");
  Serial.print(clock.readMonth());
  Serial.print(".");
  Serial.print("20");
  if(clock.readYear() < 10) { Serial.print("0"); }
  Serial.println(clock.readYear());
  Serial.println(" ");
  delay(1000);
}
