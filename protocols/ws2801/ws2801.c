/*
 * Copyright (c) 2009 by Dirk Pannenbecker <dp@sd-gp.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */
 

#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "config.h"

#define BAUD 250000

#include "ws2801.h"

#ifndef WS2801_PIXEL_NUM
#define WS2801_PIXEL_NUM 3
#endif

// Example to control WS2801-based RGB LED Modules in a strand or strip
// Written by Adafruit - MIT license
// Ported to EtherSex by Shuairan
/*****************************************************************************/

void ws2801_init(void) {
  PIN_CLEAR(WS2801_CLOCK);
  PIN_CLEAR(WS2801_DATA);
  
  numLEDs = WS2801_PIXEL_NUM;
  
  pixels = malloc(numLEDs);
  for (uint16_t i=0; i< numLEDs; i++) {
    ws2801_setPixelColor(i, 255, 0, 0);
  }
}

uint16_t ws2801_numPixels(void) {
  return numLEDs;
}

void ws2801_show(void) {
    uint32_t data;
    PIN_CLEAR(WS2801_CLOCK); //digitalWrite(clockPin, LOW);
    _delay_us(1); //delay(1);
    
    // send all the pixels
    for (uint16_t p=0; p< numLEDs; p++) {
        data = pixels[p];
	// 24 bits of data per pixel
        for (int32_t i=0x800000; i>0; i>>=1) {
            PIN_CLEAR(WS2801_CLOCK); //digitalWrite(clockPin, LOW);
            if (data & i)
                PIN_SET(WS2801_DATA); //digitalWrite(dataPin, HIGH);
            else
                PIN_CLEAR(WS2801_DATA); //digitalWrite(dataPin, LOW);
            PIN_SET(WS2801_CLOCK); //digitalWrite(clockPin, HIGH);    // latch on clock rise
        }
    }
    // when we're done we hold the clock pin low for a millisecond to latch it
    PIN_CLEAR(WS2801_CLOCK); //digitalWrite(clockPin, LOW);
    _delay_us(1); //delay(1);
}

void ws2801_setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  uint32_t data;

  if (n > numLEDs) return;

  data = r;
  data <<= 8;
  data |= g;
  data <<= 8;
  data |= b;
  
  pixels[n] = data;
}

void ws2801_setPixel(uint16_t n, uint32_t c) {
  if (n > numLEDs) return;

  pixels[n] = c & 0xFFFFFF;
}

uint32_t ws2801_getPixel(uint16_t n) {
  if (n > numLEDs) return;

  return pixels[n];
}


/*
  -- Ethersex META --
  header(protocols/dmx/dmx.h)
  init(ws2801_init)
  timer(2, ws2801_show())
*/