#include <Thing.h>
#include <SFE_MicroOLED.h>
#include <BlinkPattern.h>
#include "Wire.h"
#include "SPI.h"

using namespace ootb;

#define PIR_PIN D3

Thing thing;
MicroOLED oled(255, 0);
BlinkPattern led(BUILTIN_LED);

BlinkPattern::Pattern<2> initialize{{1,1},50};
BlinkPattern::Pattern<2> on{{39,1},25};

void setup()
{
    Serial.begin(230400);
    Serial.println();
    Serial.println("ClientID:" + thing.clientId());

    oled.begin();
    oled.setFontType(0);
  
    led.setPattern(initialize);

    display(thing.clientId());
    pinMode(BUILTIN_LED, OUTPUT);

    thing.onStateChange([](const String& msg){
        display(msg);
        Serial.println(msg);
    });

    thing.begin();

    thing.addActuator("oled/text/" + thing.clientId(), [](Value& value){
        display((String)value);
        Serial.println((String)value);
    });

    led.setPattern(on);
}

void loop()
{
    thing.handle();
}

void display(const String& value){
  oled.clear(PAGE);
  oled.setCursor(0,0);
  oled.print(value);
  oled.display(); 
}
