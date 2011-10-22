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

#include "config.h"

// the arrays of int32s that hold each LED's 24 bit color values
uint32_t *pixels;
uint16_t numLEDs;
//uint8_t dataPin, clockPin;
extern uint8_t rainbow_enabled;

void ws2801_init(void);
//void ws2801_begin();
void ws2801_show();
void ws2801_setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
void ws2801_setPixelColor(uint16_t n, uint32_t c);
uint16_t numPixels(void);

