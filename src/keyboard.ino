#include "Keyboard.h"

#define KEY_Z (2)
#define KEY_X (3)
#define KEY_R (10)

#define LED_Z (4)
#define LED_X (5)

enum {PRESSED, RELEASED} z_status = RELEASED, x_status = RELEASED, r_status = RELEASED;

void setup() {
	Serial.begin(115200);
	Serial.print("setup start\n");
	pinMode(LED_Z, OUTPUT);
	pinMode(LED_X, OUTPUT);
	analogWrite(LED_Z, 255);
	analogWrite(LED_X, 255);
	pinMode(KEY_Z, INPUT_PULLUP);
	pinMode(KEY_X, INPUT_PULLUP);
	pinMode(KEY_R, INPUT_PULLUP);
	Serial.print("setup end\n");
}

void enableKeyboard(void) {
	Serial.print("keyboard ready\n");
	attachInterrupt(digitalPinToInterrupt(KEY_Z), z_press, FALLING);
	attachInterrupt(digitalPinToInterrupt(KEY_X), x_press, FALLING);
	Keyboard.begin();
	interrupts();
}

void loop() {
	enableKeyboard();
	while (1) {
		if (z_status == PRESSED) {
			if (digitalRead(KEY_Z)) {
				Keyboard.release('z');
				z_status = RELEASED;
			}
		}
		if (x_status == PRESSED) {
			if (digitalRead(KEY_X)) {
				Keyboard.release('x');
				x_status = RELEASED;
			}
		}
		if (r_status == RELEASED) {
			if (!digitalRead(KEY_R)) {
				Keyboard.press('`');
				r_status = PRESSED;
			}
		} else {
            if (digitalRead(KEY_R)) {
				Keyboard.release('`');
				r_status = RELEASED;
            }
        }
		delay(1);
	}
}

void z_press(void) {
	Keyboard.press('z');
	z_status = PRESSED;
}

void x_press(void) {
	Keyboard.press('x');
	x_status = PRESSED;
}

void r_press(void) {
	Keyboard.press('`');
	r_status = PRESSED;
}
