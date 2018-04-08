/*
* light weight WS2812 lib V2.1 - Arduino support
*
* Controls WS2811/WS2812/WS2812B RGB-LEDs
* Author: Matthias Riegler
*
* Mar 07 2014: Added Arduino and C++ Library
*
* September 6, 2014:	Added option to switch between most popular color orders
*						(RGB, GRB, and BRG) --  Windell H. Oskay
*
* License: GNU GPL v2 (see License.txt)
*/

#include "WS2812.h"
#include <stdlib.h>

WS2812::WS2812(uint16_t num_leds) {
	count_led = num_leds;

	pixels = (uint8_t*)malloc(count_led*3);
}

uint8_t WS2812::set_crgb_at(uint16_t index, uint8_t r, uint8_t g, uint8_t b) {
	if(index < count_led) {

		uint16_t tmp;
		tmp = index * 3;

		// Offset for GRB
		pixels[tmp] = g;
		pixels[tmp + 1] = r;
		pixels[tmp + 2] = b;
		return 0;
	}
	return 1;
}

void WS2812::sync() {
	*ws2812_port_reg |= pinMask; // Enable DDR
	ws2812_sendarray_mask(pixels,3*count_led,pinMask,(uint8_t*) ws2812_port,(uint8_t*) ws2812_port_reg );
}

WS2812::~WS2812() {
	free(pixels);

}

void WS2812::setOutput(uint8_t pin) {
	pinMask = digitalPinToBitMask(pin);
	ws2812_port = portOutputRegister(digitalPinToPort(pin));
	ws2812_port_reg = portModeRegister(digitalPinToPort(pin));
}
