# 📖 Guia de Instalação Passo a Passo

Este guia detalha todo o processo de instalação do sistema de monitoramento de temperatura e umidade.

## 📋 Pré-requisitos

Antes de começar, você precisará de:
- [ ] Computador com Windows, macOS ou Linux
- [ ] Cabo USB para conectar o ESP32
- [ ] Acesso à internet para download de software
- [ ] Rede WiFi 2.4GHz disponível

## 🔧 Parte 1: Instalação do Software

### Passo 1: Instalar Arduino IDE

1. Acesse https://www.arduino.cc/en/software
2. Baixe a versão adequada para seu sistema operacional
3. Instale seguindo as instruções do instalador
4. Abra o Arduino IDE após a instalação

### Passo 2: Adicionar Suporte ESP32

1. No Arduino IDE, vá em **Arquivo** → **Preferências**
2. Na janela que abrir, encontre o campo "URLs Adicionais para Gerenciadores de Placas"
3. Cole a seguinte URL:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Clique em **OK**
5. Vá em **Ferramentas** → **Placa** → **Gerenciador de Placas...**
6. Na busca, digite "esp32"
7. Encontre "esp32 by Espressif Systems" e clique em **Instalar**
8. Aguarde a instalação completa

### Passo 3: Instalar Bibliotecas

#### Biblioteca DHT Sensor

1. Vá em **Ferramentas** → **Gerenciar Bibliotecas...**
2. Na busca, digite "DHT sensor library"
3. Encontre "DHT sensor library by Adafruit" e clique em **Instalar**
4. Uma janela perguntará sobre dependências, clique em **Install all** (instalar todas)

#### Biblioteca ESPAsyncWebServer (Instalação Manual)

Esta biblioteca não está disponível no gerenciador, então faremos instalação manual:

**Windows:**
1. Baixe o ZIP de: https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip
2. Vá em **Sketch** → **Incluir Biblioteca** → **Adicionar biblioteca .ZIP**
3. Selecione o arquivo baixado
4. Repita o processo para AsyncTCP: https://github.com/me-no-dev/AsyncTCP/archive/master.zip

**macOS/Linux:**
```bash
cd ~/Documents/Arduino/libraries/
git clone https://github.com/me-no-dev/ESPAsyncWebServer.git
git clone https://github.com/me-no-dev/AsyncTCP.git
```

### Passo 4: Verificar Instalação

1. Reinicie o Arduino IDE
2. Vá em **Sketch** → **Incluir Biblioteca**
3. Verifique se aparecem:
   - DHT sensor library
   - ESPAsyncWebServer
   - AsyncTCP

## 🔌 Parte 2: Montagem do Hardware

### Lista de Materiais

- [ ] 1x ESP32 Development Board
- [ ] 1x Sensor DHT22 (AM2302)
- [ ] 1x Resistor 10kΩ
- [ ] 3x Cabos Jumper
- [ ] 1x Protoboard (opcional)

### Esquema de Conexão

```
Passo 1: Identifique os pinos do DHT22
┌─────────────┐
│   DHT22     │
│ ┌─────────┐ │
│ │ o o o o │ │  ← 4 pinos (da esquerda para direita)
│ └─────────┘ │
└─────────────┘
Pino 1: VCC (+)
Pino 2: DATA
Pino 3: Não conectado
Pino 4: GND (-)

Passo 2: Conecte ao ESP32
DHT22 Pino 1 (VCC)  → ESP32 3.3V
DHT22 Pino 2 (DATA) → ESP32 GPIO4
DHT22 Pino 4 (GND)  → ESP32 GND

Passo 3: Adicione o resistor pull-up
Resistor 10kΩ entre:
- VCC (3.3V)
- DATA (GPIO4)
```

### Dicas de Montagem

1. **Use uma protoboard** para facilitar as conexões
2. **Certifique-se** de que o ESP32 está desligado durante a montagem
3. **Verifique a polaridade** antes de ligar
4. **Teste continuidade** com um multímetro se possível

## 💾 Parte 3: Configuração do Código

### Passo 1: Baixar o Código

1. Acesse o repositório no GitHub
2. Clique em **Code** → **Download ZIP**
3. Extraia o arquivo ZIP
4. Ou clone usando:
   ```bash
   git clone https://github.com/MatthewWARTHUNDER/ControleDe_Umidade_Temperatura.git
   ```

### Passo 2: Abrir no Arduino IDE

1. Navegue até a pasta extraída
2. Abra o arquivo `ControleDe_Umidade_Temperatura.ino`
3. O Arduino IDE deve abrir com o projeto

### Passo 3: Configurar WiFi

Encontre estas linhas no código (próximo ao topo):
```cpp
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";
```

Substitua por suas credenciais WiFi:
```cpp
const char* ssid = "MinhaRedeWiFi";
const char* password = "minhaSenhaSecreta123";
```

⚠️ **Importante:**
- Use rede WiFi 2.4GHz (ESP32 não funciona com 5GHz)
- Senha diferencia maiúsculas/minúsculas
- Não use caracteres especiais problemáticos

### Passo 4: Configurar a Placa

1. Vá em **Ferramentas** → **Placa** → **ESP32 Arduino** → **ESP32 Dev Module**
2. Configure as seguintes opções:
   - **Upload Speed**: 115200
   - **CPU Frequency**: 240MHz (WiFi/BT)
   - **Flash Frequency**: 80MHz
   - **Flash Mode**: QIO
   - **Flash Size**: 4MB (32Mb)
   - **Partition Scheme**: Default 4MB with spiffs

### Passo 5: Selecionar a Porta

1. Conecte o ESP32 ao computador via USB
2. Vá em **Ferramentas** → **Porta**
3. Selecione a porta COM (Windows) ou /dev/tty (Mac/Linux) do ESP32
   - Windows: geralmente COM3, COM4, etc.
   - macOS: /dev/cu.usbserial-*
   - Linux: /dev/ttyUSB0 ou /dev/ttyACM0

**Se a porta não aparecer:**
- Instale o driver CP2102 ou CH340 (dependendo do chip USB do seu ESP32)
- Tente outro cabo USB (alguns cabos são apenas para carga)

## 🚀 Parte 4: Upload e Teste

### Passo 1: Compilar o Código

1. Clique no botão ✓ (Verificar) na barra superior
2. Aguarde a compilação
3. Verifique se não há erros na área de mensagens

**Se houver erros:**
- Verifique se todas as bibliotecas estão instaladas
- Confirme se a placa ESP32 está selecionada
- Reinicie o Arduino IDE

### Passo 2: Upload

1. Clique no botão → (Upload)
2. Aguarde o processo (pode levar 1-2 minutos)
3. Algumas placas ESP32 exigem que você:
   - Pressione e segure o botão BOOT
   - Continue segurando até ver "Connecting..."
   - Solte quando o upload começar

### Passo 3: Monitorar a Conexão

1. Abra o Monitor Serial: **Ferramentas** → **Monitor Serial**
2. Configure a velocidade para **115200 baud** no canto inferior direito
3. Pressione o botão RESET no ESP32
4. Você deve ver:
   ```
   === Sistema de Monitoramento Iniciando ===
   Sensor DHT22 inicializado
   Conectando ao WiFi.....
   WiFi conectado!
   Endereço IP: 192.168.1.xxx
   Acesse: http://192.168.1.xxx
   Servidor HTTP iniciado
   === Sistema Pronto ===
   ```

### Passo 4: Acessar a Interface

1. Anote o endereço IP mostrado (ex: 192.168.1.100)
2. Abra um navegador (Chrome, Firefox, Safari, etc.)
3. Digite o endereço IP na barra de endereços: `http://192.168.1.100`
4. Pressione Enter

🎉 **Sucesso!** Você deve ver a interface com os dados de temperatura e umidade.

## 🔍 Solução de Problemas Comuns

### Problema: "Connecting..." infinito durante upload

**Solução:**
1. Pressione e segure o botão BOOT no ESP32
2. Clique em Upload no Arduino IDE
3. Continue segurando BOOT até ver o progresso
4. Solte o botão BOOT

### Problema: "Port not found" ou porta não aparece

**Solução:**
1. Instale drivers USB:
   - CP2102: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   - CH340: http://www.wch.cn/downloads/CH341SER_ZIP.html
2. Tente outro cabo USB
3. Tente outra porta USB do computador
4. Reinicie o computador

### Problema: Falha ao conectar ao WiFi

**Solução:**
1. Verifique SSID e senha (case-sensitive)
2. Certifique-se de usar rede 2.4GHz
3. Aproxime o ESP32 do roteador
4. Desabilite filtro MAC no roteador temporariamente
5. Tente conectar a um hotspot do celular para testar

### Problema: Leituras NaN ou --

**Solução:**
1. Verifique todas as conexões
2. Confirme se o resistor pull-up está instalado
3. Aguarde 2-3 segundos após ligar
4. Teste o sensor com exemplo básico DHT
5. O sensor pode estar defeituoso

### Problema: Página não carrega

**Solução:**
1. Confirme que está na mesma rede WiFi
2. Verifique o IP no Monitor Serial
3. Use `http://` não `https://`
4. Desabilite VPN se estiver usando
5. Limpe o cache do navegador
6. Tente outro navegador

## 📱 Teste no Smartphone

1. Conecte seu smartphone à **mesma rede WiFi**
2. Abra o navegador (Chrome, Safari, etc.)
3. Digite o endereço IP do ESP32
4. A interface deve aparecer e funcionar perfeitamente

## 🎯 Próximos Passos

Agora que tudo está funcionando:
- [ ] Experimente mover o sensor para diferentes locais
- [ ] Observe como temperatura e umidade variam
- [ ] Personalize as cores e intervalos de atualização
- [ ] Adicione mais sensores se desejar
- [ ] Monte em uma caixa permanente

## 📞 Precisa de Ajuda?

Se ainda tiver problemas:
1. Revise cada passo cuidadosamente
2. Verifique a seção de FAQ no README principal
3. Abra uma issue no GitHub com:
   - Mensagens de erro completas
   - Fotos da montagem
   - Modelo do seu ESP32
   - Sistema operacional usado

---

Boa sorte e divirta-se monitorando! 🌡️💧