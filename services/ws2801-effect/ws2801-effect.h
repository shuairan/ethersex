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
#include "config.h"
#include <stdlib.h>

#ifdef WS2801_EFFECT_SUPPORT

#define WS2801_EFFECT_DISABLED 0
#define WS2801_EFFECT_ENABLED 1

#ifdef WS2801_EFFECT_RAINBOW
extern uint8_t rainbow_enabled;

void WS2801_effect_rainbow_colors(void);
#endif
#ifdef WS2801_EFFECT_RANDOM
extern uint8_t random_enabled;
void WS2801_effecT_random_colors_gen(void);
void WS2801_effecT_random_colors_show(void);
#endif

void WS2801_effect_init(void);
void WS2801_effect_process(void);

#endif