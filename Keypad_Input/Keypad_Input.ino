#include <Ultrasonic.h>
#include <Keypad.h>
//baixar do GIT restclient.h

bool typing = false;//salvar estado da senha
String senhaDigitada;
String senha = "4321";
int buzzer = 10;
long ultimoEstadoPorta;
bool portaAberta;


Ultrasonic ultrasonic(12, 13);



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


}

void loop() {
  int distanciaPorta = ultrasonic.distanceRead();
  char key = keypad.getKey();
  //  Serial.print("Millis" );
  //  Serial.println(millis() % 15000 == 0 );
  //  Serial.print("Porta" );
  //  Serial.println(portaAberta);
  //Serial.print("Dist Porta" );
  //Serial.println(distanciaPorta);
  long now = millis();

  //  if (now % 5000 == 0) {
  //    Serial.println("5 Segundos");
  //tone(buzzer, 3000);

  if (now % 5000 == 0 ) {
    tone(buzzer, 5000);
    Serial.println("Buzzer tocou");
  }

  if (distanciaPorta < 10 && distanciaPorta > 0) {
    Serial.println(distanciaPorta);
    delay(1000);
    portaAberta = true;


    if (key) {

      if (typing && key != '#') {
        Serial.println("Taís");
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
  } else if (distanciaPorta > 10) {
    delay(1000);
    Serial.println(distanciaPorta);
  }
}



