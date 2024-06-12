#include <Adafruit_PN532.h>
#include <Wire.h>
#include "Arduino.h"

#define pin_scl 22
#define pin_sda 21

Adafruit_PN532 nfc(pin_sda, pin_scl);

void reconhecerCartaNFC(){
  Serial.println("aqui");
  uint32_t versiondata = nfc.getFirmwareVersion();
  Serial.println(versiondata);
  if(versiondata > 0){
    Serial.println("aqui2");
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t uidLength;

    // Espera por um cartão NFC
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    if (success) {
      Serial.println("Encontrado um cartão!");
      Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
      Serial.print("UID Value: ");
      for (uint8_t i=0; i < uidLength; i++) {
        Serial.print(" 0x");Serial.print(uid[i], HEX);
      }
      Serial.println("");
      
      Serial.print("UID REAL: ");
      for (uint8_t i=0; i < uidLength; i++) {
        Serial.print("indice ");
        Serial.print(i);
        Serial.print(" => ");
        Serial.print(uid[i]);
        Serial.println("");
      }
      Serial.println("");

      //digitalWrite(led_verde_e_buzzer, HIGH); //close (energise) relay so door unlocks
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.setDebugOutput(true);
  // put your setup code here, to run once:
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Não foi possível encontrar PN53x.   ");
    Serial.println(versiondata);
    while (!versiondata){
      uint32_t versiondata = nfc.getFirmwareVersion();
      Serial.println("Não foi possível encontrar PN53x.   ");
      Serial.println(versiondata);
      delay(1000);
    }
  }
  else{
  // Mostra os detalhes do firmware
    Serial.println("Encontrado chip PN5");
    Serial.println((versiondata>>24) & 0xFF, HEX);
    Serial.print("Firmware ver. ");
    Serial.print((versiondata>>16) & 0xFF, DEC);
    Serial.print('.');
    Serial.println((versiondata>>8) & 0xFF, DEC);
    // Configura o módulo para ser um leitor RFID
    nfc.SAMConfig();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  reconhecerCartaNFC();
  
  delay(500);
}
