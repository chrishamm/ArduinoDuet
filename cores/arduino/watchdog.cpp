/*
  Copyright (c) 2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <asf.h>

#include "watchdog.h"
#include "wdt/wdt.h"

void watchdogEnable (uint32_t timeout)
{
	/* this assumes the slow clock is running at 32.768 kHz
	   watchdog frequency is therefore 32768 / 128 = 256 Hz */
	timeout = timeout * 256 / 1000; 
	if (timeout == 0)
	{
		timeout = 1;
	}
	else if (timeout > 0xFFF)
	{
		timeout = 0xFFF;
	}
	wdt_init (WDT, WDT_MR_WDRSTEN, (uint16_t)timeout, (uint16_t)timeout);
}

void watchdogDisable(void)
{
	wdt_disable (WDT);
}

void watchdogReset(void)
{
	wdt_restart (WDT);
}

// End
