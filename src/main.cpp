#include <Arduino.h>
#include <FastLED.h>
#include <MicroOscSlip.h>
MicroOscSlip<128> monOsc(&Serial);

//CRGB keyPixel;
CRGB atomPixel;

#define KEY_CHANNEL_BTN 2
// gestion du hub
#include <M5_PbHub.h>
M5_PbHub myPbHub;

void setup() {
  // NE JAMAIS OUBLIER !!!
  Serial.begin(115200);
  Wire.begin();
  myPbHub.begin();

  FastLED.addLeds<WS2812, 27, GRB>(&atomPixel, 1);
  atomPixel = CRGB(255,0,0); // ROUGE
  FastLED.show();
  delay(1000); // PAUSE 1 SECONDE
  atomPixel = CRGB(255,255,0); // JAUNE
  FastLED.show();
  delay(1000); // PAUSE 1 SECONDE
  atomPixel = CRGB(0,255,0); // VERT
  FastLED.show();
  delay(1000); // PAUSE 1 SECONDE
  atomPixel = CRGB(0,0,0);
  FastLED.show(); // PAUSE 1 SECONDE
}

void loop() { 
  // oscslip btn
  int press = myPbHub.digitalRead(KEY_CHANNEL_BTN);
  monOsc.sendInt("/BUTTON", press);
  delay(100);
}