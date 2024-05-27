// REDES ELÉTRICAS INTELIGENTES
//
// Código para testar a comunicação usando protocolo MQTT
// Placa: "ESP32 Dev Module"
//
// Depois de compilado e carregado para a plataforma de desenvolvimento ESP32,
// o ESP32 faz eco da mensagem enviada para o tópico "NoIoT-XX:XX:XX:XX:XX:XX.
//
// 2023/2024
#include <WiFi.h>
#include <PubSubClient.h>
//-------------------------------------------------------------------
// Variáveis e constantes
//-------------------------------------------------------------------
// WiFi
const char* ssid     = "SmartGrid";               // SSID da rede (não alterar)
const char* password = "1234567890";              // Password da rede (não alterar)

// config do broker MQTT
const char *broker_mqtt = "mrmaldoror.hopto.org"; // Endereço
char        topico[24];                           // O tópico é dinâmico e é igual ao identificador do nó IoT
const int   porto_mqtt = 1883;                    // porto 1883

String id_do_cliente = "NoIoT-";                  // Prefixo do ID

WiFiClient espClient;                             // Cria objeto WiFi (cliente)
PubSubClient client(espClient);                   // Cria objeto MQTT
//-------------------------------------------------------------------
// SETUP()
//-------------------------------------------------------------------
void setup() {
  Serial.begin(115200);                           // Define interface de comunicação série
  id_do_cliente += String(WiFi.macAddress());     // MAC tem 6 bytes + 5 separadores
  Serial.printf("Olá. Sou o nó %s\n", id_do_cliente.c_str());
  //-----------------------------------------------------------------
  // Estabelece ligação WiFi
  //-----------------------------------------------------------------
  WiFi.begin(ssid, password);
  Serial.print("Ligando à rede...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("concluído.");
  //--------------------------------------------------------------------
  // Define broker MQTT, porto de escuta e rotina de callback
  //--------------------------------------------------------------------
  client.setServer(broker_mqtt, porto_mqtt);
  client.setCallback(callback);
  Serial.print("Ligando ao broker MQTT...");
  while (!client.connected()) {
    if (client.connect(id_do_cliente.c_str())) {
      Serial.println("concluído.");
    } else {
      Serial.print(".");
      delay(2000);
    }
  }
  //--------------------------------------------------------------------
  // Define tópico (igual ao ID do nó), subscreve tópico e publica
  //--------------------------------------------------------------------
  id_do_cliente.toCharArray(topico, 24);
  client.publish(topico, "Subcrevi tópico");
  client.subscribe(topico);
}
//--------------------------------------------------------------------
// CALLBACK()
//--------------------------------------------------------------------
void callback(char *topico, byte *payload, unsigned int length) {
  Serial.print("Nova mensagem no tópico: ");
  Serial.println(topico);
  Serial.print("com conteúdo:");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
}
//-------------------------------------------------------------------
// LOOP()
//-------------------------------------------------------------------
void loop() {
  client.loop();
}
