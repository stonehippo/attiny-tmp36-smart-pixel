 /*
	ATTiny85 Temperature Smart Pixel

	Copyright (c) 2021 George White <stonehippo@gmail.com>

	A really simple device, built around an ATTiny85, a TMP36 analog temp sensor,
	and a single RGBW NeoPixel. Doesn't do a lot: reads the temp sensor in the
	main loop, and updates the color of the Neopixel based on that. Color ranges
	from red (hottest) to blue (coolest).

	To keep things simple, this whole thing runs at 3.3V/8Mhz. This let's us use
	an LD117 @ 3.3V, with either a Li-ion or akaline battery setup. It could be
	juiced up to 5V (the NeoPixel can handle it, and the ATTiny would run at 16Mhz),
	but we really don't need to speed, and it would require either a boost convertor
	or a bigger battery.
*/
#include <tinyNeoPixel.h>

// we'll use the internal 1.1 analog reference, since that will give us better resolution
// in the range that we care about
#define AREF_VOLTAGE	1.1
#define SELECTED_AREF	INTERNAL
#define TIMEOUT			1000

#define PIXEL_PIN	4

// using GRBW, since the we have a RGBW NeoPixel
tinyNeoPixel pixel = tinyNeoPixel(1, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);

// use ADC 3
int sensor_pin = A3;
int reading;

void setup() {
	// use the internal 1.1V analog reference
	analogReference(SELECTED_AREF);
	
	pixel.begin();
	pixel.show();
}

void loop() {
	reading = analogRead(sensor_pin);
	float voltage = (reading * AREF_VOLTAGE)/1024.0;
	float tempC = (voltage - 0.5) * 100;
	float tempF = (tempC * 9.0 / 5.0) + 32.0;	
	
	setPixel(tempC);
	
	delay(TIMEOUT);
}

void setPixel(float temp) {
	pixel.setPixelColor(0, tempToColor(temp));
	pixel.show();
}

// convert a temp to a color
uint32_t tempToColor(float temp) {
	int r, b;
	r = map(temp, -10.0, 50.0, 0, 255);
	b = map(temp, -10.0, 50.0, 255, 0);
	
	return gamma32(pixel.Color(r, 0, b, 0)); 
}

// implementing gamma32 here, since it's not currently in ATTinyCore
uint32_t gamma32(uint32_t x) {
	uint8_t *y = (uint8_t *)&x;
	for (uint8_t i=0; i<4; i++) y[i] = pixel.gamma8(y[i]);
	return x;
}
