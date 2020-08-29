#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 2 rows

const int leds[4] = {12, 11, 10, 9}; // All pins for our LED lights in the correct order

int bytes[4] = {};

// Turns off all of the LEDS we have in our leds array
void turnOffLeds() {
  for (int led : leds) {
    digitalWrite(led, LOW);
  }
}

// Reverses an array
void reverse(int arr[], int size) {
  int temp;
  for (int i = 0; i < size / 2; ++i) {
    temp = arr[i];
    arr[i] = arr[size - i - 1];
    arr[size - i - 1] = temp;
  }
}

// Converts a decimal number to binary.  Maybe a simpler solution would have been just a binary adder?
void toBinary(int num) {
  memset(bytes, 0, sizeof(bytes));
  int i = 0;
  while (num > 0) {
    bytes[i] = num % 2;
    num /= 2;
    i++;
  }
  reverse(bytes, 4);
}

int currentNum = 0;

void setup() {

  // Set all leds to OUTPUT and turn them off.
  for (int led : leds) {
    pinMode(led, OUTPUT);
  }
  turnOffLeds();

  lcd.init();
  lcd.backlight();
}

void loop() {

  char bytesStr[4];

  // Add one to the number
  currentNum++;
  // Convert the next number into binary and wait 750ms
  toBinary(currentNum);

  if (currentNum == 16) {
    currentNum = 0;
  }

  // Checks the bytes array and turns the leds on and off dependent on the state
  for (int i = 0; i < 4; ++i) {
    if (bytes[i] == 1) {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }

  sprintf(bytesStr, "%d%d%d%d", bytes[0], bytes[1], bytes[2], bytes[3]);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(currentNum);
  lcd.setCursor(0, 1);
  lcd.print(bytesStr);

  delay(750);
}