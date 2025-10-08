# 📝 Exemplos de Uso

Este documento contém exemplos práticos de uso e personalização do sistema de monitoramento.

## 🌡️ Exemplo Básico de Uso

### 1. Configuração Mínima

```cpp
// Configuração mínima necessária no arquivo .ino
const char* ssid = "MinhaRedeWiFi";
const char* password = "minhaSenha123";
#define DHTPIN 4
```

### 2. Acessar os Dados

Após upload, acesse via navegador:
```
http://192.168.1.100  // Substitua pelo IP do seu ESP32
```

## 🔧 Exemplos de Personalização

### Mudar Intervalo de Atualização para 5 segundos

**No código C++ (.ino):**
```cpp
const unsigned long intervaloLeitura = 5000;  // 5000ms = 5 segundos
```

**No JavaScript (dentro do HTML):**
```javascript
setInterval(atualizarDados, 5000);  // 5000ms = 5 segundos
```

### Alterar Pino do Sensor

Se você quiser usar GPIO16 em vez de GPIO4:

```cpp
#define DHTPIN 16  // Mude para GPIO16
```

### Usar IP Estático

Adicione após `WiFi.begin(ssid, password);`:

```cpp
IPAddress local_IP(192, 168, 1, 100);    // IP fixo desejado
IPAddress gateway(192, 168, 1, 1);       // Gateway do roteador
IPAddress subnet(255, 255, 255, 0);      // Máscara de sub-rede
IPAddress primaryDNS(8, 8, 8, 8);        // DNS primário (opcional)
IPAddress secondaryDNS(8, 8, 4, 4);      // DNS secundário (opcional)

if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
  Serial.println("Falha ao configurar IP estático");
}
```

### Adicionar Alertas de Temperatura

```cpp
void verificarAlertas() {
  const float TEMP_MAX = 30.0;
  const float TEMP_MIN = 15.0;
  
  if (temperatura > TEMP_MAX) {
    Serial.println("ALERTA: Temperatura muito alta!");
    // Adicione ação desejada (LED, buzzer, etc)
  }
  
  if (temperatura < TEMP_MIN) {
    Serial.println("ALERTA: Temperatura muito baixa!");
  }
}

// No loop() ou após ler o sensor:
verificarAlertas();
```

### Mudar Cores da Interface

No CSS (dentro do HTML), localize e modifique:

```css
/* Cor de fundo principal */
body {
    background: linear-gradient(135deg, #1e3c72 0%, #2a5298 100%);
}

/* Cor da temperatura */
.temperature {
    color: #e74c3c;  /* vermelho mais escuro */
}

/* Cor da umidade */
.humidity {
    color: #3498db;  /* azul mais escuro */
}
```

## 📊 Exemplo: Consumindo a API

### JavaScript (Fetch API)

```javascript
// Obter dados em JSON
fetch('http://192.168.1.100/dados')
  .then(response => response.json())
  .then(data => {
    console.log('Temperatura:', data.temperatura + '°C');
    console.log('Umidade:', data.umidade + '%');
  })
  .catch(error => {
    console.error('Erro:', error);
  });
```

### Python

```python
import requests
import time

ESP32_IP = "192.168.1.100"

while True:
    try:
        response = requests.get(f"http://{ESP32_IP}/dados")
        data = response.json()
        
        temp = data['temperatura']
        umid = data['umidade']
        
        print(f"Temperatura: {temp}°C | Umidade: {umid}%")
        
        # Verificar condições
        if temp > 30:
            print("⚠️ Temperatura alta!")
        
    except Exception as e:
        print(f"Erro: {e}")
    
    time.sleep(5)  # Aguardar 5 segundos
```

### Node.js

```javascript
const axios = require('axios');

const ESP32_IP = '192.168.1.100';

async function obterDados() {
    try {
        const response = await axios.get(`http://${ESP32_IP}/dados`);
        const { temperatura, umidade } = response.data;
        
        console.log(`Temperatura: ${temperatura}°C | Umidade: ${umidade}%`);
        
        // Salvar em arquivo
        const fs = require('fs');
        const timestamp = new Date().toISOString();
        const log = `${timestamp},${temperatura},${umidade}\n`;
        fs.appendFileSync('dados.csv', log);
        
    } catch (error) {
        console.error('Erro:', error.message);
    }
}

// Executar a cada 10 segundos
setInterval(obterDados, 10000);
```

### Curl (Linha de Comando)

```bash
# Obter dados uma vez
curl http://192.168.1.100/dados

# Monitorar continuamente (Linux/Mac)
watch -n 2 "curl -s http://192.168.1.100/dados | python -m json.tool"

# Salvar em arquivo com timestamp
while true; do
    timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    data=$(curl -s http://192.168.1.100/dados)
    echo "$timestamp - $data" >> log.txt
    sleep 5
done
```

## 🎨 Exemplo: Interface Personalizada

### Criar Página Simplificada

Adicione uma nova rota no código .ino:

```cpp
// Página simples alternativa
const char simple_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Monitor Simples</title>
    <style>
        body {
            font-family: Arial;
            text-align: center;
            padding: 50px;
            background: #282c34;
            color: white;
        }
        .value {
            font-size: 4em;
            margin: 20px;
        }
    </style>
</head>
<body>
    <h1>Monitor Simples</h1>
    <div>
        <div class="value" id="temp">--</div>
        <div>Temperatura (°C)</div>
    </div>
    <div>
        <div class="value" id="hum">--</div>
        <div>Umidade (%)</div>
    </div>
    <script>
        function atualizar() {
            fetch('/dados')
                .then(r => r.json())
                .then(d => {
                    document.getElementById('temp').textContent = d.temperatura.toFixed(1);
                    document.getElementById('hum').textContent = d.umidade.toFixed(1);
                });
        }
        setInterval(atualizar, 2000);
        atualizar();
    </script>
</body>
</html>
)rawliteral";

// Adicionar rota
server.on("/simples", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", simple_html);
});
```

Acesse: `http://192.168.1.100/simples`

## 🔔 Exemplo: Notificações via Telegram

```cpp
// Adicione no topo do arquivo
#include <WiFiClientSecure.h>

const char* TELEGRAM_BOT_TOKEN = "SEU_TOKEN_AQUI";
const char* TELEGRAM_CHAT_ID = "SEU_CHAT_ID_AQUI";

void enviarTelegram(String mensagem) {
    WiFiClientSecure client;
    client.setInsecure();
    
    if (client.connect("api.telegram.org", 443)) {
        String url = "/bot" + String(TELEGRAM_BOT_TOKEN) + 
                     "/sendMessage?chat_id=" + String(TELEGRAM_CHAT_ID) + 
                     "&text=" + mensagem;
        
        client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: api.telegram.org\r\n" +
                     "Connection: close\r\n\r\n");
        
        client.stop();
        Serial.println("Mensagem Telegram enviada");
    }
}

// Exemplo de uso
void verificarENotificar() {
    if (temperatura > 30.0) {
        enviarTelegram("ALERTA: Temperatura alta: " + String(temperatura) + "°C");
    }
}
```

## 💾 Exemplo: Salvar Dados em SPIFFS

```cpp
#include <SPIFFS.h>

void setup() {
    // ... código existente ...
    
    // Inicializar SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Erro ao montar SPIFFS");
        return;
    }
}

void salvarDados() {
    File file = SPIFFS.open("/dados.csv", "a");
    if (file) {
        String linha = String(millis()) + "," + 
                       String(temperatura, 1) + "," + 
                       String(umidade, 1) + "\n";
        file.print(linha);
        file.close();
    }
}

// Nova rota para download dos dados
server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/dados.csv", "text/csv");
});
```

## 🌐 Exemplo: Integração com Home Assistant

Configure no `configuration.yaml` do Home Assistant:

```yaml
sensor:
  - platform: rest
    resource: http://192.168.1.100/dados
    name: ESP32 Temperatura
    unit_of_measurement: "°C"
    value_template: '{{ value_json.temperatura }}'
    
  - platform: rest
    resource: http://192.168.1.100/dados
    name: ESP32 Umidade
    unit_of_measurement: "%"
    value_template: '{{ value_json.umidade }}'
```

## 📱 Exemplo: App Mobile com Cordova

Crie um app simples com Apache Cordova:

```html
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Monitor ESP32</title>
</head>
<body>
    <h1>Monitor ESP32</h1>
    <div id="dados"></div>
    
    <script>
        const ESP32_IP = 'http://192.168.1.100';
        
        async function buscarDados() {
            try {
                const response = await fetch(`${ESP32_IP}/dados`);
                const data = await response.json();
                
                document.getElementById('dados').innerHTML = `
                    <h2>Temperatura: ${data.temperatura.toFixed(1)}°C</h2>
                    <h2>Umidade: ${data.umidade.toFixed(1)}%</h2>
                `;
            } catch (error) {
                console.error('Erro:', error);
            }
        }
        
        setInterval(buscarDados, 2000);
        buscarDados();
    </script>
</body>
</html>
```

## 🔒 Exemplo: Adicionar Autenticação

```cpp
// No topo do arquivo
const char* www_username = "admin";
const char* www_password = "senha123";

// Modificar a rota principal
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if (!request->authenticate(www_username, www_password)) {
        return request->requestAuthentication();
    }
    request->send_P(200, "text/html", index_html);
});

// Também proteger a rota de dados
server.on("/dados", HTTP_GET, [](AsyncWebServerRequest *request){
    if (!request->authenticate(www_username, www_password)) {
        return request->requestAuthentication();
    }
    
    lerSensor();
    String json = "{";
    json += "\"temperatura\":" + String(temperatura, 1) + ",";
    json += "\"umidade\":" + String(umidade, 1);
    json += "}";
    
    request->send(200, "application/json", json);
});
```

## 🎯 Dicas de Uso

1. **Teste de Conectividade**: Use `ping 192.168.1.100` para verificar se o ESP32 está acessível

2. **Debug via Serial**: Sempre mantenha o Monitor Serial aberto durante testes

3. **Reiniciar ESP32**: Se algo der errado, pressione o botão RESET

4. **Atualização Remota (OTA)**: Para implementar, use a biblioteca ArduinoOTA

5. **Monitoramento Contínuo**: Use ferramentas como `curl` em scripts para logging

## 📚 Recursos Adicionais

- **Chart.js Docs**: https://www.chartjs.org/docs/
- **ESP32 Arduino Core**: https://github.com/espressif/arduino-esp32
- **DHT Sensor Lib**: https://github.com/adafruit/DHT-sensor-library
- **ESPAsyncWebServer**: https://github.com/me-no-dev/ESPAsyncWebServer

---

**Quer mais exemplos?** Abra uma issue no GitHub com a tag `exemplo` e descreva o que você gostaria de ver!
