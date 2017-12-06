#include <Keypad.h>


bool typing = false;//salvar estado da senha
String senhaDigitada;
String senha = "4321";
int buzzer = 9;
long ultimoEstadoPorta;
bool trigger; //ativa o sistema de alarme

int infravermelho = 2;


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
  pinMode(buzzer, OUTPUT);
  pinMode(infravermelho, INPUT);
  
}

void loop() {
  int leituraInfra = digitalRead(infravermelho);
  //Serial.println();
  if (leituraInfra == "1") {
    trigger == true;
    Serial.println("Trigger");
  }

  char key = keypad.getKey();
  long now = millis();

  if ((now % 5000 == 0) && trigger == true) {
    tone(buzzer, 3000);
    Serial.println("Toca buzzer");
  }

  if (key && trigger) {

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
      Serial.println("Finalizado" );
      if (senhaDigitada == senha && leituraInfra == "1") {
        trigger = false;
        noTone (buzzer);
        Serial.println("Alarme desativado, Porta aberta");
      }
      if (senhaDigitada == senha && leituraInfra == "0") {
        trigger = false;
        noTone (buzzer);
        Serial.println("Alarme desativado");
      }
      else {
        Serial.println("Acesso negado");
        tone (buzzer, 2000);
      }
    }
    Serial.println(key);
  }

}
