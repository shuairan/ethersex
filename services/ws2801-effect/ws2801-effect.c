/*
 *
 * Copyright (c) 2011 by Maximilian Güntner <maximilian.guentner@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
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

/* Module description: the ws2801 effect module can alter ws2801 information to create animations and effects for
   headless setups or currently not animated devices */
#include <avr/pgmspace.h>
#include <stdlib.h>
#include "core/debug.h"
#include "protocols/ws2801/ws2801.h"
#include "ws2801-effect.h"

#ifdef WS2801_EFFECT_SUPPORT

#ifdef WS2801_EFFECT_RAINBOW
/* This function has been copied from the ethersex ws2801 module
   Author: Copyright (c) 2009 by Dirk Pannenbecker <dp@sd-gp.de>
 */
uint8_t rainbow_enabled = WS2801_EFFECT_DISABLED;
uint8_t color_r, color_g, color_b = 0;
#define RAINBOW_DELAY 42
void ws2801_effect_rainbow_colors(void)
{
	static uint8_t rainbow_step = 0;
	static uint16_t rainbow_delay = 0;
	if (rainbow_delay++ <= (RAINBOW_DELAY / WS2801_PIXEL_NUM)) return;
	rainbow_delay = 0;
	switch(rainbow_step) {
		case 0:
			if (color_g > 1) {
				color_g--;
				color_b++;
			} else {
				rainbow_step++;
			}
			break;
		case 1:
			if (color_r > 1) {
				color_r--;
				color_g++;
			} else {
				rainbow_step++;
			}
			break;
		case 2:
			if (color_b > 1) {
				color_b--;
				color_r++;
			} else {
				rainbow_step = 0;
			}
			break;
	}

	/*Copy colors to ws2801 storage*/
    for(uint16_t i=0;i<WS2801_EFFECT_RAINBOW_PIXELS;i++)
	{
        ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, color_b, color_g, color_r);
    }
    /*
	for(uint16_t i=0;i<WS2801_EFFECT_RAINBOW_PIXELS+(WS2801_EFFECT_RAINBOW_MARGIN*WS2801_EFFECT_RAINBOW_PIXELS);i++)
	{
#if (WS2801_EFFECT_RAINBOW_MARGIN > 0)
		for(uint8_t j=0;j<WS2801_EFFECT_RAINBOW_MARGIN;j++)
		{
			//set_dmx_channel(WS2801_EFFECT_RAINBOW_UNIVERSE, WS2801_EFFECT_RAINBOW_OFFSET+i,WS2801_EFFECT_RAINBOW_MARGIN_FILL);
            ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, WS2801_EFFECT_RAINBOW_MARGIN_FILL);
            i++;
		}
#endif 
*/
/*
		if(i%(WS2801_EFFECT_RAINBOW_MARGIN*3+3) == WS2801_EFFECT_RAINBOW_MARGIN)
            ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, color_r);
			//set_ws2801_channel(WS2801_EFFECT_RAINBOW_UNIVERSE,WS2801_EFFECT_RAINBOW_OFFSET+i,color_r);
		if(i%(WS2801_EFFECT_RAINBOW_MARGIN*3+3) == 2*WS2801_EFFECT_RAINBOW_MARGIN+1)
            ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, color_g);
			//set_ws2801_channel(WS2801_EFFECT_RAINBOW_UNIVERSE,WS2801_EFFECT_RAINBOW_OFFSET+i,color_g);
		if(i%(WS2801_EFFECT_RAINBOW_MARGIN*3+3) == 3*WS2801_EFFECT_RAINBOW_MARGIN+2)
			ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, color_b);
            //set_ws2801_channel(WS2801_EFFECT_RAINBOW_UNIVERSE,WS2801_EFFECT_RAINBOW_OFFSET+i,color_b);
*/
}
#endif /*Rainbow end*/
#ifdef WS2801_EFFECT_RANDOM
uint8_t random_enabled = WS2801_EFFECT_DISABLED;
uint8_t random_channels[WS2801_EFFECT_RANDOM_PIXELS] = {0};
void ws2801_effect_random_colors_gen(void)
{
	uint8_t red,green,blue;
	#ifndef WS2801_EFFECT_RANDOM_ALL
		red=rand()%256;
		green=rand()%256;
		blue=rand()%256;
	#endif
	for(uint8_t i=0;i<WS2801_EFFECT_RANDOM_PIXELS;i++)
	{
		#ifdef WS2801_EFFECT_RANDOM_ALL
		if(i%3 == 0)
		{
			red=rand()%256;
			green=rand()%256;
			blue=rand()%256;
		}	
		#endif
		if(i%3 == 0)
			random_channels[i]=red;
		if(i%3 == 1)
			random_channels[i]=green;
		if(i%3 == 2)
			random_channels[i]=blue;
		
	}
}
void ws2801_effect_random_colors_show()
{
	for(uint8_t i=0;i<WS2801_EFFECT_RANDOM_PIXELS;i++)
	{
        ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, random_channels[0], random_channels[1], random_channels[2]);
        
        /*
		uint8_t tmp_value=get_ws2801_channel(WS2801_EFFECT_RANDOM_UNIVERSE,WS2801_EFFECT_RANDOM_OFFSET+i);
		uint8_t target_value=random_channels[(i+1)/(WS2801_EFFECT_RANDOM_MARGIN+1)-1];
		if(tmp_value > target_value)
			ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, color_r);
            //set_ws2801_channel(WS2801_EFFECT_RANDOM_UNIVERSE,WS2801_EFFECT_RANDOM_OFFSET+i,tmp_value-1);
		else if (tmp_value < target_value)
			ws2801_setPixelColor(WS2801_EFFECT_RAINBOW_OFFSET+i, color_r);
            //set_ws2801_channel(WS2801_EFFECT_RANDOM_UNIVERSE,WS2801_EFFECT_RANDOM_OFFSET+i,tmp_value+1);
		//else == : we do nothing, everything's set
        */
	}
}
#endif /*Random end*/

void ws2801_effect_init()
{
#ifdef WS2801_EFFECT_RAINBOW
	color_r = 255;
	color_g = 128;
	color_b = 0;
#endif
}
void ws2801_effect_process()
{
	#ifdef WS2801_EFFECT_RAINBOW
	if(rainbow_enabled == WS2801_EFFECT_ENABLED)
		ws2801_effect_rainbow_colors();
	#endif
	#ifdef WS2801_EFFECT_RANDOM
	if(random_enabled == WS2801_EFFECT_ENABLED)
	{
		static uint16_t counter=0;
		if(counter == 0)
		{
			//20 seconds have passed, generate new colors
			counter=500;
			ws2801_effect_random_colors_gen();
		}
		counter--;
		ws2801_effect_random_colors_show();
	}
	#endif
}
#endif
/*
   -- Ethersex META --
   header(services/ws2801-effect/ws2801-effect.h)
   init(ws2801_effect_init)
   timer(2,ws2801_effect_process())
*/
