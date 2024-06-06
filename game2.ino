#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>


AsyncDelay delay_1s;
AsyncDelay delay_5s;
float midi[127];
int A_four = 440;
bool leftButton;
bool rightButton;
int leftButtonPin = 4;
int rightButtonPin = 5;
volatile bool switchFlag;
int switchState = false;
int switchPin = 7;
volatile int positionPin = 0;
volatile int pinPosition = 0;
volatile int timer = 0;
volatile int points = 0;
volatile int levelMode = 0;
int levelComp[8] = { 0x7A1AE5, 0x5DD1FB, 0x18E7B2, 0xF3A70C, 0xFA3905, 0xF40B8D, 0xB705FA, 0x00FF6D };
int levelDone[23][2] = {
  // level finished
  { 74, 75 },   // song[0][0]], song[0][1]]
  { 76, 75 },   // song[1][0]], song[1][1]]
  { 77, 75 },   // song[2][0]], song[2][1]]
  { 79, 75 },   // song[3][0]], song[3][1]]
  { 81, 75 },   // song[4][0]], song[4][1]]
  { 83, 200 },  // song[5][0]], song[5][1]]
  { 81, 200 },  // song[6][0]], song[6][1]]
  { 74, 75 },   // song[7][0]], song[7][1]]
  { 76, 75 },   // song[8][0]], song[8][1]]
  { 77, 75 },   // song[9][0]], song[9][1]]
  { 79, 75 },   // song[10][0]], song[10][1]]
  { 81, 75 },   // song[11][0]], song[11][1]]
  { 83, 200 },  // song[12][0]], song[12][1]]
  { 81, 200 },  // song[13][0]], song[13][1]]
  { 76, 75 },   // song[14][0]], song[14][1]]
  { 77, 75 },   // song[15][0]], song[15][1]]
  { 79, 75 },   // song[16][0]], song[16][1]]
  { 81, 75 },   // song[17][0]], song[17][1]]
  { 83, 75 },   // song[18][0]], song[18][1]]
  { 86, 200 },  // song[19][0]], song[19][1]]
  { 86, 75 },   // song[20][0]], song[20][1]]
  { 86, 75 },   // song[21][0]], song[21][1]]
  { 86, 75 },   // song[22][0]], song[22][1]]
};

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  delay_1s.start(1000, AsyncDelay::MILLIS);
  delay_5s.start(5000, AsyncDelay::MILLIS);
  attachInterrupt(leftButtonPin, leftButtonISR, RISING);
  attachInterrupt(rightButtonPin, rightButtonISR, RISING);
  attachInterrupt(switchPin, switchISR, CHANGE);
}

void loop() {

  if (switchFlag) {
    delay(50);
    switchState = !switchState;
    switchFlag = false;
  }
  if (switchState) {
    CircuitPlayground.clearPixels();
    timer = 0;
    Serial.print("Timer:   ");
    Serial.println(timer);
    points = 0;
    Serial.print("Points:   ");
    Serial.println(points);
    levelMode = 0;
    Serial.print("Level:   ");
    Serial.println(levelMode);
  }

  if (leftButton) {
    delay(100);
    positionPin--;
    CircuitPlayground.setPixelColor(positionPin, 0xff00ef);
    CircuitPlayground.clearPixels();
    leftButton = false;
    if (positionPin < 0) {
      positionPin = 9;
    }
    leftButton = false;
  }
  if (rightButton) {
    delay(100);
    positionPin++;
    CircuitPlayground.setPixelColor(positionPin, 0xff00ef);
    CircuitPlayground.clearPixels();
    if (positionPin > 9) {
      positionPin = 0;
    }
    rightButton = false;
  }


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

  //endgame();

  //wingame();
}


void ghostpink() {             // seprate from loop because it's going to run continuously on it's own,,,, will move ghost
  if (delay_1s.isExpired()) {  //the movement of the ghost
    Serial.print("Timer:   ");
    Serial.println(timer);
    timer++;
    Serial.print("Points:   ");
    Serial.println(points);
    Serial.print("Level:   ");
    Serial.println(levelMode);
  } else if (timer == 60) {
    delay_1s.expire();
    points++;
    Serial.print("Points:   ");
    Serial.println(points);
    timer = 0;
    Serial.print("Level:   ");
    Serial.println(levelMode);
    while (delay_1s.isExpired()) {
      int randomColor = random(sizeof(levelComp) / sizeof(int));  // use for completeing level; fireworks go here
      int randomLed = random(10);
      CircuitPlayground.setPixelColor(randomLed, levelComp[randomColor]);
      delay(200);
      CircuitPlayground.setPixelColor(randomLed, 0x000000);
      delay(200);
      for (int i = 0; i < sizeof(levelDone) / sizeof(levelDone[0]); i++) {  // completeing noise
        CircuitPlayground.playTone(midi[levelDone[i][0]], levelDone[i][1]);
        Serial.println(midi[levelDone[i][0]]);
        delay(1);
      }
    }
  }
  if (delay_5s.isExpired()) {
    pinPosition = random(10);
    CircuitPlayground.setPixelColor(pinPosition, 0xff00ef);
    //delay(2000);
    CircuitPlayground.clearPixels();
    //delay_5s.repeat;
  } else if (timer == 60) {
    delay_5s.expire();
    CircuitPlayground.clearPixels();
  }
  //delay_1s.repeat;
}

void ghostblue() {             // seprate from loop because it's going to run continuously on it's own,,,, will move ghost #0000ff
  if (delay_1s.isExpired()) {  //the movement of the ghost
    Serial.print("Timer:   ");
    Serial.println(timer);
    timer++;
    Serial.print("Points:   ");
    Serial.println(points);
    Serial.print("Level:   ");
    Serial.println(levelMode);
  } else if (timer == 60) {
    delay_1s.expire();
    points++;
    Serial.print("Points:   ");
    Serial.println(points);
    Serial.print("Level:   ");
    Serial.println(levelMode);
    timer = 0;
    while (delay_1s.isExpired()) {
      int randomColor = random(sizeof(levelComp) / sizeof(int));  // use for completeing level; fireworks go here
      int randomLed = random(10);
      CircuitPlayground.setPixelColor(randomLed, levelComp[randomColor]);
      delay(200);
      CircuitPlayground.setPixelColor(randomLed, 0x000000);
      delay(200);
      for (int i = 0; i < sizeof(levelDone) / sizeof(levelDone[0]); i++) {  // completeing noise
        CircuitPlayground.playTone(midi[levelDone[i][0]], levelDone[i][1]);
        Serial.println(midi[levelDone[i][0]]);
        delay(1);
      }
    }
  }
  if (delay_5s.isExpired()) {
    pinPosition = random(10);
    CircuitPlayground.setPixelColor(pinPosition, 0x0000ff);
    //delay(2000);
    CircuitPlayground.clearPixels();
    //delay_5s.repeat;
  } else if (timer == 60) {
    delay_5s.expire();
    CircuitPlayground.clearPixels();
  }
  //delay_1s.repeat;
}

void ghostred() {              // seprate from loop because it's going to run continuously on it's own,,,, will move ghost   #ff0000
  if (delay_1s.isExpired()) {  //the movement of the ghost
    Serial.print("Timer:   ");
    Serial.println(timer);
    timer++;
    Serial.print("Points:   ");
    Serial.println(points);
    Serial.print("Level:   ");
    Serial.println(levelMode);
  } else if (timer == 60) {
    delay_1s.expire();
    points++;
    Serial.print("Points:   ");
    Serial.println(points); 
    Serial.print("Level:   ");
    Serial.println(levelMode);
    timer = 0;
    while (delay_1s.isExpired()) {
      int randomColor = random(sizeof(levelComp) / sizeof(int));  // use for completeing level; fireworks go here
      int randomLed = random(10);
      CircuitPlayground.setPixelColor(randomLed, levelComp[randomColor]);
      delay(200);
      CircuitPlayground.setPixelColor(randomLed, 0x000000);
      delay(200);
      for (int i = 0; i < sizeof(levelDone) / sizeof(levelDone[0]); i++) {  // completeing noise
        CircuitPlayground.playTone(midi[levelDone[i][0]], levelDone[i][1]);
        Serial.println(midi[levelDone[i][0]]);
        delay(1);
      }
    }
  }
  if (delay_5s.isExpired()) {
    pinPosition = random(10);
    CircuitPlayground.setPixelColor(pinPosition, 0xff0000);
    //delay(2000);
    CircuitPlayground.clearPixels();
    //delay_5s.repeat;
  } else if (timer == 60) {
    delay_5s.expire();
    CircuitPlayground.clearPixels();
  }
  //delay_1s.repeat;
}



void endgame() {  // determien cirtia of when the game will end
  if (pinPosition == positionPin) {
    CircuitPlayground.clearPixels();
    timer = 0;  // timer resets
    Serial.print("Timer:   ");
    Serial.println(timer);
    points = 0;  // points resets
    Serial.print("Points:   ");
    Serial.println(points);
    levelMode = 0;
    Serial.print("Level:   ");
    Serial.println(levelMode);               // level resets
    CircuitPlayground.playTone(1500, 10);  // losing completion noise
    for (int i = 0; i < 10; i++) {         // red lights for dying??
      CircuitPlayground.setPixelColor(i, 0xff000);
      delay(1);
    }
    for (int a = 0; a < 10; a++) {
      CircuitPlayground.setPixelColor(a, 0x000000);
      delay(1);
    }
  }
}

void wingame() {
  if (timer == 60) {
    levelMode++;
  }
  if (levelMode > 2) {
    levelMode = 0;
  }
  Serial.print("Points:   ");
  Serial.println(points);
  Serial.print("Level:   ");
  Serial.println(levelMode);
}

void leftButtonISR() {
  delay(50);
  leftButton = true;
}

void rightButtonISR() {
  delay(50);
  rightButton = true;
}

void switchISR() {
  delay(50);
  switchFlag = true;
}

void generateMIDI() {
  for (int x = 0; x < 127; ++x) {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}
