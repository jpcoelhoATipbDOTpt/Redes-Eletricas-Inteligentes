// REDES ELÉTRICAS INTELIGENTES
//
// Código para testar a cadeia de compilação e gravação do programa no ESP32
// Placa: "ESP32 Dev Module"
// 
// Adaptado de "Exemplos/Blink"
//
// Depois de compilado e carregado para a plataforma de desenvolvimento ESP32, 
// o LED existente na placa deve piscar com uma frequência de 0.5Hz.
//
// 2023/2024

#define LED_BUILTIN 2
unsigned int cnt = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.println(cnt);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  cnt++;
}
