/*
 * kDS3231
 * 
 * Arduino library for DS3231 RTC
 * Copyright 2019, 2020 Bartosz Kozieł
 * 
 * version 1.0 - initial release
 * version 1.1 - added forceTempConv function and changed the way library decodes temperature info
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

#include <Arduino.h>
#include <Wire.h>
#include <kDS3231.h>

int8_t dec2bcd(int8_t dec);
void wireTransmit(int address, int value);

kDS3231::kDS3231()
{
  Wire.begin();
}

void kDS3231::wireTransmit(int address, int value)
{
  Wire.beginTransmission(0x68);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

int8_t kDS3231::wireRequest(int address)
{
  Wire.beginTransmission(0x68);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 1);
  return Wire.read();
}

void kDS3231::clockClear()
{
  wireTransmit(0x02, wireRequest(0x02) & B00111111);
  wireTransmit(0x0E, B00000100);
  wireTransmit(0x0F, B00001000);
}

int8_t kDS3231::bcd2dec(int8_t bcd=0)
{
  int8_t dec=(bcd >> 4) * 10 + (bcd & B00001111);;
  return dec;
}

int8_t kDS3231::dec2bcd(int8_t dec=0)
{
  int8_t bcd=(dec/10) << 4 | (dec-((dec/10)*10));
  return bcd;
}

int8_t kDS3231::readSeconds()
{
  return bcd2dec(wireRequest(0x00));
}

int8_t kDS3231::readMinutes()
{
  return bcd2dec(wireRequest(0x01));
}

int8_t kDS3231::readHours()
{
  return bcd2dec(wireRequest(0x02));
}

int8_t kDS3231::readDay()
{
  return bcd2dec(wireRequest(0x03));
}

int8_t kDS3231::readDate()
{
  return bcd2dec(wireRequest(0x04));
}

int8_t kDS3231::readMonth()
{
  return bcd2dec(wireRequest(0x05));
}

int kDS3231::readYear()
{
  return 2000 + bcd2dec(wireRequest(0x02));
}

int8_t kDS3231::readEOSC()
{
  return !(wireRequest(0x0E) >> 7);
}

int8_t kDS3231::readBBSQW()
{
  return (wireRequest(0x0E) & B01111111) >> 6;
}

int kDS3231::readSQWFreq()
{
  switch((wireRequest(0x0E) & B00011111) >> 3) {
    case 0:
    return 1;
    case 1:
    return 1024;
    case 2:
    return 4096;
    case 3:
    return 8192;
  }
}

int8_t kDS3231::readINTCN()
{
  return (wireRequest(0x0E) & B00000111) >> 2;
}

int8_t kDS3231::readA1enable()
{
  return (wireRequest(0x0E) & B00000011) >> 1;
}

int8_t kDS3231::readA2enable()
{
  return wireRequest(0x0E) & B00000001;
}

int8_t kDS3231::readControl()
{
  return wireRequest(0x0E);
}

int8_t kDS3231::readOSF()
{
  return wireRequest(0x0F) >> 7;
}

int8_t kDS3231::read32K()
{
  return (wireRequest(0x0F) & B00001111)  >> 3;
}

int8_t kDS3231::readBSY()
{
  return (wireRequest(0x0F) & B00000111)  >> 2;
}

int8_t kDS3231::readA2trigger()
{
  return (wireRequest(0x0F) & B00000011)  >> 1;
}

int8_t kDS3231::readA1trigger()
{
  return wireRequest(0x0F) & B00000001;
}

int8_t kDS3231::readStatus()
{
  return wireRequest(0x0F);
}

int8_t kDS3231::readOffset()
{
  return wireRequest(0x10);
}

double kDS3231::readTemp()
{
  //int8_t a = wireRequest(0x11);
  //double b = wireRequest(0x12) >> 6;
  //return a+(b/4);
  return wireRequest(0x11) + ((wireRequest(0x12) >> 6) / 4);
}

int8_t kDS3231::readA1mode()
{
  int8_t val=(wireRequest(0x07) >> 7) | ((wireRequest(0x08) >> 6) & B00000010) | ((wireRequest(0x09) >> 5) & B00000100) | ((wireRequest(0x0A) >> 4) & B00001000);
  if(val == 0) {
    return val+((wireRequest(0x0A) >> 6) & B00000001);
  }
  else {
    return val;
  }
}

int8_t kDS3231::readA2mode()
{
  int8_t val=(wireRequest(0x0B) >> 7) | ((wireRequest(0x0C) >> 6) & B00000010) | ((wireRequest(0x0D) >> 5) & B00000100);
  if(val == 0) {
    return val+((wireRequest(0x0D) >> 6) & B00000001);
  }
  else {
    return val;
  }
}

int8_t kDS3231::readA1seconds()
{
  return bcd2dec(wireRequest(0x07) & B01111111);
}

int8_t kDS3231::readA1minutes()
{
  return bcd2dec(wireRequest(0x08) & B01111111);
}

int8_t kDS3231::readA1hours()
{
  return bcd2dec(wireRequest(0x09) & B01111111);
}

int8_t kDS3231::readA1day()
{
  return bcd2dec(wireRequest(0x0A) & B00111111);
}

int8_t kDS3231::readA2minutes()
{
  return bcd2dec(wireRequest(0x0B) & B01111111);
}

int8_t kDS3231::readA2hours()
{
  return bcd2dec(wireRequest(0x0C) & B01111111);
}

int8_t kDS3231::readA2day()
{
  return bcd2dec(wireRequest(0x0D) & B00111111);
}

void kDS3231::setSeconds(int8_t val)
{
  wireTransmit(0x00, dec2bcd(val));
}

void kDS3231::setMinutes(int8_t val)
{
  wireTransmit(0x01, dec2bcd(val));
}

void setHours(int8_t val) {
  wireTransmit(0x02, dec2bcd(val));
}

void kDS3231::setDay(int8_t val)
{
  wireTransmit(0x03, dec2bcd(val));
}

void kDS3231::setDate(int8_t val)
{
  wireTransmit(0x04, dec2bcd(val));
}

void kDS3231::setMonth(int8_t val)
{
  wireTransmit(0x05, dec2bcd(val));
}

void kDS3231::setYear(int val)
{
  wireTransmit(0x06, dec2bcd(val-2000));
}

void kDS3231::setOffset(int8_t val)
{
  wireTransmit(0x10, val);
}

void kDS3231::setControl(int8_t val)
{
  wireTransmit(0x0E, val);
}

void kDS3231::setStatus(int8_t val)
{
  wireTransmit(0x0F, val);
}

void kDS3231::setEOSC(bool val)
{
  if(val == 0) {
    wireTransmit(0x0E, (readControl() | B10000000));
  }
  else {
    wireTransmit(0x0E, (readControl() & B01111111));
  }
}

void kDS3231::setBBSQW(bool val)
{
  if(val == 0) {
    wireTransmit(0x0E, (readControl() & B10111111));
  }
  else {
    wireTransmit(0x0E, (readControl() | B01000000));
  }
}

void kDS3231::setINTCN(bool val)
{
  if(val == 1) {
    wireTransmit(0x0E, (wireRequest(0x0E) | B00000100));
  }
  else {
    wireTransmit(0x0E, (wireRequest(0x0E) & B11111011));
  }
}

void kDS3231::setSQWfreq(int val)
{
  switch(val) {
    case 1:
    wireTransmit(0x0E, (readControl() & B11100111));
    break;
    case 1024:
    wireTransmit(0x0E, ((readControl() & B11101111) | B00001000));
    break;
    case 4096:
    wireTransmit(0x0E, ((readControl() & B11110111) | B00010000));
    break;
    case 8192:
    wireTransmit(0x0E, (readControl() | B00011000));
    break;
  }
}

void kDS3231::setA1enable(bool val)
{
  if(val == 1) {
    wireTransmit(0x0E, (wireRequest(0x0E) | B00000001));
  }
  else {
    wireTransmit(0x0E, (wireRequest(0x0E) & B11111110));
  }
}

void kDS3231::setA2enable(bool val)
{
  if(val == 1) {
    wireTransmit(0x0E, (wireRequest(0x0E) | B00000010));
  }
  else {
    wireTransmit(0x0E, (wireRequest(0x0E) & B11111101));
  }
}

void kDS3231::clearA1trigger()
{
  wireTransmit(0x0F, (wireRequest(0x0F) & B11111110));
}

void kDS3231::clearA2trigger()
{
  wireTransmit(0x0F, (wireRequest(0x0F) & B11111101));
}

void kDS3231::set32Kenable(bool val)
{
  if(val == 1) {
    wireTransmit(0x0F, (wireRequest(0x0F) | B00001000));
  }
  else {
    wireTransmit(0x0F, (wireRequest(0x0F) & B11110111));
  }
}

void kDS3231::clearOSF()
{
  wireTransmit(0x0F, (wireRequest(0x0F) | B01111111));
}

void kDS3231::setA1mode(int8_t val)
{
  switch(val) {
    case 0:
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) & B01111111));
    wireTransmit(0x0A, (wireRequest(0x0A) & B00111111));
    break;
    case 1:
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) & B01111111));
    wireTransmit(0x0A, ((wireRequest(0x0A) & B01111111) | B01000000));
    break;
    case 8:
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) & B01111111));
    wireTransmit(0x0A, (wireRequest(0x0A) | B11000000));
    break;
    case 12:
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) | B10000000));
    wireTransmit(0x0A, (wireRequest(0x0A) | B10000000));
    break;
    case 14:
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) | B10000000));
    wireTransmit(0x09, (wireRequest(0x09) | B10000000));
    wireTransmit(0x0A, (wireRequest(0x0A) | B10000000));
    break;
    case 15:
    wireTransmit(0x07, (wireRequest(0x07) | B10000000));
    wireTransmit(0x08, (wireRequest(0x08) | B10000000));
    wireTransmit(0x09, (wireRequest(0x09) | B10000000));
    wireTransmit(0x0A, (wireRequest(0x0A) | B10000000));
    break;
  }
}

void kDS3231::setA2mode(int8_t val)
{
  switch(val) {
    case 0:
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) & B01111111));
    wireTransmit(0x0D, (wireRequest(0x0D) & B00111111));
    break;
    case 1:
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) & B01111111));
    wireTransmit(0x0D, ((wireRequest(0x0D) & B01111111) | B01000000));
    break;
    case 4:
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) & B01111111));
    wireTransmit(0x0D, (wireRequest(0x0D) | B11000000));
    break;
    case 6:
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) | B10000000));
    wireTransmit(0x0D, (wireRequest(0x0D) | B10000000));
    break;
    case 7:
    wireTransmit(0x0B, (wireRequest(0x0B) | B10000000));
    wireTransmit(0x0C, (wireRequest(0x0C) | B10000000));
    wireTransmit(0x0D, (wireRequest(0x0D) | B10000000));
    break;
  }
}

void kDS3231::setA1seconds(int8_t val)
{
  wireTransmit(0x07, dec2bcd(val));
}

void kDS3231::setA1minutes(int8_t val)
{
  wireTransmit(0x08, dec2bcd(val));
}

void kDS3231::setA1hours(int8_t val)
{
  wireTransmit(0x09, dec2bcd(val));
}

void kDS3231::setA1day(int8_t val)
{
  wireTransmit(0x0A, dec2bcd(val));
}

void kDS3231::setA2minutes(int8_t val)
{
  wireTransmit(0x0B, dec2bcd(val));
}

void kDS3231::setA2hours(int8_t val)
{
  wireTransmit(0x0C, dec2bcd(val));
}

void kDS3231::setA2day(int8_t val)
{
  wireTransmit(0x0D, dec2bcd(val));
}

void kDS3231::forceTempConv()
{
  wireTransmit(0x0E, (wireRequest(0x0E) | B00100000));
}
