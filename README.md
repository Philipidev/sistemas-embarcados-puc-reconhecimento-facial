# ESP32 Wrover Module - Reconhecimento Facial

## Visão Geral
Este projeto envolve o uso de um módulo ESP32 Wrover para reconhecimento facial. O projeto utiliza uma câmera para reconhecimento facial, controlando o acesso de maneira segura.

## Requisitos de Hardware
- Módulo ESP32 Wrover Dev Cam (já vem configurado com a câmera)

## Requisitos de Software
- Arduino IDE (versão 1.8.13 ou posterior)
- Versão 1.0.5 da placa ESP32 para Arduino IDE
- Bibliotecas necessárias para ESP32 e periféricos

## Bibliotecas a Serem Instaladas
Antes de começar, certifique-se de ter as seguintes bibliotecas instaladas no Arduino IDE:
- `ArduinoWebsockets`
- `esp_http_server`
- `esp_timer`
- `esp_camera`

## Configurando o Arduino IDE
1. **Instalar o Pacote da Placa ESP32:**
   - Abra o Arduino IDE e vá em **Arquivo** > **Preferências**.
   - No campo "URLs Adicionais para Gerenciador de Placas", adicione a seguinte URL:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Vá em **Ferramentas** > **Placa** > **Gerenciador de Placas**.
   - Procure por "ESP32" e instale a versão 1.0.5 por Espressif Systems.

2. **Instalar Bibliotecas Necessárias:**
   - Vá em **Sketch** > **Incluir Biblioteca** > **Gerenciar Bibliotecas**.
   - Procure e instale as seguintes bibliotecas:
     - `ArduinoWebsockets`

3. **Configurar as Definições da Placa:**
   - Selecione as configurações da placa conforme mostrado na imagem fornecida:
     ```
     Board: "ESP32 Wrover Module"
     Port: Selecione a porta COM apropriada
     Flash Frequency: "80MHz"
     Flash Mode: "QIO"
     Partition Scheme: "Huge APP (3MB No OTA/1MB SPIFFS)"
     Upload Speed: "921600"
     ```

4. **Modificar o Esquema de Partição:**
   - Navegue até a pasta:
     ```
     C:\Users\phili\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.5\tools\partitions
     ```
   - Substitua o arquivo `huge_app.csv` pelo arquivo `huge_app_zo.csv` e renomeie-o para `huge_app.csv`.

## Executando o Projeto
- Faça o upload do código para o seu ESP32 Wrover Module usando o Arduino IDE.
- Verifique se a configuração do Tools está de acordo com a imagem fornecida para garantir a correta configuração do ambiente.

## Configuração da Rede
- Atualize as credenciais da rede WiFi no código:
  ```cpp
  const char* ssid = "SEU_SSID";
  const char* password = "SUA_SENHA";
  ```
- Após carregar o código, abra o monitor serial e aguarde a conexão WiFi ser estabelecida. Você verá um IP que pode ser usado para acessar a câmera e o sistema de reconhecimento facial através do navegador.

## Interface de Configuração de Usuários
A interface web do sistema pode ser acessada pelo IP mostrado no monitor serial. Nela, você verá opções para configurar os usuários permitidos:

![Interface de Configuração de Usuários](https://prnt.sc/oMiMuZN1hxf_)

- **Stream Camera:** Coloca a câmera no modo de transmissão ao vivo.
- **Detect Faces:** Ativa o modo de detecção de faces.
- **Add User:** Adiciona o usuário que está na câmera no momento. É muito importante ter uma boa iluminação e preencher o nome no campo fornecido para poder adicionar. Após clicar no botão, aguarde os ciclos de imagem.
- **Access Control:** Ativa a detecção de indivíduos para verificar se eles têm acesso ou não.

## Observações
- Certifique-se de ter a versão 1.0.5 do ESP32 instalada no Arduino IDE.
- Substitua corretamente o arquivo `huge_app.csv` conforme as instruções para garantir o funcionamento adequado do código.

## Imagem de Configuração do Tools
![Configuração do Tools](https://prnt.sc/oYXDQeXhMJXi)