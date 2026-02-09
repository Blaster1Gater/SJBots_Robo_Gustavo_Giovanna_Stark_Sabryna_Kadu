#include <SoftwareSerial.h>

SoftwareSerial SerialBT(6, 7); // RX, TX

// HW-354 (L9110S)
// Motor A
#define A1 3  // PWM
#define A2 2  // digital

// Motor B
#define B1 5  // PWM
#define B2 4  // digital

#define VELOCIDADE_PADRAO 50  // 0–100

String comandoAtual = "";
int velocidade = VELOCIDADE_PADRAO;
int pwmVel = map(VELOCIDADE_PADRAO, 0, 100, 0, 255);

void setup() {
  Serial.begin(9600);
  SerialBT.begin(9600);

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);

  pararMotores();

  Serial.println("Nano Bluetooth pronto");
  Serial.print("Velocidade inicial: ");
  Serial.println(velocidade);
}

void loop() {
  if (SerialBT.available()) {
    String recebido = SerialBT.readStringUntil('\n');
    recebido.trim();

    if (recebido.startsWith("Speed_")) {
      velocidade = recebido.substring(6).toInt();
      velocidade = constrain(velocidade, 0, 100);
      pwmVel = map(velocidade, 0, 100, 0, 255);

      Serial.print("Velocidade: ");
      Serial.println(velocidade);
    }
    else if (recebido.length() > 0) {
      comandoAtual = recebido;
      Serial.print("Comando ativo: ");
      Serial.println(comandoAtual);
    }
  }

  if (comandoAtual == "UP") {
    frente();
  }
  else if (comandoAtual == "DOWN") {
    tras();
  }
  else if (comandoAtual == "LEFT") {
    esquerda();
  }
  else if (comandoAtual == "RIGHT") {
    direita();
  }
  else if (comandoAtual == "PARAR") {
    pararMotores();
  }
  else if(comandoAtual == "LIGAR") {
    ligar();
  }
}

// ===== MOVIMENTOS COM PWM =====

void frente() {
  analogWrite(A1, pwmVel);
  digitalWrite(A2, LOW);
  analogWrite(B1, LOW);
  digitalWrite(B2, pwmVel);
}

void tras() {
  analogWrite(A1, LOW);
  digitalWrite(A2, pwmVel);
  analogWrite(B1, pwmVel);
  digitalWrite(B2, LOW);
}

void direita() {
  analogWrite(A1, pwmVel);
  digitalWrite(A2, LOW);
  analogWrite(B1, LOW);
  digitalWrite(B2, LOW);
}

void esquerda() {
  analogWrite(A1, LOW);
  digitalWrite(A2, LOW);
  analogWrite(B1, LOW);
  digitalWrite(B2, pwmVel);
}

void ligar () {
  velocidade = constrain(velocidade, 0, 100);
  pwmVel = map(velocidade, 0, 100, 0, 255);
}

void pararMotores() {
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
}
