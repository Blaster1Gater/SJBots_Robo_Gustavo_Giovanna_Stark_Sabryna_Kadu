#include <SoftwareSerial.h>

SoftwareSerial SerialBT(10, 11); // RX, TX

String comandoAtual = "";

void setup() {
  Serial.begin(115200);      // USB
  SerialBT.begin(9600);      // HC-05 padrão
  Serial.println("Nano Bluetooth pronto");
}

void loop() {
  // Atualiza comando quando recebe algo novo
  if (SerialBT.available()) {
    String recebido = SerialBT.readStringUntil('\n');
    recebido.trim();

    if (recebido.length() > 0) {
      comandoAtual = recebido;
      Serial.print("Comando ativo: ");
      Serial.println(comandoAtual);
    }
  }

  // EXECUÇÃO CONTÍNUA
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
