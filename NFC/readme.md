# Leitor de Cartão NFC com ESP32 e Adafruit PN532

## Descrição do Projeto

Este projeto envolve a criação de um sistema de leitura de cartões NFC usando um microcontrolador ESP32, um módulo NFC Adafruit PN532 e relés para controle de acesso. O sistema lê cartões NFC e compara o UID (Identificador Único) do cartão com um UID válido predefinido. Se o cartão for válido, ele aciona um relé para conceder acesso; caso contrário, nega o acesso.

## Funcionalidades

- **Leitura de Cartão NFC**: Utiliza o módulo Adafruit PN532 para ler cartões NFC.
- **Verificação de UID**: Compara o UID lido com um UID válido predefinido.
- **Controle de Acesso**: Controla relés para conceder ou negar acesso com base na verificação do UID.
- **Saída Serial**: Imprime informações detalhadas sobre o processo de leitura e verificação na porta serial.

## Pré-requisitos

Antes de começar, certifique-se de que você tem os seguintes componentes e softwares instalados:

### Componentes de Hardware

- ESP32
- Módulo NFC Adafruit PN532
- Relés
- Cartão NFC

### Software

- Arduino IDE (versão 1.8.19 ou superior)
- Pacote de placas ESP32 (versão 3.0.1)
- Bibliotecas necessárias:
  - **Adafruit_PN532**: Biblioteca para interface com o módulo NFC Adafruit PN532.
  - **Wire**: Biblioteca padrão do Arduino para comunicação I2C.

## Configuração do Ambiente de Desenvolvimento

1. **Instalar a Arduino IDE**:
   - Faça o download e instale a Arduino IDE a partir do [site oficial](https://www.arduino.cc/en/software).

2. **Adicionar Suporte ao ESP32**:
   - Abra a Arduino IDE.
   - Vá para `File > Preferences`.
   - Na caixa "Additional Board Manager URLs", adicione a seguinte URL: `https://dl.espressif.com/dl/package_esp32_index.json`.
   - Vá para `Tools > Board > Board Manager`.
   - Pesquise por "ESP32" e instale o pacote de placas ESP32 da Espressif Systems.

3. **Instalar Bibliotecas Necessárias**:
   - Vá para `Sketch > Include Library > Manage Libraries`.
   - Pesquise por "Adafruit PN532" e instale a biblioteca.
   - Certifique-se de que a biblioteca "Wire" está instalada (deve ser instalada por padrão).

## Conexões de Hardware

- **ESP32 e Módulo NFC Adafruit PN532**:
  - `pin_sda (ESP32 GPIO 21)` -> `SDA (PN532)`
  - `pin_scl (ESP32 GPIO 22)` -> `SCL (PN532)`
- **Relés**:
  - `pinRelay (ESP32 GPIO 5)`
  - `relay_pin_sucesso (ESP32 GPIO 23)`
  - `relay_pin_negado (ESP32 GPIO 32)`

## Funcionamento do Sistema

1. **Inicialização**:
   - O ESP32 inicializa e configura os pinos para os relés.
   - Inicializa o módulo NFC Adafruit PN532.

2. **Leitura do Cartão NFC**:
   - O sistema fica em loop contínuo aguardando um cartão NFC.
   - Quando um cartão é detectado, o UID é lido e comparado com o UID válido predefinido.

3. **Verificação de UID**:
   - Se o UID do cartão corresponder ao UID válido, o sistema aciona o relé de sucesso para liberar a fechadura.
   - Se o UID do cartão não corresponder, o sistema aciona o relé de negação para indicar acesso negado.

4. **Saída Serial**:
   - Informações detalhadas sobre o processo de leitura e verificação são impressas na porta serial para monitoramento e depuração.

## Como Utilizar

1. **Carregar o Código**:
   - Abra o código na Arduino IDE.
   - Selecione a placa ESP32 correta em `Tools > Board`.
   - Conecte o ESP32 ao computador e selecione a porta correta em `Tools > Port`.
   - Carregue o código para o ESP32.

2. **Monitorar o Serial**:
   - Abra o Monitor Serial na Arduino IDE para visualizar as mensagens do sistema.
   - Certifique-se de que a taxa de baud está configurada para 115200.

3. **Testar o Sistema**:
   - Aproximar um cartão NFC ao módulo PN532.
   - Verificar as mensagens no Monitor Serial e observar o comportamento dos relés.
