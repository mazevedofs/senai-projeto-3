#include <Keypad.h>

bool typing = false;//salvar estado da senha
String senhaDigitada;
String senha = "4321";


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {5, 4, 3, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {

    if (typing && key != '#') {
      senhaDigitada += key;
      Serial.println(senhaDigitada);
    }

    if (key == '*') {
      senhaDigitada = "";
      typing = true;
      Serial.println("Digitando senha...");
    }
    if (key == '#') {
      typing = false;
      Serial.println("Finalizado");
      if (senhaDigitada == senha) {
        Serial.println("Alarme desativado");
      }
      else {
        Serial.println("Acesso negado");
      }
    }
    //Serial.println(key);
  }
}
