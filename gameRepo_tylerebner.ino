#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_5s;

volatile bool leftFlag = false;
volatile bool rightFlag = false;

//float pitchValues[3] = {261.63, 440, 523.25};
int colorValues[6] = {255, 0, 100, 50, 150, 200};
int bcolorValues[2] = {255, 0};
int ccolorValues[2] = {255, 0};

void setup(void) {
  CircuitPlayground.begin();
  Serial.begin(9600); //starts serial monitor and tells it how fast to send bits
  delay_5s.start(5000, AsyncDelay::MILLIS);// start counting up by 2000 milliseconds
  //attachInterrupt(4, left, RISING);
  //attachInterrupt(5, right, RISING);
}

void loop() {
/*for(int i = 0; i < sizeof(pitchValues) / sizeof(int); i++) {
    int tonerandomIndex = random(sizeof(pitchValues) / sizeof(int));
    CircuitPlayground.playTone(pitchValues[tonerandomIndex], 500);
}*/

/*for(int i = 0; i < sizeof(acolorValues) / sizeof(int); i++) {
    int acolrandomIndex = random(sizeof(acolorValues) / sizeof(int));
    int bcolrandomIndex = random(sizeof(bcolorValues) / sizeof(int));
    int ccolrandomIndex = random(sizeof(ccolorValues) / sizeof(int));*/
    int randNumber = random(7);
   for(int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, CircuitPlayground.colorWheel(colorValues[randNumber]));
    }
    delay(1000);
    CircuitPlayground.clearPixels();
}

/*void left() {
  leftFlag = true;
}

void right() {
  rightFlag = true;
}*/