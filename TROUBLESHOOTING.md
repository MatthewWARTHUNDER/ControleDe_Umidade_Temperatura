# 🔍 Guia de Solução de Problemas

Este guia ajuda a diagnosticar e resolver problemas comuns.

## 📑 Índice

- [Problemas de Compilação](#problemas-de-compilação)
- [Problemas de Upload](#problemas-de-upload)
- [Problemas de WiFi](#problemas-de-wifi)
- [Problemas com Sensor](#problemas-com-sensor)
- [Problemas de Interface Web](#problemas-de-interface-web)
- [Problemas de Desempenho](#problemas-de-desempenho)
- [Problemas Avançados](#problemas-avançados)

## 🔨 Problemas de Compilação

### Erro: "DHT.h: No such file or directory"

**Causa**: Biblioteca DHT não instalada.

**Solução**:
1. Abra Arduino IDE
2. Vá em **Ferramentas** → **Gerenciar Bibliotecas**
3. Procure "DHT sensor library"
4. Instale "DHT sensor library by Adafruit"
5. Quando perguntado sobre dependências, clique em "Install all"

### Erro: "ESPAsyncWebServer.h: No such file or directory"

**Causa**: Biblioteca ESPAsyncWebServer não instalada.

**Solução**:
```bash
cd ~/Documents/Arduino/libraries/
git clone https://github.com/me-no-dev/ESPAsyncWebServer.git
git clone https://github.com/me-no-dev/AsyncTCP.git
```

Ou baixe manualmente:
- https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip
- https://github.com/me-no-dev/AsyncTCP/archive/master.zip

Extraia na pasta `Arduino/libraries/`

### Erro: "Sketch too big"

**Causa**: Código não cabe na memória flash.

**Solução**:
1. Vá em **Ferramentas** → **Partition Scheme**
2. Selecione "Huge APP (3MB No OTA/1MB SPIFFS)"
3. Recompile o código

### Erro: Múltiplas definições de funções

**Causa**: Bibliotecas conflitantes.

**Solução**:
1. Remova versões antigas das bibliotecas
2. Mantenha apenas uma versão de cada biblioteca
3. Reinicie o Arduino IDE

### Erro: "Board ESP32 Dev Module not found"

**Causa**: Suporte ESP32 não instalado.

**Solução**:
1. Vá em **Arquivo** → **Preferências**
2. Em "URLs Adicionais", adicione:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Vá em **Ferramentas** → **Placa** → **Gerenciador de Placas**
4. Procure "esp32"
5. Instale "esp32 by Espressif Systems"

## 📤 Problemas de Upload

### Erro: "A fatal error occurred: Failed to connect"

**Soluções possíveis**:

**Solução 1: Pressionar botão BOOT**
1. Mantenha pressionado o botão **BOOT** no ESP32
2. Clique em **Upload** no Arduino IDE
3. Continue segurando BOOT até ver "Writing at..."
4. Solte o botão BOOT

**Solução 2: Reduzir velocidade de upload**
1. Vá em **Ferramentas** → **Upload Speed**
2. Selecione **115200**
3. Tente o upload novamente

**Solução 3: Sequência BOOT + RESET**
1. Mantenha **BOOT** pressionado
2. Pressione e solte **RESET** (ainda segurando BOOT)
3. Clique em **Upload**
4. Solte **BOOT** quando upload iniciar

### Erro: "Port not found" ou "Serial port not available"

**Causa**: Drivers USB não instalados ou porta incorreta.

**Soluções**:

**Windows:**
1. Identifique o chip USB (geralmente CP2102 ou CH340)
2. Baixe e instale o driver:
   - CP2102: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
   - CH340: http://www.wch.cn/downloads/CH341SER_ZIP.html
3. Reinicie o computador
4. Reconecte o ESP32

**macOS:**
```bash
# Para CH340
brew tap adrianmihalko/ch340g-ch34g-ch34x-mac-os-x-driver
brew install --cask wch-ch34x-usb-serial-driver

# Para CP2102
# Baixe de: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
```

**Linux:**
```bash
# Adicionar usuário ao grupo dialout
sudo usermod -a -G dialout $USER

# Logout e login novamente
# Ou execute:
newgrp dialout
```

### Erro: "Timed out waiting for packet header"

**Causa**: Problema de comunicação serial.

**Soluções**:
1. Use outro cabo USB (muitos cabos são apenas para carga)
2. Tente outra porta USB do computador
3. Desconecte o DHT22 temporariamente
4. Verifique se não há curto-circuito
5. Tente em outro computador

### Upload interrompido no meio

**Causa**: Interferência, cabo ruim, ou fonte inadequada.

**Soluções**:
1. Use cabo USB curto e de qualidade
2. Conecte direto ao computador (não use hub USB)
3. Desabilite antivírus temporariamente
4. Feche outros programas que usam serial
5. Use fonte USB de 500mA ou mais

## 📡 Problemas de WiFi

### ESP32 não conecta ao WiFi

**Diagnóstico via Monitor Serial**:
```
Conectando ao WiFi...................
Falha ao conectar ao WiFi!
```

**Soluções**:

**1. Verificar credenciais**
```cpp
// Certifique-se de que está correto (case-sensitive)
const char* ssid = "NomeDaRede";     // Exatamente como aparece
const char* password = "SenhaCorreta"; // Maiúsculas/minúsculas
```

**2. Verificar frequência da rede**
- ESP32 só funciona com **2.4GHz**
- Não funciona com redes **5GHz**
- Configure seu roteador para ter rede 2.4GHz separada

**3. Verificar modo de segurança**
- ESP32 suporta: WPA, WPA2, WPA2-PSK
- Pode ter problemas com: WPA3, WEP, Enterprise

**4. Verificar distância**
- Aproxime o ESP32 do roteador
- Verifique se não há obstáculos metálicos
- Teste próximo ao roteador primeiro

**5. Desabilitar filtro MAC**
- Acesse configurações do roteador
- Temporariamente desabilite filtro MAC
- Ou adicione o MAC do ESP32 à lista permitida

**6. Aumentar timeout**
```cpp
// Aumentar tentativas de conexão
int tentativas = 0;
while (WiFi.status() != WL_CONNECTED && tentativas < 40) { // 40 em vez de 20
    delay(500);
    Serial.print(".");
    tentativas++;
}
```

### ESP32 conecta mas desconecta

**Causa**: Sinal fraco ou interferência.

**Soluções**:

**1. Melhorar sinal**
```cpp
// Adicionar no setup(), antes de WiFi.begin()
WiFi.setTxPower(WIFI_POWER_19_5dBm);  // Máxima potência
```

**2. Implementar reconexão automática**
```cpp
void verificarWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi desconectado! Reconectando...");
        WiFi.disconnect();
        WiFi.begin(ssid, password);
        
        int tentativas = 0;
        while (WiFi.status() != WL_CONNECTED && tentativas < 20) {
            delay(500);
            tentativas++;
        }
        
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Reconectado!");
            Serial.println(WiFi.localIP());
        }
    }
}

// Chamar no loop()
void loop() {
    verificarWiFi();
    delay(10);
}
```

**3. Usar IP estático** (mais estável)
```cpp
IPAddress local_IP(192, 168, 1, 100);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WiFi.config(local_IP, gateway, subnet);
```

### Não consigo encontrar o IP do ESP32

**Solução 1: Monitor Serial**
1. Abra Monitor Serial (115200 baud)
2. Pressione RESET no ESP32
3. O IP será exibido após "Endereço IP:"

**Solução 2: Verificar no roteador**
1. Acesse interface web do roteador
2. Procure por "Dispositivos conectados" ou "DHCP Clients"
3. Procure por "ESP32" ou "Espressif"

**Solução 3: Scan de rede**
```bash
# Linux/Mac
nmap -sn 192.168.1.0/24

# Windows (instalar Advanced IP Scanner)
# Download: https://www.advanced-ip-scanner.com/
```

## 🌡️ Problemas com Sensor

### Leituras mostram "NaN" ou "--"

**Diagnóstico**:
```
Temperatura: nan
Umidade: nan
```

**Causas e soluções**:

**1. Conexões incorretas**
```
Verificar:
✓ VCC → 3.3V (não 5V!)
✓ DATA → GPIO4
✓ GND → GND
✓ Resistor 10kΩ entre VCC e DATA
```

**2. Resistor pull-up ausente**
- Obrigatório: Resistor 10kΩ entre VCC e DATA
- Alguns módulos DHT22 já incluem (verifique)

**3. Aguardar inicialização**
```cpp
void setup() {
    // ...
    dht.begin();
    delay(2000);  // Aguardar 2 segundos para sensor estabilizar
}
```

**4. Verificar pino correto**
```cpp
#define DHTPIN 4  // Certifique-se que o pino está correto
```

**5. Sensor defeituoso**
- Teste com sketch exemplo básico DHT
- Se ainda assim não funcionar, sensor pode estar defeituoso

### Leituras inconsistentes ou flutuam muito

**Causa**: Interferência, conexões fracas.

**Soluções**:

**1. Melhorar conexões**
- Use cabos curtos (< 30cm)
- Solde conexões se possível
- Use protoboard de qualidade

**2. Adicionar capacitor**
- Adicione capacitor 100µF entre VCC e GND
- Ajuda a estabilizar alimentação

**3. Média de leituras**
```cpp
float lerTemperaturaMedia() {
    float soma = 0;
    int leituras = 5;
    
    for (int i = 0; i < leituras; i++) {
        float temp = dht.readTemperature();
        if (!isnan(temp)) {
            soma += temp;
        }
        delay(500);
    }
    
    return soma / leituras;
}
```

**4. Filtro de outliers**
```cpp
bool leituraValida(float valor, float anterior) {
    const float MAX_DIFERENCA = 5.0;  // Mudança máxima permitida
    return abs(valor - anterior) < MAX_DIFERENCA;
}
```

### Sensor para de responder após um tempo

**Causa**: Aquecimento, interferência, ou bug no código.

**Soluções**:

**1. Reinicializar sensor**
```cpp
void reiniciarSensor() {
    dht.begin();
    delay(2000);
}
```

**2. Aumentar intervalo entre leituras**
```cpp
const unsigned long intervaloLeitura = 5000;  // 5 segundos
```

**3. Watchdog timer**
```cpp
#include <esp_task_wdt.h>

void setup() {
    // Habilitar watchdog de 30 segundos
    esp_task_wdt_init(30, true);
    esp_task_wdt_add(NULL);
}

void loop() {
    esp_task_wdt_reset();  // Reset watchdog
    // resto do código
}
```

## 🌐 Problemas de Interface Web

### Página não carrega

**Diagnóstico**:
1. Verifique Monitor Serial: servidor iniciou?
2. Teste ping: `ping 192.168.1.100`
3. Verifique firewall

**Soluções**:

**1. Verificar se está na mesma rede**
- Computador e ESP32 devem estar na mesma rede WiFi
- Desabilite VPN
- Desabilite dados móveis no celular

**2. Usar http:// não https://**
```
✓ http://192.168.1.100
✗ https://192.168.1.100
```

**3. Limpar cache do navegador**
- Chrome: Ctrl+Shift+Del
- Firefox: Ctrl+Shift+Del
- Safari: Cmd+Option+E

**4. Testar com curl**
```bash
curl http://192.168.1.100
curl http://192.168.1.100/dados
```

### Gráficos não aparecem

**Causa**: Chart.js não carregou.

**Soluções**:

**1. Verificar console do navegador**
- F12 para abrir DevTools
- Aba Console
- Procure por erros

**2. Verificar conexão com internet**
- Chart.js é carregado via CDN
- ESP32 precisa que dispositivo tenha internet
- Alternativa: hospedar Chart.js localmente

**3. Testar Chart.js**
Adicione no console do navegador:
```javascript
console.log(typeof Chart);  // Deve retornar 'function'
```

### Dados não atualizam automaticamente

**Causa**: JavaScript não está executando.

**Soluções**:

**1. Verificar JavaScript habilitado**
- Certifique-se que JavaScript está habilitado no navegador

**2. Verificar console de erros**
- F12 → Console
- Procure erros em vermelho

**3. Testar endpoint manualmente**
```
Acesse: http://192.168.1.100/dados
Deve retornar: {"temperatura":25.4,"umidade":60.2}
```

## ⚡ Problemas de Desempenho

### ESP32 reinicia sozinho

**Diagnóstico via Monitor Serial**:
```
Brownout detector was triggered
```

**Causa**: Fonte de alimentação inadequada.

**Soluções**:

**1. Usar fonte adequada**
- Mínimo 500mA
- Use porta USB 3.0 (mais corrente)
- Ou carregador de celular 2A

**2. Adicionar capacitor**
- Capacitor eletrolítico 470µF entre VCC e GND do ESP32
- Ajuda a estabilizar picos de corrente

**3. Desabilitar brownout detector (não recomendado)**
```cpp
#include "soc/soc.h"
#include "soc/rtc_crtl_reg.h"

void setup() {
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  // Desabilitar brownout
    // resto do código
}
```

### ESP32 aquece muito

**Causa normal**: WiFi consome muita energia.

**Se aquecer excessivamente**:

**1. Reduzir potência WiFi**
```cpp
WiFi.setTxPower(WIFI_POWER_11dBm);  // Reduzir potência
```

**2. Adicionar dissipador**
- Pequeno dissipador de alumínio
- Pode usar pasta térmica

**3. Melhorar ventilação**
- Não encaixote completamente
- Deixe aberturas para circulação

### Interface web lenta

**Causa**: HTML muito grande.

**Soluções**:

**1. Comprimir HTML**
- Use ferramentas online para minificar
- Remova espaços e comentários desnecessários

**2. Usar compressão gzip** (avançado)
```cpp
// Adicionar header
AsyncWebServerResponse *response = request->beginResponse_P(
    200, "text/html", index_html_gz, sizeof(index_html_gz)
);
response->addHeader("Content-Encoding", "gzip");
request->send(response);
```

## 🔧 Problemas Avançados

### Memória insuficiente

**Erro**: "region `dram0_0_seg' overflowed"

**Soluções**:

**1. Usar PROGMEM**
```cpp
const char html[] PROGMEM = R"rawliteral(...

// Ao enviar:
request->send_P(200, "text/html", html);
```

**2. Separar HTML em arquivo SPIFFS**

**3. Reduzir tamanho do HTML**

### Stack overflow

**Erro**: "***ERROR*** A stack overflow in task..."

**Causa**: Recursão profunda ou variáveis locais grandes.

**Soluções**:
```cpp
// Aumentar stack size da task
xTaskCreatePinnedToCore(
    taskFunction,
    "TaskName",
    8192,  // Stack size (aumentar)
    NULL,
    1,
    &taskHandle,
    0
);
```

### Conflitos de biblioteca

**Erro**: Conflitos entre versões.

**Solução**:
1. Remover todas as versões
2. Instalar apenas versões compatíveis
3. Verificar dependências

## 📞 Ainda com problemas?

Se nenhuma solução funcionou:

1. **Crie um issue no GitHub** com:
   - Descrição detalhada
   - Mensagens de erro completas
   - Logs do Monitor Serial
   - Fotos da montagem
   - Modelo do ESP32
   - Versões das bibliotecas

2. **Teste com exemplo básico**:
   - Tente código mínimo de WiFi
   - Tente código mínimo de DHT
   - Isole o problema

3. **Hardware alternativo**:
   - Teste outro ESP32
   - Teste outro sensor DHT22
   - Teste outra porta USB

---

**Dica**: Sempre faça mudanças incrementais e teste após cada mudança!
