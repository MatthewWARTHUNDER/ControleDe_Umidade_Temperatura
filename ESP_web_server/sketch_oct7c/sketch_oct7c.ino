#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <LittleFS.h>
#else

#endif

// --- Bibliotecas e Configuração do Sensor DHT22 ---
#include <DHT.h>
#include <Adafruit_Sensor.h> 
#define DHTPIN 26            
#define DHTTYPE DHT22         
DHT dht(DHTPIN, DHTTYPE);

// --- Configurações de Rede ---
const char* ssid = "DON'T HACK ME!";     
const char* password = "Gidsa33#*"; 

// Cria o objeto AsyncWebServer na porta 80
AsyncWebServer server(80);

// ===============================================
// FUNÇÕES DE LEITURA DO SENSOR DHT22
// ===============================================

String readDHTTemperature() {
  // Lê a temperatura em Celsius
  float t = dht.readTemperature();
  if (isnan(t)) {    
    Serial.println("Falha ao ler o sensor DHT22!");
    return "0";
  }
  else {
    Serial.print("Temperatura: ");
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // Lê a umidade
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Falha ao ler o sensor DHT22!");
    return "0";
  }
  else {
    Serial.print("Umidade: ");
    Serial.println(h);
    return String(h);
  }
}

void setup(){
  Serial.begin(19200);
  
  // Inicializa o Sensor DHT22
  dht.begin();
  Serial.println("DHT22 inicializado.");

  // Inicializa o LittleFS (Sistema de Arquivos)
  if(!LittleFS.begin()){
    Serial.println("ERRO: Falha ao montar o LittleFS. Verifique o plugin de upload.");
    return; // Para a execução se o sistema de arquivos não iniciar
  }
  Serial.println("LittleFS montado com sucesso.");

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Imprime o IP local
  Serial.println("\nWiFi conectado.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Configura a rota principal (para servir o index.html)
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });
  
  // Rota para buscar a temperatura
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", readDHTTemperature().c_str());
  });
  
  // Rota para buscar a umidade
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", readDHTHumidity().c_str());
  });
  
  // Inicia o servidor
  server.begin();
  Serial.println("Servidor Web iniciado.");
}

void loop(){
  // O loop fica vazio porque o AsyncWebServer lida com as requisições
}