#include <Arduino.h>
#include <FastLED.h>
#include <MicroOscSlip.h>
MicroOscSlip<128> monOsc(&Serial);

// CRGB keyPixel;
CRGB atomPixel;

#define KEY_CHANNEL_BTN 2
// gestion du hub
#include <M5_PbHub.h>
M5_PbHub myPbHub;

unsigned long monChronoDepart; // À DÉPLACER au début du code avec les autres variables globales

// FONCTION QUI SERA APPELÉE LORSQU'UN N'IMPORTTE QUEL MESSAGE OSC EST REÇU
// receivedOscMessage est le message reçu
void myOscMessageParser(MicroOscMessage &receivedOscMessage)
{
  // Ici, un if et receivedOscMessage.checkOscAddress() est utilisé pour traiter les différents messages
  if (receivedOscMessage.checkOscAddress("/pixel"))
  {                                                          // MODIFIER /pixel pour l'adresse qui sera reçue
    int premierArgument = receivedOscMessage.nextAsInt();    // Récupérer le premier argument du message en tant que int
    int deuxiemerArgument = receivedOscMessage.nextAsInt();  // SI NÉCESSAIRE, récupérer un autre int
    int troisiemerArgument = receivedOscMessage.nextAsInt(); // SI NÉCESSAIRE, récupérer un autre int

    // UTILISER ici les arguments récupérés
    myPbHub.setPixelColor(KEY_CHANNEL_BTN, 0, premierArgument,deuxiemerArgument, troisiemerArgument);


    // SI NÉCESSAIRE, ajouter d'autres if pour recevoir des messages avec d'autres adresses
  }
  else if (receivedOscMessage.checkOscAddress("/autre"))
  { // MODIFIER /autre une autre adresse qui sera reçue
    // ...
  }
}

void setup()
{
  // NE JAMAIS OUBLIER !!!
  Serial.begin(115200);
  Wire.begin();
  myPbHub.begin();
  monChronoDepart = millis();

  FastLED.addLeds<WS2812, 27, GRB>(&atomPixel, 1);
  atomPixel = CRGB(255, 0, 0); // ROUGE
  FastLED.show();
  delay(1000);                   // PAUSE 1 SECONDE
  atomPixel = CRGB(255, 255, 0); // JAUNE
  FastLED.show();
  delay(1000);                 // PAUSE 1 SECONDE
  atomPixel = CRGB(0, 255, 0); // VERT
  FastLED.show();
  delay(1000); // PAUSE 1 SECONDE
  atomPixel = CRGB(0, 0, 0);
  FastLED.show(); // PAUSE 1 SECONDE
}

void loop()
{
  monOsc.onOscMessageReceived(myOscMessageParser);

  if (millis() - monChronoDepart >= 20)
  {
    monChronoDepart = millis();
    // oscslip btn
  int press = myPbHub.digitalRead(KEY_CHANNEL_BTN);
  monOsc.sendInt("/BUTTON", press);
  }
}