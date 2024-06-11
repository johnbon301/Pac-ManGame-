#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>


AsyncDelay delay_1s;
AsyncDelay delay_2s;
AsyncDelay delay_3s;
AsyncDelay delay_5s;
volatile bool leftButton;
volatile bool rightButton;
volatile bool switchFlag;
int leftButtonPin = 4;
int rightButtonPin = 5;
int switchState = false;
int switchPin = 7;
volatile int positionPin = 0;
volatile int pinPosition = 6;
volatile int timer = 0;
volatile int points = 0;
volatile int levelMode = 0;
int levelComp[8] = { 0x7A1AE5, 0x5DD1FB, 0x18E7B2, 0xF3A70C, 0xFA3905, 0xF40B8D, 0xB705FA, 0x00FF6D };
int levelDone[6][2] = {
  // level finished
  { 587, 75 },  // song[0][0]], song[0][1]]
  { 659, 75 },  // song[1][0]], song[1][1]]
  { 783, 75 },  // song[2][0]], song[2][1]]
  { 880, 75 },  // song[3][0]], song[3][1]]
  { 987, 75 },  // song[4][0]], song[4][1]]
};

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  delay_1s.start(1000, AsyncDelay::MILLIS);
  delay_2s.start(2000, AsyncDelay::MILLIS);
  delay_3s.start(3000, AsyncDelay::MILLIS);
  delay_5s.start(5000, AsyncDelay::MILLIS);
  attachInterrupt(leftButtonPin, leftButtonISR, RISING);
  attachInterrupt(rightButtonPin, rightButtonISR, RISING);
  attachInterrupt(switchPin, switchISR, CHANGE);
}

void loop() {

  if (switchFlag) {
    delay(50);
    switchState = !switchState;
    CircuitPlayground.clearPixels();
    Serial.println("Game off!!");
    switchFlag = false;
  }
  if (switchState) {
    CircuitPlayground.setPixelColor(positionPin, 0xefff00);
    if (leftButton) {
      delay(200);
      CircuitPlayground.setPixelColor(positionPin, 0x000000);
      positionPin--;
      if (positionPin < 0) {
        positionPin = 9;
      }
      CircuitPlayground.setPixelColor(positionPin, 0xefff00);
      leftButton = false;
    }

    if (rightButton) {
      delay(200);
      CircuitPlayground.setPixelColor(positionPin, 0x000000);
      positionPin++;
      if (positionPin > 9) {
        positionPin = 0;
      }
      CircuitPlayground.setPixelColor(positionPin, 0xefff00);
      rightButton = false;
    }


    level();

    wingame();

    endgame();
  }
}


void ghostpink() {             // seprate from loop because it's going to run continuously on it's own,,,, will move ghost
  if (delay_1s.isExpired()) {  //the movement of the ghost
    Serial.println("  ");
    Serial.print("Timer:   ");
    Serial.println(timer);
    timer++;
    Serial.print("Points:   ");
    Serial.println(points);
    Serial.print("Level:   ");
    Serial.println(levelMode);
    delay_1s.repeat();
  } else if (timer == 10) {
    delay_1s.expire();
    CircuitPlayground.clearPixels();
    points++;
    Serial.print("Points:   ");
    Serial.println(points);
    timer = 0;
    Serial.print("Level:   ");
    Serial.println(levelMode);
    for (int i = 0; i < sizeof(levelDone) / sizeof(levelDone[0]); i++) {  // completeing noise
      CircuitPlayground.playTone(levelDone[i][0], levelDone[i][1]);
      delay(1);
      for (int l : levelComp) {
        int randomLed = random(10);  // use for completeing level; fireworks go here
        CircuitPlayground.setPixelColor(randomLed, l);
        delay(10);
        CircuitPlayground.setPixelColor(randomLed, 0x000000);
        delay(10);
      }
    }
  }
  if (delay_5s.isExpired()) {
    CircuitPlayground.setPixelColor(pinPosition, 0x000000);
    pinPosition = random(10);
    CircuitPlayground.setPixelColor(pinPosition, 0xff00ef);
    delay_5s.repeat();
  }
}

void ghostblue() {             // seprate from loop because it's going to run continuously on it's own,,,, will move ghost #0000ff
  if (delay_1s.isExpired()) {  //the movement of the ghost
    Serial.println("  ");
    Serial.print("Timer:   ");
    Serial.println(timer);
    timer++;
    Serial.print("Points:   ");
    Serial.println(points);
    Serial.print("Level:   ");
    Serial.println(levelMode);
    delay_1s.repeat();
  } else if (timer == 10) {
    delay_1s.expire();
    CircuitPlayground.clearPixels();
    points++;
    Serial.print("Points:   ");
    Serial.println(points);
    timer = 0;
    Serial.print("Level:   ");
    Serial.println(levelMode);
    for (int i = 0; i < sizeof(levelDone) / sizeof(levelDone[0]); i++) {  // completeing noise
      CircuitPlayground.playTone(levelDone[i][0], levelDone[i][1]);
      delay(1);
      for (int l : levelComp) {
        int randomLed = random(10);  // use for completeing level; fireworks go here
        CircuitPlayground.setPixelColor(randomLed, l);
        delay(10);
        CircuitPlayground.setPixelColor(randomLed, 0x000000);
        delay(10);
      }
    }
  }
  if (delay_3s.isExpired()) {
    CircuitPlayground.setPixelColor(pinPosition, 0x000000);
    pinPosition = random(10);
    CircuitPlayground.setPixelColor(pinPosition, 0x0000ff);
    delay_3s.repeat();
  }
}

void ghostred() {              // seprate from loop because it's going to run continuously on it's own,,,, will move ghost   #ff0000
  if (delay_1s.isExpired()) {  //the movement of the ghost
    Serial.println("  ");
    Serial.print("Timer:   ");
    Serial.println(timer);
    timer++;
    Serial.print("Points:   ");
    Serial.println(points);
    Serial.print("Level:   ");
    Serial.println(levelMode);
    delay_1s.repeat();
  } else if (timer == 10) {
    delay_1s.expire();
    CircuitPlayground.clearPixels();
    points++;
    Serial.print("Points:   ");
    Serial.println(points);
    timer = 0;
    Serial.print("Level:   ");
    Serial.println(levelMode);
    for (int i = 0; i < sizeof(levelDone) / sizeof(levelDone[0]); i++) {  // completeing noise
      CircuitPlayground.playTone(levelDone[i][0], levelDone[i][1]);
      delay(1);
      for (int l : levelComp) {
        int randomLed = random(10);  // use for completeing level; fireworks go here
        CircuitPlayground.setPixelColor(randomLed, l);
        delay(10);
        CircuitPlayground.setPixelColor(randomLed, 0x000000);
        delay(10);
      }
    }
  }
  if (delay_2s.isExpired()) {
    CircuitPlayground.setPixelColor(pinPosition, 0x000000);
    pinPosition = random(10);
    CircuitPlayground.setPixelColor(pinPosition, 0xff0000);
    delay_2s.repeat();
  }
}

void level() {  // change if level progression works but ghosts work
  switch (levelMode) {
    case 0:
      ghostpink();
      break;
    case 1:
      ghostblue();
      break;
    case 2:
      ghostred();
      break;
    default:
      break;
  }
}



void wingame() {  // wingame have to check if it is working
  if (timer == 10) {
    levelMode++;
  }
  if (levelMode > 3) {
    levelMode = 0;
    timer = 0;
    points = 0;
    Serial.println("YAY YOU WON!!!");
  }
}

void endgame() {                     // determine cirtia of when the game will end
  if (pinPosition == positionPin) {  // end is finshed
    CircuitPlayground.clearPixels();
    CircuitPlayground.playTone(1500, 10);  // losing completion noise
    for (int i = 0; i < 10; i++) {         // red lights for dying??
      CircuitPlayground.setPixelColor(i, 0xff0000);
      delay(1);
    }
    for (int a = 0; a < 10; a++) {
      CircuitPlayground.setPixelColor(a, 0x000000);
      delay(1);
    }
    Serial.println("  ");
    timer = 0;  // timer resets
    Serial.print("Timer:   ");
    Serial.println(timer);
    points = 0;  // points resets
    Serial.print("Points:  ");
    Serial.println(points);
    levelMode = 0;
    Serial.print("Level:   ");
    Serial.println(levelMode);  // level resets
    Serial.println("YOU LOST HAHHAHHAHA!!");
  }
}



void leftButtonISR() {
  leftButton = true;
}

void rightButtonISR() {
  rightButton = true;
}

void switchISR() {
  switchFlag = true;
}
