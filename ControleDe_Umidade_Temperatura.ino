/*
 * Sistema de Monitoramento de Temperatura e Umidade com ESP32
 * 
 * Este projeto implementa um servidor web assíncrono no ESP32 que:
 * - Coleta dados de temperatura e umidade usando o sensor DHT22
 * - Exibe os dados em tempo real através de gráficos interativos
 * - Não requer serviços de cloud externos
 * 
 * Bibliotecas necessárias:
 * - ESPAsyncWebServer
 * - AsyncTCP
 * - DHT sensor library
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <SPIFFS.h>

// Configurações do WiFi
const char* ssid = "SEU_SSID";          // Substitua pelo nome da sua rede WiFi
const char* password = "SUA_SENHA";      // Substitua pela senha da sua rede WiFi

// Configurações do sensor DHT22
#define DHTPIN 4                         // Pino GPIO4 conectado ao DHT22
#define DHTTYPE DHT22                    // Tipo do sensor: DHT22
DHT dht(DHTPIN, DHTTYPE);

// Criar objeto do servidor web na porta 80
AsyncWebServer server(80);

// Variáveis para armazenar as leituras
float temperatura = 0.0;
float umidade = 0.0;
unsigned long ultimaLeitura = 0;
const unsigned long intervaloLeitura = 2000;  // Intervalo de 2 segundos entre leituras

// Função para ler os dados do sensor
void lerSensor() {
  unsigned long tempoAtual = millis();
  
  if (tempoAtual - ultimaLeitura >= intervaloLeitura) {
    ultimaLeitura = tempoAtual;
    
    // Ler dados do sensor
    float novaTemperatura = dht.readTemperature();
    float novaUmidade = dht.readHumidity();
    
    // Verificar se as leituras são válidas
    if (!isnan(novaTemperatura) && !isnan(novaUmidade)) {
      temperatura = novaTemperatura;
      umidade = novaUmidade;
    }
  }
}

// Página HTML principal
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Monitor de Temperatura e Umidade</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            padding: 20px;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        h1 {
            text-align: center;
            color: white;
            margin-bottom: 30px;
            font-size: 2.5em;
            text-shadow: 2px 2px 4px rgba(0,0,0,0.3);
        }
        
        .cards {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin-bottom: 30px;
        }
        
        .card {
            background: white;
            border-radius: 15px;
            padding: 30px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.3);
            text-align: center;
            transition: transform 0.3s ease;
        }
        
        .card:hover {
            transform: translateY(-5px);
        }
        
        .card-icon {
            font-size: 3em;
            margin-bottom: 10px;
        }
        
        .card-title {
            font-size: 1.2em;
            color: #666;
            margin-bottom: 10px;
        }
        
        .card-value {
            font-size: 2.5em;
            font-weight: bold;
            color: #333;
        }
        
        .temperature {
            color: #ff6b6b;
        }
        
        .humidity {
            color: #4ecdc4;
        }
        
        .chart-container {
            background: white;
            border-radius: 15px;
            padding: 30px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.3);
            margin-bottom: 20px;
        }
        
        .chart-title {
            font-size: 1.5em;
            color: #333;
            margin-bottom: 20px;
            text-align: center;
        }
        
        .status {
            text-align: center;
            color: white;
            margin-top: 20px;
        }
        
        .status-indicator {
            display: inline-block;
            width: 12px;
            height: 12px;
            border-radius: 50%;
            background-color: #4CAF50;
            margin-right: 8px;
            animation: pulse 2s infinite;
        }
        
        @keyframes pulse {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.5; }
        }
        
        @media (max-width: 768px) {
            h1 {
                font-size: 1.8em;
            }
            
            .card-value {
                font-size: 2em;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>🌡️ Monitor de Temperatura e Umidade</h1>
        
        <div class="cards">
            <div class="card">
                <div class="card-icon">🌡️</div>
                <div class="card-title">Temperatura</div>
                <div class="card-value temperature">
                    <span id="temperatura">--</span>°C
                </div>
            </div>
            
            <div class="card">
                <div class="card-icon">💧</div>
                <div class="card-title">Umidade</div>
                <div class="card-value humidity">
                    <span id="umidade">--</span>%
                </div>
            </div>
        </div>
        
        <div class="chart-container">
            <h3 class="chart-title">Histórico de Temperatura</h3>
            <canvas id="tempChart"></canvas>
        </div>
        
        <div class="chart-container">
            <h3 class="chart-title">Histórico de Umidade</h3>
            <canvas id="humChart"></canvas>
        </div>
        
        <div class="status">
            <span class="status-indicator"></span>
            <span>Atualização automática ativa</span>
        </div>
    </div>
    
    <script>
        // Configuração dos gráficos
        const maxDataPoints = 20;
        const tempData = {
            labels: [],
            datasets: [{
                label: 'Temperatura (°C)',
                data: [],
                borderColor: '#ff6b6b',
                backgroundColor: 'rgba(255, 107, 107, 0.1)',
                tension: 0.4,
                fill: true
            }]
        };
        
        const humData = {
            labels: [],
            datasets: [{
                label: 'Umidade (%)',
                data: [],
                borderColor: '#4ecdc4',
                backgroundColor: 'rgba(78, 205, 196, 0.1)',
                tension: 0.4,
                fill: true
            }]
        };
        
        const chartOptions = {
            responsive: true,
            maintainAspectRatio: true,
            scales: {
                y: {
                    beginAtZero: false
                }
            },
            plugins: {
                legend: {
                    display: true,
                    position: 'top'
                }
            },
            animation: {
                duration: 750
            }
        };
        
        const tempChart = new Chart(
            document.getElementById('tempChart'),
            {
                type: 'line',
                data: tempData,
                options: chartOptions
            }
        );
        
        const humChart = new Chart(
            document.getElementById('humChart'),
            {
                type: 'line',
                data: humData,
                options: chartOptions
            }
        );
        
        // Função para atualizar os dados
        function atualizarDados() {
            fetch('/dados')
                .then(response => response.json())
                .then(data => {
                    // Atualizar valores nos cards
                    document.getElementById('temperatura').textContent = data.temperatura.toFixed(1);
                    document.getElementById('umidade').textContent = data.umidade.toFixed(1);
                    
                    // Adicionar ao histórico
                    const agora = new Date().toLocaleTimeString('pt-BR');
                    
                    // Temperatura
                    if (tempData.labels.length >= maxDataPoints) {
                        tempData.labels.shift();
                        tempData.datasets[0].data.shift();
                    }
                    tempData.labels.push(agora);
                    tempData.datasets[0].data.push(data.temperatura);
                    tempChart.update();
                    
                    // Umidade
                    if (humData.labels.length >= maxDataPoints) {
                        humData.labels.shift();
                        humData.datasets[0].data.shift();
                    }
                    humData.labels.push(agora);
                    humData.datasets[0].data.push(data.umidade);
                    humChart.update();
                })
                .catch(error => {
                    console.error('Erro ao obter dados:', error);
                });
        }
        
        // Atualizar dados a cada 2 segundos
        setInterval(atualizarDados, 2000);
        
        // Primeira atualização imediata
        atualizarDados();
    </script>
</body>
</html>
)rawliteral";

void setup() {
  // Iniciar comunicação serial
  Serial.begin(115200);
  Serial.println("\n=== Sistema de Monitoramento Iniciando ===");
  
  // Iniciar sensor DHT
  dht.begin();
  Serial.println("Sensor DHT22 inicializado");
  
  // Conectar ao WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 20) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Acesse: http://");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFalha ao conectar ao WiFi!");
    Serial.println("Verifique o SSID e senha configurados");
  }
  
  // Configurar rota para a página principal
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  // Configurar rota para obter dados em JSON
  server.on("/dados", HTTP_GET, [](AsyncWebServerRequest *request){
    lerSensor();
    
    String json = "{";
    json += "\"temperatura\":" + String(temperatura, 1) + ",";
    json += "\"umidade\":" + String(umidade, 1);
    json += "}";
    
    request->send(200, "application/json", json);
  });
  
  // Iniciar servidor
  server.begin();
  Serial.println("Servidor HTTP iniciado");
  Serial.println("=== Sistema Pronto ===\n");
}

void loop() {
  // O loop principal fica vazio, pois o servidor é assíncrono
  // e os dados são lidos sob demanda na rota /dados
  delay(10);
}
