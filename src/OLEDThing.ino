#include <Thing.h>
#include <BlinkPattern.h>
#include "devices/SSD1306I2C64x48.h"

using namespace ootb;
using namespace g3rb3n;

Thing thing;
BlinkPattern led(BUILTIN_LED);
SSD1306I2C64x48 oled(0x3C);

BlinkPattern::Pattern<2> initialize{{1,1},50};
BlinkPattern::Pattern<2> on{{39,1},25};

void setup()
{
    Serial.begin(230400);
    Serial.println();
    Serial.println("ClientID:" + thing.clientId());

    oled.begin();

    led.setPattern(initialize);

    showText(thing.clientId());

    thing.onStateChange([](const String& msg)
    {
        showText(msg);
        Serial.println(msg);
    });

    thing.begin();
    String topic = "things/" + thing.clientId() + "/oled/text";
    thing.addActuator(topic, [](Value& value)
    {
        showText((String)value);
        Serial.println((String)value);
    });

    led.setPattern(on);
}

void loop()
{
    thing.handle();
}

void showText(const String& value)
{
    oled.clear();
    oled.setCursor(0,0);
    oled.print(value);
    oled.display();
}
