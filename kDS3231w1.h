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
 */

#ifndef kDS3231w1_h
#define kDS3231w1_h

#include <Arduino.h>

class kDS3231w1
{
  public:
  kDS3231w1(void);
  void clockClear();
  int8_t readSeconds();
  int8_t readMinutes();
  int8_t readHours();
  int8_t readDay();
  int8_t readDate();
  int8_t readMonth();
  int8_t readYear();
  bool readCentury();
  bool readEOSC();
  bool readBBSQW();
  int readSQWFreq();
  bool readINTCN();
  bool readA1Enable();
  bool readA2Enable();
  int8_t readControl();
  bool readOSF();
  bool read32KEnable();
  bool readBSY();
  bool readA2Trigger();
  bool readA1Trigger();
  int8_t readStatus();
  int8_t readOffset();
  double readTemp();
  char readA1Mode();
  char readA2Mode();
  int8_t readA1Seconds();
  int8_t readA1Minutes();
  int8_t readA1Hours();
  int8_t readA1Day();
  int8_t readA2Minutes();
  int8_t readA2Hours();
  int8_t readA2Day();
  void setSeconds(int8_t val);
  void setMinutes(int8_t val);
  void setHours(int8_t val);
  void setDay(int8_t val);
  void setDate(int8_t val);
  void setMonth(int8_t val);
  void setYear(int8_t val);
  void setOffset(int8_t val);
  void setControl(int8_t val);
  void setStatus(int8_t val);
  void setEOSC(bool val);
  void setBBSQW(bool val);
  void setINTCN(bool val);
  void setSQWFreq(int val);
  void setA1Enable(bool val);
  void setA2Enable(bool val);
  void clearA1Trigger();
  void clearA2Trigger();
  void set32KEnable(bool val);
  void clearOSF();
  void setA1Mode(char val);
  void setA2Mode(char val);
  void setA1Seconds(int8_t val);
  void setA1Minutes(int8_t val);
  void setA1Hours(int8_t val);
  void setA1Day(int8_t val);
  void setA2Minutes(int8_t val);
  void setA2Hours(int8_t val);
  void setA2Day(int8_t val);
  void forceTempConv();
  
  private:
  void wireTransmit(int address, int value);
  int8_t wireRequest(int address);
  int8_t bcd2dec(int8_t bcd);
  int8_t dec2bcd(int8_t dec);
};

#endif
