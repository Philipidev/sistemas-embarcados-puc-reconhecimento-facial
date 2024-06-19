# Projeto de Reconhecimento Facial com ESP32

Este projeto implementa um sistema de reconhecimento facial usando uma placa ESP32, uma câmera e módulos adicionais para controle de acesso. O projeto pode ser configurado para funcionar com ou sem um servidor web.

## Requisitos de Software

- Arduino IDE (versão 1.8.13 ou posterior)
- Versão 1.0.5 da placa ESP32 para Arduino IDE
- Bibliotecas necessárias para ESP32 e periféricos:
  - `ArduinoWebsockets`
  - `esp_http_server`
  - `esp_timer`
  - `esp_camera`

## Configuração

### Conexão Wi-Fi

Defina o SSID e a senha da rede Wi-Fi:

```cpp
const char* ssid = "MPS3000";
const char* password = "MPSenha2002";
```

### Modelos de Câmera

Selecione o modelo da câmera descomentando a linha correspondente:

```cpp
#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
//#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"
```

### Modo de Inicialização

Defina o modo de inicialização:

```cpp
#define INICIAR_COM_WEB_SERVER 0 // 0 para iniciar offline sem precisar de internet
```

## Funcionalidades

### Principais Componentes Utilizados

- **ArduinoWebsockets:** Biblioteca utilizada para comunicação via WebSocket.
- **esp_http_server:** Biblioteca utilizada para criar um servidor HTTP no ESP32.
- **esp_timer:** Biblioteca utilizada para funções de temporização no ESP32.
- **esp_camera:** Biblioteca utilizada para controlar a câmera do ESP32.

### Estrutura do Código

1. **Configuração e Inicialização:**
   - Configura os pinos da câmera e inicializa a câmera.
   - Configura os pinos de saída para LED e relé.
   - Conecta à rede Wi-Fi se o modo `INICIAR_COM_WEB_SERVER` estiver ativo.
   
2. **Servidor Web e WebSocket:**
   - Inicia o servidor HTTP e o servidor WebSocket.
   - Define o manipulador para a página inicial (`index_handler`).

3. **Reconhecimento Facial:**
   - Implementa a lógica para detectar, reconhecer e cadastrar rostos.
   - Controla o relé para abrir a porta quando um rosto reconhecido for detectado.

### Funções Principais

- `setup()`: Configura a inicialização da câmera, Wi-Fi, servidor HTTP e WebSocket.
- `loop()`: Executa o reconhecimento facial com ou sem servidor web, dependendo do modo de inicialização.
- `iniciarReconhecimentoComCameraWebServer()`: Lida com o reconhecimento facial e comunicação via WebSocket.
- `iniciarApenasReconhecimento()`: Lida com o reconhecimento facial sem comunicação via WebSocket.
- `open_door()`, `open_door_sem_client()`: Controla a abertura da porta.

### Configuração de FaceNet e HTTP Server

- **FaceNet:** Configuração de parâmetros para detecção e reconhecimento facial.
- **HTTP Server:** Inicializa e configura o servidor HTTP, registra os manipuladores de URI.

### Estrutura de Dados

- **http_img_process_result:** Estrutura que armazena resultados de processamento de imagens.
- **en_fsm_state:** Enumeração para estados da máquina de estados finita (FSM) usada no processo de reconhecimento.

## Como Usar

1. **Configuração:**
   - Conecte os componentes conforme necessário.
   - Ajuste as configurações de Wi-Fi e modelo de câmera no código.
   - Carregue o código no ESP32 usando o Arduino IDE.

2. **Operação:**
   - Para treinamento e reconhecimento de rostos, inicie com `INICIAR_COM_WEB_SERVER` configurado como 1.
   - Para apenas reconhecimento (depois de ter treinado os rostos), configure `INICIAR_COM_WEB_SERVER` como 0.

3. **Acesso:**
   - Acesse o servidor web via IP fornecido no Serial Monitor para treinar novos rostos.
   - O sistema abrirá a porta automaticamente quando um rosto conhecido for reconhecido.

---

Este projeto utiliza as bibliotecas `ArduinoWebsockets`, `esp_http_server`, `esp_timer` e `esp_camera` para implementar um sistema de reconhecimento facial completo e funcional com ESP32.