/*kDS3231
 * 
 * Arduino library for DS3231 RTC
 * Copyright 2019, 2020 Bartosz Kozieł
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
 */

#ifndef kDS3231_h
#define kDS3231_h

#include <Arduino.h>

class kDS3231
{
  public:
  kDS3231(void);
  void clockClear();
  int8_t readSeconds();
  int8_t readMinutes();
  int8_t readHours();
  int8_t readDay();
  int8_t readDate();
  int8_t readMonth();
  int8_t readYear();
  int8_t readCentury();
  int8_t readEOSC();
  int8_t readBBSQW();
  int readSQWFreq();
  int8_t readINTCN();
  int8_t readA1enable();
  int8_t readA2enable();
  int8_t readControl();
  int8_t readOSF();
  int8_t read32K();
  int8_t readBSY();
  int8_t readA2trigger();
  int8_t readA1trigger();
  int8_t readStatus();
  int8_t readOffset();
  double readTemp();
  int8_t readA1mode();
  int8_t readA2mode();
  int8_t readA1seconds();
  int8_t readA1minutes();
  int8_t readA1hours();
  int8_t readA1day();
  int8_t readA2minutes();
  int8_t readA2hours();
  int8_t readA2day();
  void setSeconds(int8_t val);
  void setMinutes(int8_t val);
  void setHours(int8_t val);
  void setDay(int8_t val);
  void setDate(int8_t val);
  void setMonth(int8_t val);
  void setYear(int val);
  void setOffset(int8_t val);
  void setControl(int8_t val);
  void setStatus(int8_t val);
  void setEOSC(bool val);
  void setBBSQW(bool val);
  void setINTCN(bool val);
  void setSQWfreq(int val);
  void setA1enable(bool val);
  void setA2enable(bool val);
  void clearA1trigger();
  void clearA2trigger();
  void set32Kenable(bool val);
  void clearOSF();
  void setA1mode(char val);
  void setA2mode(char val);
  void setA1seconds(int8_t val);
  void setA1minutes(int8_t val);
  void setA1hours(int8_t val);
  void setA1day(int8_t val);
  void setA2minutes(int8_t val);
  void setA2hours(int8_t val);
  void setA2day(int8_t val);
  void forceTempConv();
  
  private:
  void wireTransmit(int address, int value);
  int8_t wireRequest(int address);
  int8_t bcd2dec(int8_t bcd);
  int8_t dec2bcd(int8_t dec);
};

#endif

