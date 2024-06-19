#include <Adafruit_PN532.h>
#include <Wire.h>
#include "Arduino.h"

#define pin_scl 22
#define pin_sda 21
#define pinRelay 5
#define relay_pin_sucesso 23 // Escolha o pino GPIO para controlar a corrente
#define relay_pin_negado 32 // Escolha o pino GPIO para controlar a corrente

Adafruit_PN532 nfc(pin_sda, pin_scl);

// UID do cartão específico (188, 81, 211)
uint8_t validUID[] = {211, 188, 81, 211};

void reconhecerCartaNFC() {
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (versiondata > 0) {
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t uidLength;

    // Espera por um cartão NFC
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    if (success) {
      Serial.println("Encontrado um cartão!");
      Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
      Serial.print("UID Value: ");
      for (uint8_t i = 0; i < uidLength; i++) {
        Serial.print(" 0x"); Serial.print(uid[i], HEX);
      }
      Serial.println("");

      Serial.print("UID REAL: ");
      for (uint8_t i = 0; i < uidLength; i++) {
        Serial.print("indice ");
        Serial.print(i);
        Serial.print(" => ");
        Serial.print(uid[i]);
        Serial.println("");
      }
      Serial.println("");

      // Verifica se o UID corresponde ao UID específico
      bool isValidCard = true;
      for (uint8_t i = 0; i < 4; i++) {
        if (uid[i] != validUID[i]) {
          isValidCard = false;
          break;
        }
      }

      if (isValidCard) {
        Serial.println("Cartão válido encontrado, liberando fechadura.");
        // Ativa o relé (ou corrente) no pino escolhido
        digitalWrite(relay_pin_negado, LOW); // Garante que o relé esteja desligado
        digitalWrite(relay_pin_sucesso, HIGH); // Energiza o relé
        digitalWrite(pinRelay, LOW); // Energiza o relé
        delay(1000); // Mantenha o relé ativado por 1 segundo (ajuste conforme necessário)
        digitalWrite(relay_pin_sucesso, LOW); // Desenergiza o relé
        digitalWrite(pinRelay, HIGH); // Energiza o relé
      } else {
        Serial.println("Cartão não autorizado.");
        digitalWrite(relay_pin_sucesso, LOW); // Garante que o relé esteja desligado
        digitalWrite(pinRelay, HIGH); // Energiza o relé
        digitalWrite(relay_pin_negado, HIGH); // Garante que o relé esteja desligado
        delay(500); // Mantenha o relé ativado por 1 segundo (ajuste conforme necessário)
        digitalWrite(relay_pin_negado, LOW); // Garante que o relé esteja desligado
      }
    } else {
      digitalWrite(relay_pin_sucesso, LOW); // Garante que o relé esteja desligado se nenhum cartão for encontrado
      digitalWrite(pinRelay, HIGH); // Energiza o relé
      digitalWrite(relay_pin_negado, LOW); // Garante que o relé esteja desligado
    }
  } else {
    digitalWrite(relay_pin_sucesso, LOW); // Garante que o relé esteja desligado se o módulo NFC não estiver disponível
    digitalWrite(pinRelay, HIGH); // Energiza o relé
    digitalWrite(relay_pin_negado, LOW); // Garante que o relé esteja desligado
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.setDebugOutput(true);
  // Configura o pino do relé como saída
  pinMode(relay_pin_sucesso, OUTPUT);
  digitalWrite(relay_pin_sucesso, LOW); // Inicializa o relé como desligado

  pinMode(relay_pin_negado, OUTPUT);
  digitalWrite(relay_pin_negado, LOW); // Inicializa o relé como desligado

  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, HIGH); // Inicializa o relé como desligado

  // Inicializa o módulo NFC
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Não foi possível encontrar PN53x.");
    Serial.println(versiondata);
    while (!versiondata){
      uint32_t versiondata = nfc.getFirmwareVersion();
      Serial.println("Não foi possível encontrar PN53x.");
      Serial.println(versiondata);
      delay(1000);
    }
  } else {
    // Mostra os detalhes do firmware
    Serial.println("Encontrado chip PN5");
    Serial.println((versiondata >> 24) & 0xFF, HEX);
    Serial.print("Firmware ver. ");
    Serial.print((versiondata >> 16) & 0xFF, DEC);
    Serial.print('.');
    Serial.println((versiondata >> 8) & 0xFF, DEC);
    // Configura o módulo para ser um leitor RFID
    nfc.SAMConfig();
  }
}

void loop() {
  // Executa a leitura do cartão NFC repetidamente
  reconhecerCartaNFC();
  delay(500);
}
