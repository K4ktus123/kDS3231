/*
 * kDS3231w1
 * 
 * Arduino library for DS3231 RTC on Wire1 interface
 * Copyright 2020 Bartosz Kozieł
 * 
 * This file is part of kDS3231 library.

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

#include <Arduino.h>
#include <Wire1.h>
#include <kDS3231w1.h>

int8_t dec2bcd(int8_t dec);
void wireTransmit(int address, int value);

kDS3231w1::kDS3231w1()
{
  Wire1.begin();
}

void kDS3231w1::wireTransmit(int address, int value)
{
  Wire1.beginTransmission(0x68);
  Wire1.write(address);
  Wire1.write(value);
  Wire1.endTransmission();
}

int8_t kDS3231w1::wireRequest(int address)
{
  Wire1.beginTransmission(0x68);
  Wire1.write(address);
  Wire1.endTransmission();
  Wire1.requestFrom(0x68, 1);
  return Wire1.read();
}

void kDS3231w1::clockClear()
{
  wireTransmit(0x02, wireRequest(0x02) & B00111111);
  wireTransmit(0x0E, B00000100);
  wireTransmit(0x0F, B00001000);
}

int8_t kDS3231w1::bcd2dec(int8_t bcd=0)
{
  int8_t dec=(bcd >> 4) * 10 + (bcd & B00001111);;
  return dec;
}

int8_t kDS3231w1::dec2bcd(int8_t dec=0)
{
  int8_t bcd=(dec/10) << 4 | (dec-((dec/10)*10));
  return bcd;
}

int8_t kDS3231w1::readSeconds()
{
  return bcd2dec(wireRequest(0x00));
}

int8_t kDS3231w1::readMinutes()
{
  return bcd2dec(wireRequest(0x01));
}

int8_t kDS3231w1::readHours()
{
  return bcd2dec(wireRequest(0x02));
}

int8_t kDS3231w1::readDay()
{
  return bcd2dec(wireRequest(0x03));
}

int8_t kDS3231w1::readDate()
{
  return bcd2dec(wireRequest(0x04));
}

int8_t kDS3231w1::readMonth()
{
  return bcd2dec(wireRequest(0x05) & 127);
}

int8_t kDS3231w1::readYear()
{
  return bcd2dec(wireRequest(0x06));
}

bool kDS3231w1::readCentury()
{
  return bcd2dec(wireRequest(0x05)) >> 7;
}

bool kDS3231w1::readEOSC()
{
  return !(wireRequest(0x0E) >> 7);
}

bool kDS3231w1::readBBSQW()
{
  return (wireRequest(0x0E) & B01111111) >> 6;
}

int kDS3231w1::readSQWFreq()
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

bool kDS3231w1::readINTCN()
{
  return (wireRequest(0x0E) & B00000111) >> 2;
}

bool kDS3231w1::readA1Enable()
{
  return (wireRequest(0x0E) & B00000011) >> 1;
}

bool kDS3231w1::readA2Enable()
{
  return wireRequest(0x0E) & B00000001;
}

int8_t kDS3231w1::readControl()
{
  return wireRequest(0x0E);
}

bool kDS3231w1::readOSF()
{
  return wireRequest(0x0F) >> 7;
}

bool kDS3231w1::read32KEnable()
{
  return (wireRequest(0x0F) & B00001111)  >> 3;
}

bool kDS3231w1::readBSY()
{
  return (wireRequest(0x0F) & B00000111)  >> 2;
}

bool kDS3231w1::readA2Trigger()
{
  return (wireRequest(0x0F) & B00000011)  >> 1;
}

bool kDS3231w1::readA1Trigger()
{
  return wireRequest(0x0F) & B00000001;
}

int8_t kDS3231w1::readStatus()
{
  return wireRequest(0x0F);
}

int8_t kDS3231w1::readOffset()
{
  return wireRequest(0x10);
}

double kDS3231w1::readTemp()
{
  return wireRequest(0x11) + ((wireRequest(0x12) >> 6) / 4);
}

char kDS3231w1::readA1Mode()
{
  int8_t val=(wireRequest(0x07) >> 7) | ((wireRequest(0x08) >> 6) & B00000010) | ((wireRequest(0x09) >> 5) & B00000100) | ((wireRequest(0x0A) >> 4) & B00001000);
  if(val == 0) {
    val = val+((wireRequest(0x0A) >> 6) & B00000001);
  }
  char A1Mode;
  switch(val) {
    case 0:
      A1Mode = 'D';
    case 1:
      A1Mode = 'd';
    case 8:
      A1Mode = 'h';
    case 12:
      A1Mode = 'm';
    case 14:
      A1Mode = 's';
    case 15:
     A1Mode = 'S';
  }
  return A1Mode;
}

char kDS3231w1::readA2Mode()
{
  int8_t val=(wireRequest(0x0B) >> 7) | ((wireRequest(0x0C) >> 6) & B00000010) | ((wireRequest(0x0D) >> 5) & B00000100);
  if(val == 0) {
    val = val+((wireRequest(0x0D) >> 6) & B00000001);
  }
  char A2Mode;
  switch(val) {
    case 0:
      A2Mode = 'D';
    case 1:
      A2Mode = 'd';
    case 4:
      A2Mode = 'h';
    case 6:
      A2Mode = 'm';
    case 7:
      A2Mode = 'M';
  }
  return A2Mode;
}

int8_t kDS3231w1::readA1Seconds()
{
  return bcd2dec(wireRequest(0x07) & B01111111);
}

int8_t kDS3231w1::readA1Minutes()
{
  return bcd2dec(wireRequest(0x08) & B01111111);
}

int8_t kDS3231w1::readA1Hours()
{
  return bcd2dec(wireRequest(0x09) & B01111111);
}

int8_t kDS3231w1::readA1Day()
{
  return bcd2dec(wireRequest(0x0A) & B00111111);
}

int8_t kDS3231w1::readA2Minutes()
{
  return bcd2dec(wireRequest(0x0B) & B01111111);
}

int8_t kDS3231w1::readA2Hours()
{
  return bcd2dec(wireRequest(0x0C) & B01111111);
}

int8_t kDS3231w1::readA2Day()
{
  return bcd2dec(wireRequest(0x0D) & B00111111);
}

void kDS3231w1::setSeconds(int8_t val)
{
  wireTransmit(0x00, dec2bcd(val));
}

void kDS3231w1::setMinutes(int8_t val)
{
  wireTransmit(0x01, dec2bcd(val));
}

void kDS3231w1::setHours(int8_t val) {
  wireTransmit(0x02, dec2bcd(val));
}

void kDS3231w1::setDay(int8_t val)
{
  wireTransmit(0x03, dec2bcd(val));
}

void kDS3231w1::setDate(int8_t val)
{
  wireTransmit(0x04, dec2bcd(val));
}

void kDS3231w1::setMonth(int8_t val)
{
  wireTransmit(0x05, dec2bcd(val));
}

void kDS3231w1::setYear(int8_t val)
{
  wireTransmit(0x06, dec2bcd(val));
}

void kDS3231w1::setOffset(int8_t val)
{
  wireTransmit(0x10, val);
}

void kDS3231w1::setControl(int8_t val)
{
  wireTransmit(0x0E, val);
}

void kDS3231w1::setStatus(int8_t val)
{
  wireTransmit(0x0F, val);
}

void kDS3231w1::setEOSC(bool val)
{
  if(val == 0) {
    wireTransmit(0x0E, (readControl() | B10000000));
  }
  else {
    wireTransmit(0x0E, (readControl() & B01111111));
  }
}

void kDS3231w1::setBBSQW(bool val)
{
  if(val == 0) {
    wireTransmit(0x0E, (readControl() & B10111111));
  }
  else {
    wireTransmit(0x0E, (readControl() | B01000000));
  }
}

void kDS3231w1::setINTCN(bool val)
{
  if(val == 1) {
    wireTransmit(0x0E, (wireRequest(0x0E) | B00000100));
  }
  else {
    wireTransmit(0x0E, (wireRequest(0x0E) & B11111011));
  }
}

void kDS3231w1::setSQWFreq(int val)
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

void kDS3231w1::setA1Enable(bool val)
{
  if(val == 1) {
    wireTransmit(0x0E, (wireRequest(0x0E) | B00000001));
  }
  else {
    wireTransmit(0x0E, (wireRequest(0x0E) & B11111110));
  }
}

void kDS3231w1::setA2Enable(bool val)
{
  if(val == 1) {
    wireTransmit(0x0E, (wireRequest(0x0E) | B00000010));
  }
  else {
    wireTransmit(0x0E, (wireRequest(0x0E) & B11111101));
  }
}

void kDS3231w1::clearA1Trigger()
{
  wireTransmit(0x0F, (wireRequest(0x0F) & B11111110));
}

void kDS3231w1::clearA2Trigger()
{
  wireTransmit(0x0F, (wireRequest(0x0F) & B11111101));
}

void kDS3231w1::set32KEnable(bool val)
{
  if(val == 1) {
    wireTransmit(0x0F, (wireRequest(0x0F) | B00001000));
  }
  else {
    wireTransmit(0x0F, (wireRequest(0x0F) & B11110111));
  }
}

void kDS3231w1::clearOSF()
{
  wireTransmit(0x0F, (wireRequest(0x0F) | B01111111));
}

void kDS3231w1::setA1Mode(char val)
{
  switch(val) {
    case 'D':
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) & B01111111));
    wireTransmit(0x0A, (wireRequest(0x0A) & B00111111));
    break;
    case 'd':
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) & B01111111));
    wireTransmit(0x0A, ((wireRequest(0x0A) & B01111111) | B01000000));
    break;
    case 'h':
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) & B01111111));
    wireTransmit(0x0A, (wireRequest(0x0A) | B11000000));
    break;
    case 'm':
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) & B01111111));
    wireTransmit(0x09, (wireRequest(0x09) | B10000000));
    wireTransmit(0x0A, (wireRequest(0x0A) | B10000000));
    break;
    case 's':
    wireTransmit(0x07, (wireRequest(0x07) & B01111111));
    wireTransmit(0x08, (wireRequest(0x08) | B10000000));
    wireTransmit(0x09, (wireRequest(0x09) | B10000000));
    wireTransmit(0x0A, (wireRequest(0x0A) | B10000000));
    break;
    case 'S':
    wireTransmit(0x07, (wireRequest(0x07) | B10000000));
    wireTransmit(0x08, (wireRequest(0x08) | B10000000));
    wireTransmit(0x09, (wireRequest(0x09) | B10000000));
    wireTransmit(0x0A, (wireRequest(0x0A) | B10000000));
    break;
  }
}

void kDS3231w1::setA2Mode(char val)
{
  switch(val) {
    case 'D':
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) & B01111111));
    wireTransmit(0x0D, (wireRequest(0x0D) & B00111111));
    break;
    case 'd':
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) & B01111111));
    wireTransmit(0x0D, ((wireRequest(0x0D) & B01111111) | B01000000));
    break;
    case 'h':
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) & B01111111));
    wireTransmit(0x0D, (wireRequest(0x0D) | B11000000));
    break;
    case 'm':
    wireTransmit(0x0B, (wireRequest(0x0B) & B01111111));
    wireTransmit(0x0C, (wireRequest(0x0C) | B10000000));
    wireTransmit(0x0D, (wireRequest(0x0D) | B10000000));
    break;
    case 'M':
    wireTransmit(0x0B, (wireRequest(0x0B) | B10000000));
    wireTransmit(0x0C, (wireRequest(0x0C) | B10000000));
    wireTransmit(0x0D, (wireRequest(0x0D) | B10000000));
    break;
  }
}

void kDS3231w1::setA1Seconds(int8_t val)
{
  wireTransmit(0x07, (wireRequest(0x07) & B10000000) | dec2bcd(val));
}

void kDS3231w1::setA1Minutes(int8_t val)
{
  wireTransmit(0x08, (wireRequest(0x08) & B10000000) | dec2bcd(val));
}

void kDS3231w1::setA1Hours(int8_t val)
{
  wireTransmit(0x09, (wireRequest(0x09) & B10000000) | dec2bcd(val));
}

void kDS3231w1::setA1Day(int8_t val)
{
  wireTransmit(0x0A, (wireRequest(0x0A) & B10000000) | dec2bcd(val));
}

void kDS3231w1::setA2Minutes(int8_t val)
{
  wireTransmit(0x0B, (wireRequest(0x0B) & B10000000) | dec2bcd(val));
}

void kDS3231w1::setA2Hours(int8_t val)
{
  wireTransmit(0x0C, (wireRequest(0x0C) & B10000000) | dec2bcd(val));
}

void kDS3231w1::setA2Day(int8_t val)
{
  wireTransmit(0x0D, (wireRequest(0x0D) & B10000000) | dec2bcd(val));
}

void kDS3231w1::forceTempConv()
{
  wireTransmit(0x0E, (wireRequest(0x0E) | B00100000));
}
