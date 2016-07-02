/*
  Copyright (c) 2011 Arduino.  All right reserved.

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

#include "Arduino.h"

extern "C" void pinModeDuet(uint32_t ulPin, enum PinMode ulMode, uint32_t debounceCutoff)
{
	if (ulPin > MaxPinNumber)
	{
		return;
	}

	const PinDescription& pinDesc = g_APinDescription[ulPin];
    if (pinDesc.ulPinType == PIO_NOT_A_PIN)
    {
        return;
    }

	switch (ulMode)
	{
		case INPUT:
			/* Enable peripheral for clocking input */
			pmc_enable_periph_clk(pinDesc.ulPeripheralId);
			pio_configure(
					pinDesc.pPort,
					PIO_INPUT,
					pinDesc.ulPin,
					(debounceCutoff == 0) ? 0 : PIO_DEBOUNCE);
			if (debounceCutoff != 0)
			{
				pio_set_debounce_filter(pinDesc.pPort, pinDesc.ulPin, debounceCutoff);	// enable debounce filer with specified cutoff frequency
			}
			break;

		case INPUT_PULLUP:
			/* Enable peripheral for clocking input */
			pmc_enable_periph_clk(pinDesc.ulPeripheralId);
			pio_configure(
					pinDesc.pPort,
					PIO_INPUT,
					pinDesc.ulPin,
					(debounceCutoff == 0) ? PIO_PULLUP : PIO_PULLUP | PIO_DEBOUNCE);
			if (debounceCutoff != 0)
			{
				pio_set_debounce_filter(pinDesc.pPort, pinDesc.ulPin, debounceCutoff);	// enable debounce filer with specified cutoff frequency
			}
			break;

#if SAM4E
		case INPUT_PULLDOWN:
			/* Enable peripheral for clocking input */
			pmc_enable_periph_clk(pinDesc.ulPeripheralId);
			pio_pull_down(pinDesc.pPort, pinDesc.ulPin, 1);
			pio_configure(
					pinDesc.pPort,
					PIO_INPUT,
					pinDesc.ulPin,
					(debounceCutoff == 0) ? 0 : PIO_DEBOUNCE);
			if (debounceCutoff != 0)
			{
				pio_set_debounce_filter(pinDesc.pPort, pinDesc.ulPin, debounceCutoff);	// enable debounce filer with specified cutoff frequency
			}
			break;
#endif

		case OUTPUT_LOW:
			pio_configure(
					pinDesc.pPort,
					PIO_OUTPUT_0,
					pinDesc.ulPin,
					pinDesc.ulPinConfiguration);

			/* if all pins are output, disable PIO Controller clocking, reduce power consumption */
			if (pinDesc.pPort->PIO_OSR == 0xffffffff)
			{
				pmc_disable_periph_clk(pinDesc.ulPeripheralId);
			}
			break;

		case OUTPUT_HIGH:
			pio_configure(
					pinDesc.pPort,
					PIO_OUTPUT_1,
					pinDesc.ulPin,
					pinDesc.ulPinConfiguration);

			/* if all pins are output, disable PIO Controller clocking, reduce power consumption */
			if (pinDesc.pPort->PIO_OSR == 0xffffffff)
			{
				pmc_disable_periph_clk(pinDesc.ulPeripheralId);
			}
			break;

		case AIN:
			pio_pull_up(pinDesc.pPort, pinDesc.ulPin, 0);		// turn off pullup
#if SAM4E
			pio_pull_down(pinDesc.pPort, pinDesc.ulPin, 0);		// turn off pulldown
#endif
			// Ideally we should record which pins are being used as analog inputs, then we can disable the clock
			// on any PIO that is being used solely for outputs and ADC inputs. But for now we don't do that.
			break;

		case SPECIAL:
			ConfigurePin(pinDesc);
			break;

		default:
			break;
	}
}

// This has now been optimised to speed it up, so it may no longer be used to enable the pullup resistor on an input pin (use mode INPUT_PULLUP instead).
extern "C"  void digitalWrite(uint32_t ulPin, bool ulVal)
{
	if (ulPin <= MaxPinNumber)
	{
		const PinDescription& pinDesc = g_APinDescription[ulPin];
		if (pinDesc.ulPinType != PIO_NOT_A_PIN)
		{
			if (ulVal)		// we make use of the fact that LOW is zero and HIGH is nonzero
			{
				pinDesc.pPort->PIO_SODR = pinDesc.ulPin;
			}
			else
			{
				pinDesc.pPort->PIO_CODR = pinDesc.ulPin;
			}
		}
	}
}

extern "C" bool digitalRead(uint32_t ulPin)
{
	if (ulPin > MaxPinNumber)
	{
		return false;
	}

	const PinDescription& pinDesc = g_APinDescription[ulPin];
	if (pinDesc.ulPinType == PIO_NOT_A_PIN)
    {
        return false ;
    }

	return (bool)pio_get(pinDesc.pPort, PIO_INPUT, pinDesc.ulPin);
}

extern "C" void setPullup(uint32_t ulPin, bool en)
{
	if (ulPin <= MaxPinNumber)
	{
		const PinDescription& pinDesc = g_APinDescription[ulPin];
		if (pinDesc.ulPinType != PIO_NOT_A_PIN)
		{
			pio_pull_up(g_APinDescription[ulPin].pPort, g_APinDescription[ulPin].ulPin, (uint32_t)en) ;
		}
	}
}

// End
