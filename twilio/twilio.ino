#include <UIPEthernet.h>
#include <RestClient.h>

// Alterar o último valor para o id do seu kit
const byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xF1, 0x77 };
EthernetClient ethclient;

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
  if(Ethernet.begin(mac)) {
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
  parametros.concat(from);

  parametros.concat("&body=Mensagem Legal");

  Serial.println(parametros);

  int statusCode = client.post("/sms", parametros.c_str(), &response);
  Serial.print("Status da resposta: ");
  Serial.println(statusCode);
  Serial.print("Resposta do servidor: ");
  Serial.println(response);
  delay(1000);
}

void loop(){

}
