#include <SPI.h>
#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>
#include <RestClient.h>

int msg;

// Alterar o último valor para o id do seu kit
const byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xF1, 0x77 };

void callback(char *topic, byte *payload, unsigned int length);

EthernetClient ethclient;

PubSubClient client("m10.cloudmqtt.com", 11356, callback, ethClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  char c = payload;
  Serial.println(c);
  Serial.println(topic);

  if (strcmp(topic, "validaSenha") == 0) {
    msg = atoi(c);
    if (msg == 1) {
      Serial.println("Validou senha");
    }
  }

}
boolean reconnect() // Recebe função que reconecta ao servidor MQTT
{
  Serial.println("reconectando...");
  if (client.connect("arduinoClient", "usuario", "senha")) {
    client.subscribe("vaga/22");
  }
  return client.connected();
}

RestClient client = RestClient("192.168.3.186", 3000, ethclient);
const char* sid = "AC9848c713c4f8d834a1a99b5ade904f60";
const char* token = "c4cede7f15c35be0622896d597833aba";
const char* to = "5511984820042";
const char* from = "15744061737";

String response = "";

//Setup
void setup() {
  Serial.begin(9600);
  // Connect via DHCP
  if (Ethernet.begin(mac)) {
    Serial.println("Conectado via DHCP");
    Serial.print("IP recebido:"); Serial.println(Ethernet.localIP());
  }

  String parametros = "sid=";
  parametros.concat(sid);

  parametros.concat("&token=");
  parametros.concat(token);

  parametros.concat("&to=");
  parametros.concat(to);

  parametros.concat("&from=");
  parametros.concat("15744061737");

  parametros.concat("&body=TESTE");

  Serial.println(parametros);

  int statusCode = client.post("/sms", parametros.c_str(), &response);
  Serial.print("Status da resposta: ");
  Serial.println(statusCode);
  Serial.print("Resposta do servidor: ");
  Serial.println(response);
  delay(1000);
}

void loop() {

}
