#include <EEPROM.h>
#include <tone.h> 


int redLed = 2;
int yellowLed = 3;
int greenLed = 4;
int blueLed = 5;
int redButton = 6;
int yellowButton = 7;
int greenButton = 8;
int blueButton = 9;

int leds[] = { redLed, yellowLed, greenLed, blueLed };
int button[] = {redButton, yellowButton, greenButton, blueButton};
int sequence[100];
int roundNumber = 0;

int highScore = 0;

void generateRandomSequence() {
  randomSeed(analogRead(0));
  for (int i = 0; i < 100; i++) {
    sequence[i] = random(4);
  }

}

void flashRoundSeequence() {
  for (int i = 0; i <= roundNumber; i++) {
    int ledIndex = sequence[i];
    int ledPin = leds[ledIndex];
    flashLed(ledPin, 500);
  }

}

int getButtonPress() {

  int buttonPressed = -1;
  while (buttonPressed < 0) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(button[i]) == LOW) {
        digitalWrite(leds[i], HIGH);

        while (digitalRead(button[i]) == LOW) {
          delay(20);
        }
        digitalWrite(leds[i], LOW);

        buttonPressed = i;
      }
    }

  }
  return buttonPressed;
}

void flashLed(int pin, int delayTime) {
  digitalWrite(pin, HIGH);
  delay(delayTime);
  digitalWrite(pin, LOW);
  delay(delayTime);
}



void setup() {
  Serial.begin(9600);
  pinMode(button, OUTPUT);

  highScore = EEPROM.read(0);

  //int val = analogRead(0) / 4;

  //EEPROM.write(highScore, val);

  digitalWrite(leds, HIGH);


  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(button[i], INPUT_PULLUP);
  }

  generateRandomSequence();


  flashLed(blueLed, 40);
  flashLed(greenLed, 40);
  flashLed(yellowLed, 40);
  flashLed(redLed, 40);
  flashLed(blueLed, 40);
  flashLed(greenLed, 40);
  flashLed(yellowLed, 40);
  flashLed(redLed, 40);
  delay(1500);
}
//String highscore = "";

void loop() {

  flashRoundSeequence();

  //mb put this at the end?

  int playerPositionInRound = 0;

  while (playerPositionInRound <= roundNumber) {

    int buttonPressed = getButtonPress();

    if (buttonPressed == sequence[playerPositionInRound]) {
      playerPositionInRound++;
    } else {
      break;
    }
  }


  if (playerPositionInRound > roundNumber) {

    Serial.print("Completado ronda: ");
    Serial.println(roundNumber + 1);
    roundNumber++;
  } else {
    Serial.print("Perdido en ronda: ");
    Serial.println(roundNumber + 1);
    if (roundNumber > highScore) {
      //roundNumber = EEPROM.read(0);
      highScore = roundNumber;
      EEPROM.update(0, roundNumber);
    }


    flashLed(redLed, 30);
    flashLed(redLed, 30);
    flashLed(redLed, 30);
    flashLed(redLed, 30);
    roundNumber = 0;


  }

  //if (roundNumber <= highScore) {

  //highScore = roundNumber;
  //val = highScore;

  //}
  //if (highScore <= EEPROM.read(0)) {

  //} else {
  //highScore = 0;
  //highScore = EEPROM.read(0);
  //EEPROM.update(0, highScore);

  //}

  Serial.print("Current high-score: ");
  Serial.print("\n");
  Serial.print(highScore);
  Serial.println("p");
  delay(500);

}



