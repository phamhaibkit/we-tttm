/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>

IRsend irsend;

void setup()
{
  
}

void loop() {
	for (int i = 0; i < 3; i++) {
		irsend.sendNEC(0x20250AF, 32);
		delay(40);
	}
	delay(30000); //5 second delay between each signal burst
}
