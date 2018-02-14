#include <Arduino.h>
#include "NESDriver.h"

#define DATA0_PIN 8
#define DATA1_PIN 9
#define LATCH_PIN 7
#define CLOCK_PIN 4
#define BTN_L1 10
#define BTN_R1 16
#define BTN_L2 14
#define BTN_R2 15
#define LED_1 5
#define LED_2 6

#define SLEEP delay(16)

NESController c

void setup() {
    NESDriver.begin(LATCH_PIN, CLOCK_PIN, DATA0_PIN, DATA1_PIN);
    Serial.begin(9600);
}

void loop() {
    NESDriver.updateState();
    c = NESDriver.state1();
    if (c.isChanged()) {
      Serial.write(c.state());
    }
    SLEEP;
}
