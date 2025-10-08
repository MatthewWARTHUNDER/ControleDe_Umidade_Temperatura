/*
 * Arquivo de Configuração de Exemplo
 * 
 * Para usar:
 * 1. Copie este arquivo para config.h
 * 2. Preencha suas credenciais WiFi
 * 3. Ajuste outras configurações conforme necessário
 * 4. Inclua no arquivo .ino: #include "config.h"
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// CONFIGURAÇÕES DE REDE WiFi
// ============================================

// Nome da rede WiFi (SSID)
#define WIFI_SSID "SEU_SSID_AQUI"

// Senha da rede WiFi
#define WIFI_PASSWORD "SUA_SENHA_AQUI"

// Tempo limite para conexão WiFi (milissegundos)
#define WIFI_TIMEOUT 20000

// ============================================
// CONFIGURAÇÕES DO SENSOR DHT22
// ============================================

// Pino GPIO conectado ao DHT22
#define DHT_PIN 4

// Tipo do sensor (DHT11, DHT22, DHT21)
#define DHT_TYPE DHT22

// Intervalo entre leituras do sensor (milissegundos)
// Mínimo recomendado: 2000ms
#define SENSOR_READ_INTERVAL 2000

// ============================================
// CONFIGURAÇÕES DO SERVIDOR WEB
// ============================================

// Porta do servidor web
#define WEB_SERVER_PORT 80

// ============================================
// CONFIGURAÇÕES DE DEBUG
// ============================================

// Habilitar saída serial para debug
#define ENABLE_SERIAL_DEBUG true

// Velocidade da comunicação serial (baud rate)
#define SERIAL_BAUD_RATE 115200

// ============================================
// CONFIGURAÇÕES AVANÇADAS
// ============================================

// Nome do dispositivo na rede
#define DEVICE_NAME "ESP32-TempMonitor"

// Habilitar modo AP (Access Point) se falhar conexão WiFi
#define ENABLE_AP_FALLBACK false

// SSID do modo AP (se habilitado)
#define AP_SSID "ESP32-Monitor"

// Senha do modo AP (deixe vazio para rede aberta)
#define AP_PASSWORD ""

#endif // CONFIG_H
