
#include <M5Atom.h>

#include "FreqCountESP\src\FreqCountESP.h"  // https://github.com/kapraran/FreqCountESP (MIT)
uint8_t inputPin = 33;
uint16_t timerMs = 1000;

bool blink = false;


void setup()
{

  M5.begin(true, false, true);
  M5.dis.fillpix(0x00004f);

  Serial.println(" FreqCounterESP lib"); // Console print
  FreqCountESP.begin(inputPin, timerMs);

}

void loop()
{

  // Frequency counter with GPIO33
  static unsigned long Ftimer = 0;
  if (FreqCountESP.available())
  {
    unsigned long t = millis();
    uint32_t frequency = FreqCountESP.read();
    Serial.printf("\nTime %lu ms  -  Frequency %i Hz\n", t - Ftimer, frequency);
    Ftimer = t;
  }

  // transfer GPS data via BlueTooth
  static bool blink = false;
  static unsigned long oneSecondPM = 0;
  unsigned long oneSecondCM = millis();
  if (oneSecondCM - oneSecondPM >= (1000 * 1))
  {
    if ((blink = !blink))
    {
      M5.dis.drawpix(0, 0, 0x0000cc); // blue
    }
    else
    {
      M5.dis.drawpix(0, 0, 0x00ff00); // green
    }

    // -------- oneSecond end ----------------------------------------------------------------
    oneSecondPM = oneSecondCM;
  }
}
