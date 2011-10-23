/*
 *
 * Copyright (c) 2011 by Sascha Riedinger <s.riedinger@gmail.com>
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
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "core/debug.h"
#include "config.h"
#include "protocols/ws2801/ws2801.h"
#include "protocols/ecmd/ecmd-base.h"

int16_t parse_cmd_ws2801_get_pixel(char *cmd, char *output, uint16_t len)
{
	uint16_t ret=0, pixel=0;
	if (cmd[0]!=0) ret = sscanf_P(cmd, PSTR("%u"), &pixel);
	if(ret == 1)
	{
		if (pixel >= WS2801_PIXEL_NUM)
			return ECMD_ERR_PARSE_ERROR;
		itoa(ws2801_getPixel(pixel), output, 16);
		return ECMD_FINAL(strlen(output));
	}
	else
		return ECMD_ERR_PARSE_ERROR;
}

int16_t parse_cmd_ws2801_set_pixels(char *cmd, char *output, uint16_t len)
{
    uint16_t startpixel=0, val1=0,val2=0,val3=0, pixelcounter=0, i=3;
    if (cmd[0]!=0) {
        sscanf_P(cmd, PSTR("%u"), &startpixel);
        if (startpixel >= WS2801_PIXEL_NUM)
            return ECMD_ERR_PARSE_ERROR;
        
        while (cmd[i]!=0){           //read and write all values
			sscanf_P(cmd+i, PSTR(" %2x%2x%2x"),&val1, &val2, &val3);
			/*if(set_dmx_channel(universe,startchannel+channelcounter,value))
				return ECMD_ERR_WRITE_ERROR;
			*/
            ws2801_setPixelColor(startpixel+pixelcounter, val1, val2, val3);
            pixelcounter++;
			do{                         //search for next space
				i++;
				if(cmd[i]==0) break;
			}while(cmd[i]!=' ');
		}

		return ECMD_FINAL_OK;
	}
	else
		return ECMD_ERR_PARSE_ERROR;

}
int16_t parse_cmd_ws2801_set_pixel_rgb(char *cmd, char *output, uint16_t len)
{
    uint8_t ret=0, pixel=0, r=0, g=0, b=0;
    ret = sscanf_P(cmd, PSTR("%hhu %hhu %hhu %hhu"), &pixel, &r, &g, &b);
    if(ret == 4)
	{
		if (pixel >= WS2801_PIXEL_NUM)
            return ECMD_ERR_PARSE_ERROR;
        
        ws2801_setPixelColor(pixel, r, g, b);
        return ECMD_FINAL_OK;
    }
    else
		return ECMD_ERR_PARSE_ERROR;
    
}

int16_t parse_cmd_ws2801_get_nums(char *cmd, char *output, uint16_t len)
{
	itoa(WS2801_PIXEL_NUM, output, 10);
	return ECMD_FINAL(strlen(output));
}

/*
   -- Ethersex META --
   block([[WS2801]] commands)
   ecmd_feature(ws2801_get_pixel, "ws2801 get",, Return pixel value) 
   ecmd_feature(ws2801_set_pixels, "ws2801 set",, Set pixel(s) values) 
   ecmd_feature(ws2801_get_nums, "ws2801 nums",, How many pixels)
   ecmd_feature(ws2801_set_pixel_rgb, "ws2801 rgb", PIXEL R G B, Set one pixel with rgb values)
 */
