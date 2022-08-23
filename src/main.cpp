
#include <M5Atom.h>

#include "FreqCountESP\src\FreqCountESP.h" // https://github.com/kapraran/FreqCountESP (MIT)
uint8_t inputPin = GPIO_NUM_33;            // 33;
uint16_t timerMs = 1000;

bool blink = false;

void ElapsedRuntime(uint16_t &dd, byte &hh, byte &mm, byte &ss, uint16_t &ms)
// returns the elapsed time since startup of the ESP
{
  unsigned long now = millis();
  int nowSeconds = now / 1000;

  dd = nowSeconds / 60 / 60 / 24;
  hh = (nowSeconds / 60 / 60) % 24;
  mm = (nowSeconds / 60) % 60;
  ss = nowSeconds % 60;
  ms = now % 1000;
}

void setup()
{

  M5.begin(true, false, true);
  M5.dis.fillpix(0x00004f);

  Serial.println(" FreqCounterESP lib"); // Console print
  FreqCountESP.begin(inputPin, timerMs);
}

void loop()
{
  uint16_t dd = 0;
  byte hh = 0;
  byte ss = 0;
  byte mm = 0;
  uint16_t ms = 0;

  // Frequency counter with GPIO33
  static unsigned long Ftimer = 0;
  if (FreqCountESP.available())
  {
    unsigned long t = millis();
    uint32_t frequency = FreqCountESP.read();
    ElapsedRuntime(dd, hh, mm, ss, ms);
    Serial.printf("%05d|%02i:%02i:%02i:%03i|  F-Time %lu ms  -  Frequency %i Hz\n",
                  dd,
                  hh,
                  mm,
                  ss,
                  ms,
                  t - Ftimer,
                  frequency);
    Ftimer = t;
  }

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
