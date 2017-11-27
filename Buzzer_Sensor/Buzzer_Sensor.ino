#include <RestClient.h>
#include <Ultrasonic.h>
#include <Keypad.h>
#include <UIPEthernet.h>

bool typing = false;//salvar estado da senha
String senhaDigitada;
String senha = "4321";
int buzzer = 3;
long ultimoEstadoPorta;
bool alarmeAtivado;

Ultrasonic ultrasonic(7, 8);

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

// Alterar o último valor para o id do seu kit
const byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFF };
EthernetClient ethclient;

RestClient client = RestClient("192.168.3.186", 3000, ethclient);
const char* sid = "AC9848c713c4f8d834a1a99b5ade904f60";
const char* token = "c4cede7f15c35be0622896d597833aba";
const char* to = "5511984820042";
const char* from = "15744061737";

String response = "";


void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(buzzer, OUTPUT);

  if(Ethernet.begin(mac)) {
    Serial.println("Conectado via DHCP");
    Serial.print("IP recebido:"); Serial.println(Ethernet.localIP());
  }

  String parametros = "sid=";
  parametros += String(sid);

  parametros += String("&token=");
  parametros += String(token);

  parametros += String("&to=");
  parametros += String(to);

  parametros += String("&from=");
  parametros += String(from);

  parametros += "&body=Mensagem Legal";

  Serial.println(parametros);

  int statusCode = client.post("/sms", parametros.c_str(), &response);
  Serial.print("Status da resposta: ");
  Serial.println(statusCode);
  Serial.print("Resposta do servidor: ");
  Serial.println(response);
  delay(1000);
}


void loop() {
  int distanciaPorta = 0;
  if (Serial.available() > 0) {
    distanciaPorta = Serial.parseInt();
  }

  char key = keypad.getKey();
  long now = millis();

  if ((now % 5000 == 0) && alarmeAtivado) {
    //Serial.println("5 Segundos");
    tone(buzzer, 3000);
  }

  if (key && alarmeAtivado) {

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
        alarmeAtivado = false;
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

  if (distanciaPorta < 10 && distanciaPorta > 0) {
    Serial.println(distanciaPorta);
    delay(1000);
    alarmeAtivado = true;
  } else if (distanciaPorta > 10) {
    delay(1000);
    Serial.println(distanciaPorta);
  }
}
