#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

String comandoAtual = "";

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  Serial.println("ESP32 Bluetooth pronto");
}

void loop() {
  // Atualiza comando apenas quando receber algo novo
  if (SerialBT.available()) {
    String recebido = SerialBT.readStringUntil('\n');
    recebido.trim();

    if (recebido.length() > 0) {
      comandoAtual = recebido;
      Serial.print("Comando ativo: ");
      Serial.println(comandoAtual);
    }
  }

  // EXECUÇÃO CONTÍNUA DO COMANDO ATIVO
  if (comandoAtual == "UP") {
    Serial.println("UP_OK");
    delay(200);
  }
  else if (comandoAtual == "DOWN") {
    Serial.println("DOWN_OK");
    delay(200);
  }
  else if (comandoAtual == "LEFT") {
    Serial.println("LEFT_OK");
    delay(200);
  }
  else if (comandoAtual == "RIGHT") {
    Serial.println("RIGHT_OK");
    delay(200);
  }
}
